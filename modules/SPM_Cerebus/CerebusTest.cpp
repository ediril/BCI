#include <stdio.h>
#include <sstream>
#include <iostream>
#include "CerebusClient.h"
#include "SpikeCounter.h"

void ProcessPacket( Packet *pack); // defined below

#ifndef _UNIX_C
	//Global counter frequency value- used by GetAbsTime() on Windows
	double win_counter_freq;
#endif

double
GetAbsTime( void)
//WIN: returns a seconds timestamp from a system counter
{
#ifdef _UNIX_C
		struct timeval tim;
		if ( gettimeofday(&tim, NULL)  == 0 )
		{
			double t = tim.tv_sec + (tim.tv_usec/1000000.0);
			return t;
		}else{
			return 0.0;
		}
#else
		LONGLONG current_time;
		QueryPerformanceCounter( (LARGE_INTEGER*) &current_time);
		return (double) current_time / win_counter_freq;
#endif
}


int main( int argc, char *argv[])
{
	#ifndef _UNIX_C
		LONGLONG freq;
		QueryPerformanceFrequency( (LARGE_INTEGER*) &freq);
		win_counter_freq = (double) freq;
	#endif

	try {
		CerebusClient client;
		int loop_count = 0;
		bool keep_running = true;
		double timeout = 1.0; // in units of seconds
		bool got_packet = false;
		bool cerebus_connected = false;
		while( keep_running) {

			//
			// Connect to Cerebus port (unless already connected)
			//
			if( !cerebus_connected) {
				cerebus_connected = client.SetupConnection("192.168.137.4");
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
					ProcessPacket( pack);
					delete pack;
				} else {
					printf( "Timed out while waiting for packets from Cerebus\n");
					cerebus_connected = false;
				}
			}

			//
			// Pause if cerebus not connected
			// because otherwise this program will busy-loop
			//
			if( !cerebus_connected) Sleep( 1000);

			//if( ++loop_count >= 100) keep_running = false;
		}
	} catch(std::exception &e){
		std::cout << "Exception occurred: " << e.what();
	}
}

#define MAX_CHANNELS  96
#define MAX_UNITS     5
#define MAX_TOTAL_UNITS (MAX_CHANNELS*MAX_UNITS)
SpikeCounter Counter( MAX_CHANNELS, MAX_UNITS);
SpikeCounter counter( MAX_CHANNELS, MAX_UNITS);
SpikeCounter threshCounter( MAX_CHANNELS, 1);
int TheCount[MAX_TOTAL_UNITS];
unsigned char theCount[MAX_TOTAL_UNITS];
unsigned char threshCount[MAX_CHANNELS];
//double prev_time = 0;

void ProcessPacket( Packet *pack)
{
	//double diff = pack->time - prev_time;
	//prev_time = pack->time;
	//printf("timediff = %.3f ms\n", 1000*diff);

	//printf("Processing Packet: type %i, nbytes %i, time %.3f\n", pack->type, pack->nbytes, pack->time);
	
	int display_chan = 1;

	switch( pack->type){

		case Packet::TYPE_SPIKE:
		{
			SpikePacket *spike_pack = (SpikePacket*) pack;
			//if( spike_pack->chan == display_chan)
			//	printf("\nSpike: chan %.3i unit %i time %.3f\n", spike_pack->chan, spike_pack->unit, spike_pack->time);
			//printf("|");
			// The spike processor may have additional channels (e.g. 128) but we only care about the ones that are actually hooked up to electrodes (e.g. 96)
			if( spike_pack->chan <= MAX_CHANNELS) {
				Counter.AddSpike( spike_pack->chan, spike_pack->unit);
				counter.AddSpike( spike_pack->chan, spike_pack->unit);
				threshCounter.AddSpike( spike_pack->chan, 0);
			}
			break;
		}
		case Packet::TYPE_WAVEDATA:
		{
			printf("~");
			break;
		}
		case Packet::TYPE_GROUP:
		{
			printf("G");
			break;
		}
		case Packet::TYPE_HEARTBEAT:
		{
			double time = GetAbsTime();
			printf("%.3f\n", time);
			//printf(".");
			counter.GetAndResetCount( theCount, MAX_TOTAL_UNITS);
			//threshCounter.GetAndResetCount( 
			//for( int j = 0; j < MAX_UNITS; j++) printf("%i", 
			break;
		}
		case Packet::TYPE_STATUS:
		{
			//printf("S");
			StatusPacket *status_pack = (StatusPacket*) pack;
			double mega_bytes_received = ((double)status_pack->bytesReceived) / (1024.0 * 1024.0);
			//printf("\nProtocol Status: received %i packets (%.3f MB), dropped %i packets", status_pack->packetsReceived, mega_bytes_received, status_pack->packetsDropped);
			//Print out number of spike packets and number of wave packets received since last status update
			Counter.GetAndResetCount( TheCount, MAX_TOTAL_UNITS);
			
			break;
		}
		default:
			// Any other types of packets are ignored
			//printf("U");
			//printf("\nUndefined packet: type %i, nbytes %i, time %.3f\n", pack->type, pack->nbytes, pack->time);
			break;
	}
}
