// Cerebus- Artifact Elimination
// For NHP and HST rigs, uses digital input to remove large artifact

#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <queue>
#include "Dragonfly.h"
#include "Dragonfly_config.h"
#include "spike_types.h"
#include "CerebusClient.h"
#include "SpikeCounter.h"
#include "LFPAggregate.h"


Dragonfly_Module dragonfly;
CMessage msg;

#define FIRST_SNIPPET_CHUNK_LENGTH	5
#define SECOND_SNIPPET_CHUNK_START  10	
#define SECOND_SNIPPET_CHUNK_LENGTH	2

#define MAX_CEREBUS_CHANNELS				128		//Updated to include sensory channels
#define MAX_CEREBUS_UNITS					6
#define MAX_CEREBUS_TOTAL_UNITS				(MAX_CEREBUS_CHANNELS*MAX_CEREBUS_UNITS)

SpikeCounter TotalCounter( MAX_SPIKE_CHANS_PER_SOURCE, MAX_UNITS_PER_CHAN );
SpikeCounter theCounter( MAX_SPIKE_CHANS_PER_SOURCE, MAX_UNITS_PER_CHAN);
SpikeCounter threshCounter( MAX_SPIKE_CHANS_PER_SOURCE, 1);

SpikeCounter TotalRejectCounter( MAX_SPIKE_CHANS_PER_SOURCE, MAX_UNITS_PER_CHAN );
SpikeCounter theRejectCounter( MAX_SPIKE_CHANS_PER_SOURCE, MAX_UNITS_PER_CHAN);
SpikeCounter rejectThreshCounter( MAX_SPIKE_CHANS_PER_SOURCE, 1);

int TotalCount[MAX_TOTAL_SPIKE_CHANS_PER_SOURCE];
unsigned char theCount[MAX_TOTAL_SPIKE_CHANS_PER_SOURCE];
unsigned char threshCount[MAX_SPIKE_CHANS_PER_SOURCE];
short lfpdata[(MAX_SPIKE_CHANS_PER_SOURCE+MAX_ANALOG_CHANS)*LFPSAMPLES_PER_HEARTBEAT];

int Overall_Spike_Count;
int Snippet_Message_Number;
MDF_SPIKE_SNIPPET* ss_msgs[MAX_SPIKE_CHANS_PER_SOURCE*MAX_UNITS_PER_CHAN]; //a very large number of possible snippets per heartbeat

int Overall_Rejected_Count;
int Rejected_Snippet_Message_Number;
MDF_REJECTED_SNIPPET* rs_msgs[MAX_SPIKE_CHANS_PER_SOURCE*MAX_UNITS_PER_CHAN]; //a very large number of possible snippets per heartbeat
bool validFlag;

double FS = 1.0/30000.0;
#define PRETHRESHOLD_SAMPLES 11

double bufferDelay = 0.002; // delay in s
std::queue<SpikePacket> spikeQueue;
std::queue<LARGE_INTEGER> stQueue;
LARGE_INTEGER frequency;
LARGE_INTEGER bufferPeriod;

MDF_DIGITAL_EVENT* de_msgs[MAX_DIG_PER_SAMPLE];
MDF_STIM_SYNC_EVENT* sse_msgs[MAX_DIG_PER_SAMPLE];
int Dig_Message_Number;
int Sse_Message_Number;

LFPAggregate LFPData( MAX_SPIKE_CHANS_PER_SOURCE+MAX_ANALOG_CHANS, LFPSAMPLES_PER_HEARTBEAT); //LFP sampled at 1kHz, heartbeats at 10ms==100Hz therefore 10 samples agregated
bool overflow_possible;


double artifactTimer = 0;
double spikeTime;

double BLANK_SAMPLES = 30.01; // 90 usec
double BLANK_TIME = BLANK_SAMPLES*FS;//
double ARTIFACT_WINDOW_TIME = 0.006;

int acceptAllDigEvts = 0;
int collect_LFP = 1;
int collect_snippets = 1;
int stimSyncMask = 0;
int stimParamMask = 0;

unsigned int prevDigDataRaw = 0; // previous 16-bit value of digital input (to subtract (AND NOT) from current value)
unsigned int prevDigData = 0; // previous dig input value, after subtracted from value before that
int digCount = 0;


void SendCounts( double timestamp, unsigned char *count, int num_chans, int nsp_index)
{
	//printf("c");
	// Fill in the Dragonfly message data struct
	MDF_RAW_SPIKECOUNT sc;
	memset( &sc, 0, sizeof(sc));
	sc.source_index = nsp_index;
	sc.source_timestamp = timestamp;
	sc.count_interval = CEREBUS_HEARTBEAT_INTERVAL;
	if( num_chans > MAX_TOTAL_SPIKE_CHANS_PER_SOURCE) throw std::exception("SendCounts(): num_chans exceeds MAX_RAW_TOTAL_SPIKE_CHANS");
	for( int i = 0; i < num_chans; i++)	sc.counts[i] = count[i];

	// Send the message
	msg.Set( MT_RAW_SPIKECOUNT, &sc, sizeof(sc));
	dragonfly.SendMessage( &msg);
}
void AddSpikeSnippet(SpikePacket *spike_pack,int nsp_index,double ptime)
{
//	ss_msg.ss[Overall_Spike_Count] = ss;

	if (Overall_Spike_Count==0)
		ss_msgs[Snippet_Message_Number] = new MDF_SPIKE_SNIPPET();

	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].source_index = nsp_index;
	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].source_timestamp = ptime;
	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].nPeak = (short)spike_pack->nPeak;
	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].nValley = (short)spike_pack->nValley;
	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].channel = (short)spike_pack->chan;
	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].unit = (unsigned char)spike_pack->unit;
	for( int i = 0; i < 3; i++)	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].fPattern[i] = spike_pack->fPattern[i];
	for( int i = 0; i < SAMPLES_PER_SNIPPET; i++)	ss_msgs[Snippet_Message_Number]->ss[Overall_Spike_Count].snippet[i] = spike_pack->snippet[i];


	Overall_Spike_Count++;

	if (Overall_Spike_Count>=SNIPPETS_PER_MESSAGE)
	{
		Overall_Spike_Count = 0;
		Snippet_Message_Number++;

	}

}

void SendSnippets()
{
	//printf("$");
	if (Overall_Spike_Count == 0)
		Snippet_Message_Number--;

	for (int i = 0; i<=Snippet_Message_Number; i++)
	{
		// Send the message
			msg.Set( MT_SPIKE_SNIPPET, ss_msgs[i], sizeof(*ss_msgs[i]));
			dragonfly.SendMessage( &msg);
			delete ss_msgs[i];
	}

	Overall_Spike_Count = 0;
	Snippet_Message_Number = 0;

}

void AddDigitalEvent(DigitalPacket* dig_pack,int nsp_idx,double ptime)
{
	if (Dig_Message_Number < MAX_DIG_PER_SAMPLE) //hst 3/5
	{
		de_msgs[Dig_Message_Number] = new MDF_DIGITAL_EVENT();

		de_msgs[Dig_Message_Number]->source_index = nsp_idx;
		de_msgs[Dig_Message_Number]->source_timestamp = ptime;
		de_msgs[Dig_Message_Number]->channel = (int)dig_pack->chid;

		unsigned short data = (unsigned short) dig_pack->data[0];
		de_msgs[Dig_Message_Number]->data[0] = (unsigned int)(data & 0x00FF);
		de_msgs[Dig_Message_Number]->data[1] = (unsigned int)(data & 0xFF00);
		Dig_Message_Number++;
	}
}

void AddStimSyncEvent(DigitalPacket* dig_pack,int nsp_idx,double ptime)
{
	if (Sse_Message_Number < MAX_DIG_PER_SAMPLE) 
	{
		sse_msgs[Sse_Message_Number] = new MDF_STIM_SYNC_EVENT();

		sse_msgs[Sse_Message_Number]->source_index = nsp_idx;
		sse_msgs[Sse_Message_Number]->source_timestamp = ptime;
		sse_msgs[Sse_Message_Number]->channel = (int)dig_pack->chid;
		sse_msgs[Sse_Message_Number]->data = dig_pack->data[0];

		Sse_Message_Number++;
	}
}

void SendStimSyncEvents()
{
	Sse_Message_Number--;

	for (int i = 0; i<=Sse_Message_Number; i++)
	{
		// Send the message
		msg.Set( MT_STIM_SYNC_EVENT, sse_msgs[i], sizeof(*sse_msgs[i]));
		dragonfly.SendMessage( &msg);
		delete sse_msgs[i];
	}

	Sse_Message_Number = 0;
}

void SendDigEvents()
{
	Dig_Message_Number--;

	for (int i = 0; i<=Dig_Message_Number; i++)
	{
		// Send the message
		msg.Set( MT_DIGITAL_EVENT, de_msgs[i], sizeof(*de_msgs[i]));
		dragonfly.SendMessage( &msg);
		delete de_msgs[i];
	}

	Dig_Message_Number = 0;
}


bool checkSnippetValidity(SpikePacket* pack ){
	short tempSum = 0;
	short firstMean, secondMean = 0;

	for( int i = 0; i < FIRST_SNIPPET_CHUNK_LENGTH ; i++){
		tempSum += pack->snippet[i];
	}

	firstMean = tempSum/FIRST_SNIPPET_CHUNK_LENGTH; 
	tempSum = 0;

	for( int i = SECOND_SNIPPET_CHUNK_START; i < SECOND_SNIPPET_CHUNK_START+SECOND_SNIPPET_CHUNK_LENGTH; i++){
		tempSum += pack->snippet[i];
	}

	secondMean = tempSum/SECOND_SNIPPET_CHUNK_LENGTH;

	return(firstMean > secondMean);
}

void AddRejectedSnippet(SpikePacket *spike_pack,int nsp_index,double ptime,int rejectType)
{

	if (Overall_Rejected_Count==0)
		rs_msgs[Rejected_Snippet_Message_Number] = new MDF_REJECTED_SNIPPET();

	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].source_index = nsp_index;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].source_timestamp = ptime;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].nPeak = (short)spike_pack->nPeak;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].nValley = (short)spike_pack->nValley;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].channel = (short)spike_pack->chan;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].unit = (unsigned char)spike_pack->unit;
	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].rejectType = rejectType;
	for( int i = 0; i < 3; i++)	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].fPattern[i] = spike_pack->fPattern[i];
	for( int i = 0; i < SAMPLES_PER_SNIPPET; i++)	rs_msgs[Rejected_Snippet_Message_Number]->rs[Overall_Rejected_Count].snippet[i] = spike_pack->snippet[i]; 


	Overall_Rejected_Count++;

	if (Overall_Rejected_Count >= SNIPPETS_PER_MESSAGE)
	{
		Overall_Rejected_Count = 0;
		Rejected_Snippet_Message_Number++;

	}

}

void SendRejectedSnippets()
{
	//printf("rs");
	if (Overall_Rejected_Count == 0)
		Rejected_Snippet_Message_Number--;

	for (int i = 0; i<=Rejected_Snippet_Message_Number; i++)
	{
		// Send the message
		//printf("rs");
		msg.Set( MT_REJECTED_SNIPPET, rs_msgs[i], sizeof(*rs_msgs[i]));
		dragonfly.SendMessage( &msg);
		delete rs_msgs[i];
	}

	Overall_Rejected_Count = 0;
	Rejected_Snippet_Message_Number = 0;

}

void SendLFPs(int nsp_index,double ptime)
{
	//printf("~");
	int buffer_length=0;
	LFPData.GetAndReset(lfpdata, &buffer_length);

	// Fill in the Dragonfly message data struct
	MDF_RAW_CTSDATA sc;
	memset( &sc, 0, sizeof(sc));
	sc.source_index = nsp_index;
	sc.source_timestamp = ptime;

	for( int i = 0; i < ((MAX_SPIKE_CHANS_PER_SOURCE+MAX_ANALOG_CHANS)*LFPSAMPLES_PER_HEARTBEAT); i++)	
	{
		if ( i <= buffer_length)
		{
			sc.data[i] = lfpdata[i];
		}
		else
		{
			sc.data[i] = 0;
		}
	}

	// Send the message
	msg.Set( MT_RAW_CTSDATA, &sc, sizeof(sc));
	dragonfly.SendMessage( &msg);
}

void ProcessSpikePacket(SpikePacket *pack, int nsp_index)
{
	int display_chan = 0;
	int rejectType = 0;

	validFlag = true;
	spikeTime = pack->time;

	//decide if the spike is a primary artifact or if it needs to be checked for validity
	if( (spikeTime + PRETHRESHOLD_SAMPLES*FS - artifactTimer) < BLANK_TIME && (spikeTime + PRETHRESHOLD_SAMPLES*FS - artifactTimer) > 0){
		validFlag = false; //expect incoming spikes to be primary artifact, reject these. 
		rejectType = 1;
	}
	else{ //packet is out of initial blanking range
		if( (spikeTime + PRETHRESHOLD_SAMPLES*FS - artifactTimer) < ARTIFACT_WINDOW_TIME && (spikeTime + PRETHRESHOLD_SAMPLES*FS - artifactTimer) > 0){ //if out of secondary range
			validFlag = checkSnippetValidity((SpikePacket*) pack); //Could be secondary artifact or valid.
			if (!validFlag)
				rejectType = 2;
		}
	}

	if(validFlag)
	{ //if it's a real spike, send it like normal
		SpikePacket *spike_pack = (SpikePacket*) pack;
		if( spike_pack->chan == display_chan)
			printf("\nSpike: chan %.3i unit %i time %.3f\n", spike_pack->chan, spike_pack->unit, spike_pack->time);
		// The spike processor may have additional channels (e.g. 128) but we only care about the ones that are actually hooked up to electrodes (e.g. 96)
		if( spike_pack->chan <= MAX_SPIKE_CHANS_PER_SOURCE) {
			TotalCounter.AddSpike( spike_pack->chan, spike_pack->unit);
			theCounter.AddSpike( spike_pack->chan, spike_pack->unit);
			threshCounter.AddSpike( spike_pack->chan, 0);
		}
		//Send Snippet Data:
		//add to current batch and send when ready
		AddSpikeSnippet(spike_pack,nsp_index,pack->time);
	}
	else   //send the snippets as invalid snippets	
	{	//exact same method as spikes but identified as rejected spikes.
		SpikePacket *reject_pack = (SpikePacket*) pack;
		if( reject_pack->chan == display_chan)
			printf("\nSpike: chan %.3i unit %i time %.3f\n", reject_pack->chan, reject_pack->unit, reject_pack->time);
		// The spike processor may have additional channels (e.g. 128) but we only care about the ones that are actually hooked up to electrodes (e.g. 96)
		if( reject_pack->chan <= MAX_SPIKE_CHANS_PER_SOURCE) {
			TotalRejectCounter.AddSpike( reject_pack->chan, reject_pack->unit);
			theRejectCounter.AddSpike( reject_pack->chan, reject_pack->unit);
			rejectThreshCounter.AddSpike( reject_pack->chan, 0);
		}
		//Send Snippet Data as rejects
		AddRejectedSnippet(reject_pack,nsp_index,pack->time,rejectType);
		printf("\n rejected \n");
	}
}

void checkSpikeQueue(int nsp_index)
{
	while (!stQueue.empty()) {

		// get elapsed time since first spike packet
		LARGE_INTEGER t_now, t_elapsed,t_2;
		QueryPerformanceCounter(&t_now);
		t_elapsed.QuadPart = (t_now.QuadPart - stQueue.front().QuadPart);

		if (t_elapsed.QuadPart < bufferPeriod.QuadPart) // if first spiketime less than buffer delay, return
			return;

		// print number of us spikes are in queue
		/*if (t_elapsed.QuadPart > 1.55*bufferPeriod.QuadPart) {
			t_elapsed.QuadPart *= 1000000;
			t_elapsed.QuadPart /= frequency.QuadPart;
			cout << double(t_elapsed.QuadPart) << endl;
		}*/

		// process first packet
		ProcessSpikePacket(&spikeQueue.front(),nsp_index);

		// delete from Queue
		spikeQueue.pop(); // automatically calls destructor
		stQueue.pop();
	}
}

void clearQueue(int nsp_index)
{
	while (!stQueue.empty()) {
		// process first packet
		ProcessSpikePacket(&spikeQueue.front(),nsp_index);

		// delete from Queue
		spikeQueue.pop(); // automatically calls destructor
		stQueue.pop();
	}
}

void ProcessPacket( Packet *pack, int nsp_index)
{
	//double diff = pack->time - prev_time;
	//prev_time = pack->time;
	//printf("timediff = %.3f ms\n", 1000*diff);

	//printf("Processing Packet: type %i, nbytes %i, time %.3f\n", pack.type, pack.nbytes, pack.time);

	int display_chan = 0;

	switch( pack->type){

		case Packet::TYPE_SPIKE:
		{
		
			// add copy of spike packet to queue buffer
			SpikePacket *sp = (SpikePacket*)pack;
			SpikePacket sp_copy = *sp;
			spikeQueue.push(sp_copy);
			LARGE_INTEGER t_spikePack;
			QueryPerformanceCounter(&t_spikePack);
			stQueue.push(t_spikePack);

			break;	
		
		} //end case
		case Packet::TYPE_WAVEDATA:
		{
			printf("~");
			break;
		}
		case Packet::TYPE_GROUP:
		{
			GroupPacket *wave_pack = (GroupPacket*) pack;
			bool done = LFPData.AddSample(wave_pack->data);
			if (done) //we have enough samples to send onwards
			{
				if (overflow_possible)
					printf("LFP Overflow - Packet Lost\n");
				overflow_possible = true;
			}
			else
			{
				overflow_possible =  false;
			}
			break;
		}

		case Packet::TYPE_HEARTBEAT:
		{
			theCounter.GetAndResetCount( theCount, MAX_TOTAL_SPIKE_CHANS_PER_SOURCE);
			threshCounter.GetAndResetCount( threshCount, MAX_SPIKE_CHANS_PER_SOURCE);

			SendDigEvents(); // send first so that combiner will include in current sample
			SendCounts( pack->time, theCount, MAX_TOTAL_SPIKE_CHANS_PER_SOURCE, nsp_index);
			
			if(collect_LFP){
				SendLFPs(nsp_index, pack->time);
			}
			else{
				int buffer_length=0;
				LFPData.GetAndReset(lfpdata, &buffer_length);
			}

			SendStimSyncEvents();

			if(collect_snippets){
				SendSnippets();
				SendRejectedSnippets();
			}
			else{
				Overall_Spike_Count = 0;
				Snippet_Message_Number= 0;
				Overall_Rejected_Count = 0;
				Rejected_Snippet_Message_Number = 0;

			}	
			
			//printf(".");
			break;
		}
		case Packet::TYPE_STATUS:
		{
			StatusPacket *status_pack = (StatusPacket*) pack;
			double mega_bytes_received = ((double)status_pack->bytesReceived) / (1024.0 * 1024.0);

            if (status_pack->packetsDropped > 0)
                printf("x");
            else
                printf("S");

			TotalCounter.GetAndResetCount( TotalCount, MAX_CEREBUS_TOTAL_UNITS);

			break;
		}
		case Packet::TYPE_DIGITAL:
		{
			DigitalPacket *digital_pack = (DigitalPacket*) pack;
			
			// subtract bits that were already high
			unsigned int data = digital_pack->data[0] & ~prevDigDataRaw;
			prevDigDataRaw = digital_pack->data[0];
			bool stimRelatedEvent = false;
			// handle stim sync events
			if (data & stimSyncMask) { // check if digital event is due to a stim sync pulse
				artifactTimer = pack->time; // set artifact timer
				AddStimSyncEvent(digital_pack,nsp_index,pack->time);
				clearQueue(nsp_index); // buffer can be cleared without further delay

				data = data & ~stimSyncMask; // reset stimSyncBit for remaining comparisons
				stimRelatedEvent = true;
			}
			
			// misc. digital events
			if ((data != prevDigData) && ((digCount > 1) || (!stimRelatedEvent && prevDigDataRaw != prevDigData))){ // this will ignore falling edges of stim related events, but accept all other bit changes
				AddDigitalEvent(digital_pack,nsp_index,pack->time);
			}

			prevDigData = data;
			digCount++;
			
			break;	
		}
	default:
		// Any other types of packets are ignored
		break;
	}
}


// This program takes 3 commandline arguments:
// - IP of network interface that the NSP is connected to
// - Zero-based numeric ID of the NSP (i.e. 0 for the first box, 1 for the second etc)
//   If you specify a string that is not an integer number then it will the default value 0 will be applied
//   This ID will be used in outgoing packets to identify which NSP the information is coming from
// - IP of the Message Manager
// For example, the following command
// SPM_Cerebus 192.168.137.4 3 192.168.2.74
// will connect to the NSP on the network interface 192.168.137.4, it will label
// spike count messages with the ID 3, and will connect to message manager at 192.168.2.74
// If the arguments are omitted, then default values will be applied
int main( int argc, char *argv[])
{
	try {
		// Process command line arguments
		char *nsp_ip = NULL;
		if( argc > 1) {
			nsp_ip = argv[1];
		}
		int nsp_index = 0;
		if( argc > 2) {
			nsp_index = atoi( argv[2]);
		}
		char *mm_ip;
		char default_mm_ip[] = DEFAULT_MM_IP;
		if( argc > 3) {
			mm_ip = argv[3];
		}
		if( argc > 4) {
			collect_snippets = atoi( argv[4]);
		}
		if( argc > 5) {
			collect_LFP = atoi(argv[5]);
		}

		int stimSyncBit = -1; // negative value means disconnected
		int stimParamBit = -1;
		if( argc > 6)
			acceptAllDigEvts = atoi(argv[6]);
		if (argc > 7)
			stimSyncBit = atoi(argv[4]);

		if (stimSyncBit > -1)
			stimSyncMask = (1 << stimSyncBit);
		if (stimParamBit > -1)
			stimParamMask = (1 << stimParamBit);		

		printf("collect LFP: %d\n", collect_LFP);

		printf("Connecting to Dragonfly: ");
		// Connect to Dragonfly
		MODULE_ID mod_id = MID_SPM_MOD1 + nsp_index;
		dragonfly.InitVariables( mod_id, 0);
		dragonfly.ConnectToMMM( mm_ip);
		dragonfly.SendModuleReady();
		printf(" done\n");

		// get frequency for high performance timer
		QueryPerformanceFrequency(&frequency);
		double d_bufferPeriod = bufferDelay * frequency.QuadPart;
		bufferPeriod.QuadPart = (LONGLONG)d_bufferPeriod;

		// Run in a loop, reading UDP messages from Cerebus, sending out spike counts to Dragonfly
		CerebusClient client;
		int loop_count = 0;
		Overall_Spike_Count = 0;
		Snippet_Message_Number = 0;
		Overall_Rejected_Count = 0;
		Rejected_Snippet_Message_Number = 0;
		Dig_Message_Number = 0;
		bool keep_running = true;
		double timeout = 1.0; // in units of seconds
		bool got_packet = false;
		bool cerebus_connected = false;
		while( keep_running) {

			//
			// Connect to Cerebus port (unless already connected)
			//
			if( !cerebus_connected) {
				cerebus_connected = client.SetupConnection( nsp_ip);
				if( !cerebus_connected) {
					printf( "Failed to connect to Cerebus port, will continue trying...\n");
				}
			}

			//
			// Read packet from Cerebus (time out after 1 second
			// to make sure we don't keep waiting if Cerebus goes down)
			//
			if( cerebus_connected) {
				Packet *pack = client.ReadPacket( timeout);
				if( pack) {
					ProcessPacket( pack, nsp_index);
					delete pack;
				} else {
					printf( "Timed out while waiting for packets from Cerebus\n");
					cerebus_connected = false;
				}
			}

			// check spike Queue and process spikes
			checkSpikeQueue(nsp_index);

			//
			// Pause if cerebus not connected
			// because otherwise this program will busy-loop
			//
			if( !cerebus_connected) Sleep( 1000);
		} // end while (keep running) 

		
	} catch(UPipeException &e){
		MyCString trace;
		e.AppendTraceToString( trace);
		std::cout << "UPipeException occurred: " << trace.GetContent() << std::endl;
	} catch(MyCException &e){
		MyCString trace;
		e.AppendTraceToString( trace);
		std::cout << "MyCException occurred: " << trace.GetContent() << std::endl;
	} catch(std::exception &e){
		std::cout << "Exception occurred: " << e.what() << std::endl;
	} catch(...){
		std::cout << "Unknown exception occurred!" << std::endl;
	}
		
}
