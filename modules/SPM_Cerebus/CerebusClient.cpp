///////////////////////////////////////////////////////////////////////////////
//
// CerebusClient.cpp - Implementation of the CerebusClient class
//
// The main user-level functions are SetupConnection, ReadPacket and
// TearDownConnection. ReadPacket always returns the next packet from
// the Cerebus system. If a packet is available immediately, then it
// will return right away, otherwise it will perform a blocking wait
// (up to a timeout).


#include <sstream>
#include "winsock2.h"
#include "CerebusClient.h"

WSADATA wsaData;

//-----------------------------------------------------------------------------
/// Constructor. Zeros selected variables.
CerebusClient::CerebusClient(void)
{
	_ReceiveBuffer = new char[MAX_RECEIVE_BUFSIZE];
	if( _ReceiveBuffer == NULL) throw std::exception("CerebusClient: Could not allocate memory for _ReceiveBuffer\n");
	ResetVariables();
    _ReceivingSocket = 0;
	_ClockFrequency = 30000.0; // This is nominal (actual might be a bit different)
}

void
CerebusClient::ResetVariables(void)
{
	_FirstSysProtoMonitorReceived = false;
	_PacketCheckNum = 0;
	_NumBytesSinceCheck = 0;
	_NumBytesInBuffer = 0;
	_BufferReadIndex = 0;
	sprintf( _LocalIP, "%s", DEFAULT_LOCAL_IP_ADDR);
}

//-----------------------------------------------------------------------------
/// Destructor. Disconnects client UDP connection.
CerebusClient::~CerebusClient(void)
{
    TearDownConnection();
	delete [] _ReceiveBuffer;
}


//-----------------------------------------------------------------------------
/// Initialize the UDP connections with the Cerebus device.
//
/// Creates and binds a UDP socket. Uses
/// Winsock, but can easily be adapted for another system.
bool
CerebusClient::SetupConnection( char *NSP_IP)
{
	// Reset member variables every time we connect, because some of these variables
	// make assumptions about continuity of information coming from the Cerebus. So if
	// we disconnect/connect, then this information will not longer be continuous.
	ResetVariables();

	if( NSP_IP != NULL) {
		if( strlen( NSP_IP) > MAX_IP_LENGTH) throw std::exception("CerebusClient::SetupConnection(): IP Address length exceeds MAX");
		sprintf( _LocalIP, "%s", NSP_IP);
	}

	struct sockaddr_in LocalAddr;

	//-----------------------------------------------
	// Initialize Winsock. According to the documentation, it is alright to
    // invoke WSAStartup more than once.
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		throw std::exception("CerebusClient::SetupConnection(): Unable to initialize Winsock");

	//---------------------------------------------
	// Create socket for receiving data.
	closesocket(_ReceivingSocket);
	_ReceivingSocket = socket(AF_INET, SOCK_DGRAM,0);// IPPROTO_UDP);
	if(_ReceivingSocket == INVALID_SOCKET)
	  throw std::exception("CerebusClient::SetupConnection(): Unable to initialize receiving socket");

	//---------------------------------------------
	// Set socket options so that multiple clients can receive data on this socket
	const char optval = 1;
	int status;
	status = setsockopt (_ReceivingSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));
	if (status < 0){
		throw std::exception("CerebusClient::SetupConnection(): Could not set socket option SO_REUSEADDR!\n");
	}

	int optval2 = 1024*1024;
	status = setsockopt(_ReceivingSocket, SOL_SOCKET, SO_RCVBUF, (char *)&optval2, sizeof(optval2));
	if (status < 0){
		printf("%d",WSAGetLastError());
		throw std::exception("CerebusClient::SetupConnection(): Could not set socket option SO_RCVBUF!\n");
	}

	//---------------------------------------------
	// Set up the LocalAddr structure with the IP address of
	// the workstation and the specified port number.
	LocalAddr.sin_family		= AF_INET;
	LocalAddr.sin_port			= htons(LOCAL_PORT);
	LocalAddr.sin_addr.s_addr	= inet_addr(_LocalIP);

	//-----------------------------------------------
	// Bind the local socket. This is important for setting a fixed local
	// port for the Cerebus unit to respond to.
	struct sockaddr* local = (struct sockaddr *) &LocalAddr;
	if( bind( _ReceivingSocket, local, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		//char errString[256];
		//sprintf(errString,"cannot bind local: err %ld", WSAGetLastError());
	    //throw std::exception(errString);
		_ReceivingSocket = 0;
		return false;
	}
	return true;
}


//-----------------------------------------------------------------------------
/// Release UDP socket resources.
//
/// Eliminate the socket that connects the client with the Cerebus unit. Shut
/// shut down Winsock.
void
CerebusClient::TearDownConnection(void)
{
    closesocket(_ReceivingSocket);
    WSACleanup();
}

//-----------------------------------------------------------------------------
// Reads the next packet from the Cerebus system (could be a spike event,
// analog/digital data or continuous waveform snippet or something else).
// If no data is immediately available, then performs a blocking read until
// data becomes available or timeout (seconds) expires. If any packets
// are available, then it reads them all into an internal memory buffer in
// the CerebusClient class (to clear the UDP buffer), but only returns the
// first packet. The remaining buffered packets can then be read using
// subsequent calls to this function. The return value is NULL if timeout
// expired, otherwise a pointer to the newly allocated buffer object (the
// caller is responsible for deleting the object when finished with it)
//
Packet*
CerebusClient::ReadPacket( double timeout)
{
	//
	// If there are no data bytes in the _ReceiveBuffer, then read
	// any available new data into this buffer
	//
	if( _NumBytesInBuffer == 0) {

		_NumBytesInBuffer = WaitForAndReceiveData( _ReceiveBuffer, MAX_RECEIVE_BUFSIZE, timeout);
		// printf("-");

		// If no new bytes were available, then timeout must have expired
		if( _NumBytesInBuffer == 0) {
			return NULL;
		}
	}

	//
	// At this point there should be some data in the _ReceiveBuffer, and the read
	// index should not be at the end of the buffer.
	//
	if( _NumBytesInBuffer <= 0) {
        throw std::exception("CerebusClient::ReadPacket: Internal error (_NumBytesInBuffer <= 0)");
	}
	if( _BufferReadIndex >= _NumBytesInBuffer) {
        throw std::exception("CerebusClient::ReadPacket: Internal error (_BufferReadIndex >= _NumBytesInBuffer)");
	}

	//
	// Parse the packet at current read index of the buffer and advance the read index
	//
	char *buffer = _ReceiveBuffer + _BufferReadIndex;
	int bytes_parsed;
	Packet *pack = ParsePacket( buffer, &bytes_parsed);

	//
	// Advance the buffer read index. If it gets to the end, then reset it to zero.
	// (It should never go past the end)
	_BufferReadIndex += bytes_parsed;
	if( _BufferReadIndex == _NumBytesInBuffer) {
		_NumBytesInBuffer = 0;
		_BufferReadIndex = 0;
	}
	if( _BufferReadIndex > _NumBytesInBuffer) {
		throw std::exception("CerebusClient::ReadPacket: Internal error (Buffer read pointer passed the end of buffer)");
	}

	return pack;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// PRIVATE/PROTECTED functions /////////////////////////////////////////////?
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Performs a blocking wait until data from the Cerebus is available, and then
// keeps reading incoming data bytes for as long as there is more data
// immediately available (or until buffer_length is reached). Returns the number
// of bytes read. If timeout expires or data cannot be read for some other reason
// then returns 0.
//
int
CerebusClient::WaitForAndReceiveData( char *buffer, int buffer_length, double timeout)
{
	bool data_available = WaitForInput( timeout);

	if( !data_available) return 0;

	char *remaining_buffer = buffer;
	int remaining_buffer_length = buffer_length;
	int total_bytes = 0;
    while( data_available)
    {
		int bytes_recv = ReceiveSomeData( remaining_buffer, remaining_buffer_length);
		//printf("%i ",bytes_recv);
		remaining_buffer += bytes_recv;
		remaining_buffer_length -= bytes_recv;
		total_bytes += bytes_recv;
		if( remaining_buffer_length < MIN_RECEIVE_BUFSIZE) break;
		data_available = WaitForInput( 0); // Non-blocking check for data availability
	}
	//printf(": %i\n", total_bytes);
	return total_bytes;
}

//----------------------------------------------------------------------------------------
// Performs a blocking wait (up to timeout seconds) until Cerebus data is available.
// Returns true if there is data available to be read, otherwise false.
// If timeout is zero, then it will just test whether data is available
// and return immediately.
bool
CerebusClient::WaitForInput( double timeout)
{
	//-----------------------------------------------
    if(_ReceivingSocket == 0)
        throw std::exception("CerebusClient::WaitForInput: Socket Uninitialized");

	// Set up wait struct
	struct timeval wait, *pWait;
	if( timeout < 0) { // Negative timeout value means we are willing to wait forever
		pWait = NULL;
	} else {
		wait.tv_sec  = (long)timeout;
		double remainder = timeout - ((double)(wait.tv_sec));
		wait.tv_usec = (long)(remainder*1000000.0);
		pWait = &wait;
	}

	//-----------------------------------------------
	// Set up the select structure.
    fd_set  selectset;
    FD_ZERO(&selectset);
    FD_SET(_ReceivingSocket, &selectset);

	//-----------------------------------------------
    // Check the status of the receiving socket. Read, if a packet is
    // available.
    int nfds   = 0; // Compatibility.

    int status = select(nfds, &selectset, NULL, NULL, pWait);
	///printf( "status = %i\n", status);
    if(status == SOCKET_ERROR)
    {
        std::ostringstream err;
        err << "CerebusClient::WaitForInput: socket select error "
            << "(Winsock error code " << WSAGetLastError() << ")";

        throw std::exception(err.str().c_str());
    }
    if(status == 0)
	{
        //printf("CerebusClient::WaitForInput(): Read interval expired without receiving a "
        //                        "packet from Cerebus processor\n");
		return false;
	}
	if(status > 0) return true;
	else return false;
}

//------------------------------------------------------------------------------
// Receives as many bytes as the system can give us in a single read call
// into the buffer (up to a max of buffer_length). Returns the number of
// bytes actually received.
//
int
CerebusClient::ReceiveSomeData( char *buffer, int buffer_length)
{
    //-----------------------------------------------
    // Receive a UDP packet.
    struct sockaddr_in sender_addr;
    int   sockaddr_in_len = sizeof(sender_addr);
    int	  bytes_recv      = 0;
    int	  flags	          = 0;

	int result;
    result = recvfrom(_ReceivingSocket, buffer, buffer_length, flags,
			              (SOCKADDR *) &sender_addr, &sockaddr_in_len);

	if(result == SOCKET_ERROR)
    {
		std::ostringstream err;
		err << "CerebusClient::ReadPacket: ReceiveSomeData(): Read from server socket failed (Winsock error code " << WSAGetLastError() << ")";
		throw std::exception(err.str().c_str());
	}
	if(result < 0)
    {
		std::ostringstream err;
		err << "CerebusClient::ReadPacket: ReceiveSomeData(): Read from server socket failed (unspecified error)";
		throw std::exception(err.str().c_str());
	}
	if(result < 0)
    {
		std::ostringstream err;
		err << "CerebusClient::ReadPacket: ReceiveSomeData(): Read from server socket failed (zero bytes read)";
		throw std::exception(err.str().c_str());
	}

	bytes_recv = result;
    //if(bytes_recv != buffer_length)
    //{
    //    printf("ReadPacket(): Received less than the requested number of bytes");
    //}
	return bytes_recv;
}


//--------------------------------------------------------------------------------------
// Parses a single packet from a binary byte buffer. Returns a pointer to a newly allocated
// packet object, and outputs the number of bytes parsed in `bytes_parsed`.
//
Packet*
CerebusClient::ParsePacket( char *buffer, int *bytes_parsed)
{
	Packet *pack = NULL;
	cbPKT_GENERIC *packet = (cbPKT_GENERIC*) buffer;
	_PacketCheckNum++;
	// Print out raw header bytes received
	//printf("<%i>", bytes_recv);
	//printf("Received %i bytes\n", bytes_recv);
	//printf("Header: time=%i, chid=%i(0x%.4X), type=%i, dlen=%i\n", packet.time, packet.chid, packet.chid, packet.type, packet.dlen);

	//
	// Return the number of bytes parsed through the pointer argument
	//
	*bytes_parsed = cbPKT_HEADER_SIZE + packet->dlen * 4;

	// Increment count of bytes received since last check
	_NumBytesSinceCheck += *bytes_parsed;

	if( (packet->chid & cbPKTCHAN_CONFIGURATION) == cbPKTCHAN_CONFIGURATION) { // If the "config" bit is set, then it is a system/config packet
		pack = ParseConfigPacket( packet);
	} else { // else it is a data packet
		if( packet->chid >= 1 && packet->chid <= 128){ // Channel ID-s below 128 are spike channels
			cbPKT_SPK *spike_packet = (cbPKT_SPK*) packet;
			//printf("[%i.%i:%i]\n", spike_packet->chid, spike_packet->unit, spike_packet->time);
			SpikePacket *spike_pack = new SpikePacket();
			spike_pack->chan = spike_packet->chid;
			spike_pack->unit = spike_packet->unit;

			for (int i=0; i<3; i++) spike_pack->fPattern[i] = (double)spike_packet->fPattern[i];
			spike_pack->nPeak = spike_packet->nPeak;
			spike_pack->nValley = spike_packet->nValley;
			spike_pack->dlen = spike_packet->dlen;
			for (int i=0; i<128; i++) spike_pack->snippet[i] = spike_packet->wave[i];

			pack = spike_pack;
		}
		if( packet->chid == 0) { // Channel ID 0 means GROUP packet (i.e. continuous waveform, perhaps)
			//printf("~");
			cbPKT_GROUP *group_packet = (cbPKT_GROUP*) packet;
			GroupPacket *g_pack = new GroupPacket();
			g_pack->chid = group_packet->chid;
			g_pack->dlen = group_packet->dlen;
			g_pack->data = group_packet->data;
			pack = g_pack;
		}
		if ( packet->chid == 0x8000) { //Channel ID of 0x8000 means groupinfo packet, containing continuous waveform (?)
			cbPKT_GROUPINFO *groupinfo_packet = (cbPKT_GROUPINFO*) packet;
			WaveDataPacket *wave_pack = new WaveDataPacket();
			wave_pack->chan = groupinfo_packet->chid;
			wave_pack->list = groupinfo_packet->list;
			pack = wave_pack;
		}
		if( packet->chid > 128) { // Channel ID above 128 means digital input
			// printf("#");
			cbPKT_DINP *dinp_packet = (cbPKT_DINP*) packet;
			DigitalPacket* digital_pack = new DigitalPacket();
			digital_pack->chid = dinp_packet->chid;
			digital_pack->dlen = dinp_packet->dlen;
			digital_pack->data = dinp_packet->data;
			pack = digital_pack;
		}
	}

	//
	// If no specific packet was parsed, then generate a generic packet
	//
	if( pack == NULL) pack = new Packet();

	//
	// Return the packet
	//
	pack->nbytes = *bytes_parsed;
	pack->time = ((double) packet->time) / _ClockFrequency; // Convert Cerebus clock time to seconds
	return pack;
}

Packet*
CerebusClient::ParseConfigPacket( cbPKT_GENERIC *packet)
{
	Packet *pack = NULL;
	// Extract the part of channel ID other than the "config" bit
	unsigned short chid = packet->chid & (~cbPKTCHAN_CONFIGURATION);
	if( chid > 0) {
		// Non-zero channel ID for a config message indicates that it is a "Preview" configuration of some sort
	} else {
		switch( packet->type) {
			case cbPKTTYPE_SYSHEARTBEAT:
				pack = new HeartbeatPacket();
				// printf(".");
				break;
			case cbPKTTYPE_SYSPROTOCOLMONITOR: // system protocol monitor packet (tells us how many bytes have been sent since the previous protocol monitor packet)
				//printf("\nReceived cbPKT_SYSPROTOCOLMONITOR: ");
				if( packet->dlen != 1) {
					std::ostringstream err;
					err << "CerebusClient::ParsePacket(): Data length was expected to be 4, but was instead " << packet->dlen;
					throw std::exception(err.str().c_str());
				} else {
					cbPKT_SYSPROTOCOLMONITOR *pSysProtoMonitorPacket = (cbPKT_SYSPROTOCOLMONITOR*) packet;
					int sent_packets = pSysProtoMonitorPacket->sentpkts;
					//printf("NSP sent %i packets\n", sent_packets);
					if( _FirstSysProtoMonitorReceived) {
						//printf( "We received %i packets\n", _PacketCheckNum);
						int num_dropped_packets = sent_packets - _PacketCheckNum;
						// printf("\n%i PACKETS DROPPED!!!\n", num_dropped_packets);
						// Compose an output packet to report the number of packets received, number dropped and number of bytes received
						StatusPacket *status_pack = new StatusPacket();
						status_pack->packetsReceived = _PacketCheckNum;
						status_pack->packetsDropped = num_dropped_packets;
						status_pack->bytesReceived = _NumBytesSinceCheck;
						pack = status_pack;
					}
					_FirstSysProtoMonitorReceived = true;
					_PacketCheckNum = 0;
					_NumBytesSinceCheck = 0;
				}
				break;
			default:
				break;
		}
	}

	return pack;
}
