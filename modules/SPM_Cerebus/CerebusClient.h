///////////////////////////////////////////////////////////////////////////////
//
// CerebusClient.h - Declaration of the CerebusClient class
//
// The main user-level functions are SetupConnection, ReadPacket and 
// TearDownConnection. ReadPacket always returns the next packet from 
// the Cerebus system. If a packet is available immediately, then it
// will return right away, otherwise it will perform a blocking wait
// (up to a timeout).
//
// Meel Velliste and Angus McMorland 10/7/2010

#ifndef _CEREBUS_CLIENT_H_
#define _CEREBUS_CLIENT_H_

#include <exception>
#include <string>
#include <winsock2.h>
#include "cbhwlib.h"
#include "Packet.h"


#define REMOTE_IP_ADDR  "192.168.137.128"
#define REMOTE_PORT     51001
#define DEFAULT_LOCAL_IP_ADDR  "192.168.137.1"
#define LOCAL_PORT      51002

#define CEREBUS_HEARTBEAT_INTERVAL  .01  // seconds

#define MAX_RECEIVE_BUFSIZE 1024*1024
#define MIN_RECEIVE_BUFSIZE sizeof(cbPKT_GENERIC)
#define MAX_IP_LENGTH 256

class CerebusClient
{
protected:
	SOCKET       _ReceivingSocket;
	bool         _FirstSysProtoMonitorReceived;
	int          _PacketCheckNum;
	int          _NumBytesSinceCheck;
	char         *_ReceiveBuffer;
	int          _NumBytesInBuffer;
	int          _BufferReadIndex;
	double       _ClockFrequency; // Cerebus clock counts per second
	char         _LocalIP[MAX_IP_LENGTH];

	void ResetVariables(void);
	int WaitForAndReceiveData( char *buffer, int buffer_length, double timeout);
	bool WaitForInput( double timeout);
	int ReceiveSomeData( char *buffer, int buffer_length);
	Packet* ParsePacket( char *buffer, int *bytes_parsed);
	Packet* ParseConfigPacket( cbPKT_GENERIC *packet);

public:
    // Constructor and destructor.
    CerebusClient(void);
    virtual ~CerebusClient(void);

    // Important utility functions.
    bool SetupConnection( char *NSP_IP);
    void TearDownConnection(void);

	// Reads a general packet from Cerebus
	// timeout - timeout value for blocking read (seconds). Negative indicates infinite wait.
	// Zero indicates non-blocking read.
	// Returns a pointer to a new packet object (make sure to delete this object when finished with it).
	// Returns NULL if nothing was read (i.e. timed out)
    Packet* ReadPacket( double timeout) throw(std::exception);
};


#endif //_CEREBUS_CLIENT_H_

