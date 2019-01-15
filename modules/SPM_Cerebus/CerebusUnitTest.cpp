#include <stdio.h>
#include <sstream>
#include <iostream>
#include "CerebusClient.h"
/* Test program specs

tests to do:
* is port openable?
* do I get HEARTBEAT packets?
* do I get spike packets?

Potential future tests:
* do I get sorted spikes? UIDs>0

output to stdout name:value pairs
*/

int main( int argc, char *argv[])
{
	try {
		CerebusClient client;
		int heartbeat_count = 0;
		int spike_packet_count = 0;
		bool keep_running = true;
		double timeout = 1.0; // in units of seconds
		bool got_packet = false;
		bool cerebus_connected = false;

		//
		// Connect to Cerebus port (unless already connected)
		//	
		cerebus_connected = client.SetupConnection();
		while( cerebus_connected && keep_running) {
			//
			// Read packet from Cerebus (time out after 1 second
			// to make sure we don't keep waiting if Cerebus goes down)
			//
			Packet *pack = client.ReadPacket( timeout);
			if( pack) {
				switch (pack->type) {
					case Packet::TYPE_HEARTBEAT:
						heartbeat_count++;
						break;
					case Packet::TYPE_SPIKE:
						spike_packet_count++;
						break;
				}
				delete pack;
			} else {
				// timed out
				keep_running = false;
			}

			//
			// Quit after receiving one heartbeat and one spike packet
			// or after 100 heartbeats
			//
			if ((heartbeat_count > 0) && (spike_packet_count > 0)) {
				keep_running = false;
			} else if (heartbeat_count > 100) {
				keep_running = false;
			}
		}

		//
		// Print output in a user and machine -friendly format
		//
		printf( "%12s : %s\n", "portopen", (cerebus_connected) ? "pass" : "FAIL");
		printf( "%12s : %s\n", "heartbeats", (heartbeat_count > 0) ? "pass" : "FAIL");
		printf( "%12s : %s\n", "spikepackets", (spike_packet_count > 0) ? "pass" : "FAIL");
		printf( "%12s : pass\n", "exceptions");
	} catch(...){
		printf( "%12s : FAIL\n", "portopen");
		printf( "%12s : FAIL\n", "heartbeats");
		printf( "%12s : FAIL\n", "spikepackets");
		printf( "%12s : FAIL\n", "exceptions");
		// std::cout << "Exception occurred: " << e.what();
	}
}
