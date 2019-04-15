/////////////////////////////////////////////////////////////////////////////////////////
//
// Packet.h - declaration of the Packet base class and specific subclasses that represent
//            the different types of data that can be received from a spike acquisition
//            system.
// 
// Meel Velliste 10/14/2010

//
// Base packet type. All packets have a type identifier and a timestamp. Timestamp refers
// to the event time that originated this packet, based on the hardware clock of the spike
// acquisition, but is in units of seconds.
//
class Packet
{
public:
	int type;    // Packet type ID, see below for valid values
	int nbytes;  // Number of bytes that were in the raw packet (for monitoring purposes)
	double time; // Packet source timestamp in seconds

public:
	// Valid values for packet ID
	static const int TYPE_UNDEFINED = -1;
	static const int TYPE_NULL      = 0;
	static const int TYPE_HEARTBEAT = 1;
	static const int TYPE_STATUS    = 2;
	static const int TYPE_SPIKE     = 100;
	static const int TYPE_WAVEDATA  = 101;
	static const int TYPE_GROUP		= 102;
	static const int TYPE_DIGITAL   = 103; // JW: Assuming this is arbitrary
	static const int TYPE_ANALOG    = 104; // SF continuing the assumption it's arbitrary
		
public:
	Packet(void){ type = TYPE_UNDEFINED; nbytes = 0; time = 0;}
	virtual ~Packet(void){}
};

class HeartbeatPacket : public Packet
{
public:
	HeartbeatPacket(void){ type = TYPE_HEARTBEAT;}
	virtual ~HeartbeatPacket(void){}
};

class StatusPacket : public Packet
{
public:
	int bytesReceived; // Number of bytes received from spike processor since last status packet
	int packetsReceived; // Number of packets received from spike processor since last status packet
	int packetsDropped; // Number of packets dropped since last status packet
public:
	StatusPacket(void){ type = TYPE_STATUS;}
	virtual ~StatusPacket(void){}
};

class SpikePacket : public Packet
{
public:
	int chan; // Channel number (1-based)
	int unit; // Unit number (0 = unsorted, 1 = unit a, 2 = unit b, etc)
	int source_index;
	double fPattern[3];
	short nPeak;
	short nValley;
	char dlen;
	short snippet[128];



public:
	SpikePacket(void){ type = TYPE_SPIKE;}
	virtual ~SpikePacket(void){}
};

class WaveDataPacket : public Packet
{
public:
	int chan; // Channel number (1-based)
	unsigned int* list; //data?
public:
	WaveDataPacket(void){ type = TYPE_WAVEDATA;}
	virtual ~WaveDataPacket(void){}
};

class GroupPacket : public Packet
{
public:
    unsigned short  chid;       // 0x0000
    unsigned char   dlen;       // packet length equal
	short* data;
public:
	GroupPacket(void){ type = TYPE_GROUP;}
	virtual ~GroupPacket(void){}
};

class DigitalPacket : public Packet
{
public:
	unsigned short chid;
	unsigned char dlen;
	unsigned int* data;
public:
	DigitalPacket(void){ type = TYPE_DIGITAL;}
	virtual ~DigitalPacket(void){}
};
