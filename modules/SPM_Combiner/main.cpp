//////////////////////////////////////////////////////////////////////////////////
//
// This implements the SPM_Combiner module that combines the raw spike counts from 
// a bunch of separate spike sources (such as separate acquisition boxes into one
// spike count sample that is sent out. The raw counts can be more frequent (e.g.
// once per 10 ms) than the output counts (e.g. once per 30 ms).
 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dragonfly.h"
#include "vr_config.h"

//static RTMA_Module rtma( MID_TEST_MOD, 0);
static Dragonfly_Module dragonfly( MID_TEST_MOD, 0);
static CMessage SpikeCountMessage( MT_SPM_SPIKECOUNT);
static CMessage SampleGeneratedMessage( MT_SAMPLE_GENERATED);
static CMessage PingAckMessage( MT_PING_ACK);
static MDF_SAMPLE_GENERATED *SampleGeneratedData;
static int SampleNo = 0;
static double LatestSourceTimestamp = 0.0;
static double RawCountInterval = 0;
static int SourceCount[MAX_SPIKE_SOURCES]; // Counts how many messages have been received from each source
static bool ActiveSources[MAX_SPIKE_SOURCES]; // Keeps track of which sources are active


void Initialize( void)
{
  // Initialize fixed message objects for frequently sent messages
  SpikeCountMessage.AllocateData( sizeof(MDF_SPM_SPIKECOUNT));
  SampleGeneratedMessage.AllocateData( sizeof(MDF_SAMPLE_GENERATED));
  PingAckMessage.AllocateData( sizeof(MDF_PING_ACK));
  SampleGeneratedData = (MDF_SAMPLE_GENERATED*) SampleGeneratedMessage.GetDataPointer();

  // Initialize sample number and source timestamp
  SampleNo = 2;     // 0 is invalid, 1 will mess up data_loader, so start at 2
  LatestSourceTimestamp = 0.0;
}

void PrintRawCount( MDF_RAW_SPIKECOUNT *rc)
{
  //fprintf(stdout,"%.3f\n", rc->source_timestamp);
  for( int u = 0; u < MAX_UNITS_PER_CHAN; u++) {
    for( int c = 0; c < MAX_SPIKE_CHANS_PER_SOURCE; c++) {
      int linear_unit_index = c * MAX_UNITS_PER_CHAN + u;
      int count = rc->counts[linear_unit_index];
      fprintf(stdout,"%2d", count);
    }
    fprintf(stdout,"\n");
  }
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
}

void PrintCount( MDF_SPM_SPIKECOUNT *sc)
{
  for( int u = 0; u < MAX_UNITS_PER_CHAN; u++) {
    for( int s = 0; s < MAX_SPIKE_SOURCES; s++) {
      for( int c = 0; c < MAX_SPIKE_CHANS_PER_SOURCE; c++) {
		int linear_unit_index = s * MAX_SPIKE_CHANS_PER_SOURCE*MAX_UNITS_PER_CHAN + c * MAX_UNITS_PER_CHAN + u;
		int count = sc->counts[linear_unit_index];
		fprintf(stdout,"%1d", count);
      }
      fprintf(stdout," ");
    }
    fprintf(stdout,"\n");
  }
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n");
}

// Resets the counts to zero
void ResetCount( void)
{
  MDF_SPM_SPIKECOUNT *sc = (MDF_SPM_SPIKECOUNT*) SpikeCountMessage.GetDataPointer();
  memset(sc,0,sizeof(MDF_SPM_SPIKECOUNT));
  for( int i = 0; i < MAX_SPIKE_SOURCES; i++) SourceCount[i] = 0;
}

// Adds the raw count rc to the output count sc
void AddCount( MDF_RAW_SPIKECOUNT *rc)
{
  MDF_SPM_SPIKECOUNT *sc = (MDF_SPM_SPIKECOUNT*) SpikeCountMessage.GetDataPointer();

  // Add the counts from this raw count message into the big outgoing count message
  int source_offset = rc->source_index * MAX_TOTAL_SPIKE_CHANS_PER_SOURCE;
  for( int i = 0; i < MAX_TOTAL_SPIKE_CHANS_PER_SOURCE; i++) {
    sc->counts[source_offset+i] += rc->counts[i];
  }

  // Keep track of how many messages have been received from each source
  SourceCount[rc->source_index]++;

  // Keep track of source timestamp of latest data added to the count and keep track of raw count interval
  LatestSourceTimestamp = rc->source_timestamp;
  RawCountInterval = rc->count_interval;
}

// Reset the checking for whether each source is active
void ResetActiveSources( void)
{
  for( int i = 0; i < MAX_SPIKE_SOURCES; i++) {
    ActiveSources[i] = true;      // start by assuming all sources are active
  }
}

// Update the list of which sources are active
void UpdateActiveSources( void)
{
  for( int i = 0; i < MAX_SPIKE_SOURCES; i++) {
    // Sources that have sent exactly the expected number of messages since last sample
    // generation are considered the good active sources
    if( SourceCount[i] == RAW_COUNTS_PER_SAMPLE) ActiveSources[i] = true;

    // Sources that have have sent less than the expected counts since last sample generation are 
    // considered inactive
    if( SourceCount[i] < RAW_COUNTS_PER_SAMPLE) ActiveSources[i] = false;

    // If a source has sent more than the expected counts, then we do not change its status
  }  
}

// Look at how many samples have been received from this source
// and if the incoming sample would be one too many, then this 
// data does not belong in the current sample
bool IncomingDataBelongsInNextSample( int incoming_source_id)
{
  bool source_is_active = ActiveSources[incoming_source_id];
  bool source_has_sent_more_than_enough = SourceCount[incoming_source_id] >= RAW_COUNTS_PER_SAMPLE;
  if( source_is_active && source_has_sent_more_than_enough) return true;
  else return false;
}

// Look at whether enough samples have been received from each active source
bool EnoughDataForSample( void)
{
  for( int i = 0; i < MAX_SPIKE_SOURCES; i++) {
    bool this_source_is_active = ActiveSources[i];
    bool enough_counts_from_this_source = (SourceCount[i] >= RAW_COUNTS_PER_SAMPLE);
    if( this_source_is_active && !enough_counts_from_this_source) return false;
  }
  return true;
}

void GenerateSample( void)
{
  // Increment sample no
  SampleNo++;

  // Fill in spikecount header, assume spike count itself has already been filled, and send it
  MDF_SPM_SPIKECOUNT *sc = (MDF_SPM_SPIKECOUNT*) SpikeCountMessage.GetDataPointer();
  sc->sample_header.DeltaTime = ((double)0.020);
  sc->sample_header.SerialNo = SampleNo;
  sc->sample_header.Flags = 0;
  sc->source_timestamp = LatestSourceTimestamp;
  sc->count_interval = RawCountInterval * ((double)RAW_COUNTS_PER_SAMPLE);
  dragonfly.SendMessage( &SpikeCountMessage);

  MDF_SAMPLE_GENERATED *sg = (MDF_SAMPLE_GENERATED*) SampleGeneratedMessage.GetDataPointer();
  //MDF_SAMPLE_GENERATED sgd;
  //MDF_SAMPLE_GENERATED *sg = &sgd;
  sg->sample_header.DeltaTime = ((double)0.020);
  sg->sample_header.SerialNo = SampleNo;
  sg->sample_header.Flags = 0;
  sg->source_timestamp = LatestSourceTimestamp;
  //SampleGeneratedMessage.SetData( sg, sizeof(MDF_SAMPLE_GENERATED));
  dragonfly.SendMessage( &SampleGeneratedMessage);


  // Update list of active sources
  UpdateActiveSources();

  // Reset count
  ResetCount();

  //PrintCount( SpikeCountData);
}

void ProcessRawCount( MDF_RAW_SPIKECOUNT *rc)
{
  //PrintRawCount( rc);

  // Check that the source index is within defined range. If it is not, then ignore it,
  // and return without further processing
  if( rc->source_index < 0) {
    fprintf(stderr,"Source index < 0 !!! This should never happen !!!\n");
    return;
  }
  if( rc->source_index >= MAX_SPIKE_SOURCES) {
    fprintf(stderr,"Source index exceeds maximum number of defined spike sources!\n");
    return;
  }

  //
  // Aggregate counts from N consecutive raw counts across all active 
  // sources to make a spike count sample
  //
  if( IncomingDataBelongsInNextSample( rc->source_index)) GenerateSample();

  AddCount( rc);

  if( EnoughDataForSample()) GenerateSample();
}

//bool ProcessMessage(RTMA_Module *rtma, CMessage *M)
bool ProcessMessage(Dragonfly_Module *dragonfly, CMessage *M)
{
  bool keep_running = true;
  switch( M->msg_type) {
  case MT_RAW_SPIKECOUNT:
    {
      MDF_RAW_SPIKECOUNT *rc = (MDF_RAW_SPIKECOUNT*) M->GetDataPointer();
      ProcessRawCount( rc);
      //fprintf(stdout,".");
      break;
    }
  case MT_EXIT:
    {
        if ((M->dest_mod_id == 0) || (M->dest_mod_id == dragonfly->GetModuleID()))
        {
            fprintf(stdout,"got exit!\n");
            dragonfly->SendSignal(MT_EXIT_ACK);
            dragonfly->DisconnectFromMMM();
            keep_running = false;
        }
        break;
    }
  case MT_PING:
    {
      char MODULE_NAME[] = "SPM_Combiner";
      MDF_PING *pg = (MDF_PING *) M->GetDataPointer();
      if ( (strcmp(pg->module_name, MODULE_NAME) == 0) || 
           (strcmp(pg->module_name, "*") == 0) ||
           (M->dest_mod_id == dragonfly->GetModuleID()) )
      {
        MDF_PING_ACK *pa = (MDF_PING_ACK *) PingAckMessage.GetDataPointer();
        
        memset(pa,0,sizeof(MDF_PING_ACK));        
        for (int i = 0; i < strlen(MODULE_NAME); i++)
        {
          pa->module_name[i] = MODULE_NAME[i];
        }

        dragonfly->SendMessage( &PingAckMessage);
      }
      
      break;
    }
  }
  fflush(stdout);
  return keep_running;
}

void SendData(int message_type, void *data, unsigned data_size)
{
  static CMessage M;
  M.Set(message_type, data, data_size);
  dragonfly.SendMessage(&M);
}

int main(int argc, char *argv[])
{
  // Process command line arguments
  char *config_filename = NULL;
  if( argc > 1) {
	config_filename = argv[1];
  }
  char *mm_ip = NULL;
  if( argc > 2) {
	mm_ip = argv[2];
  }

  static CMessage inMsg;

  Initialize();

  bool try_again = true;
  while(try_again) {
    
    try {	
      fprintf(stdout, "Connecting to Dragonfly\n");
	  if( mm_ip == NULL) dragonfly.ConnectToMMM();
	  else dragonfly.ConnectToMMM(mm_ip);
      dragonfly.Subscribe(MT_EXIT);
      dragonfly.Subscribe(MT_PING);
      dragonfly.Subscribe(MT_RAW_SPIKECOUNT);
      dragonfly.SendModuleReady();
      fprintf(stdout, "Connected to Dragonfly\n");
      ResetCount();
      ResetActiveSources();
      bool keep_running = true;
      while(keep_running) {
		double timeout = .5; // seconds
		bool got_msg = dragonfly.ReadMessage( &inMsg, timeout);
		if( got_msg) {
		  keep_running = ProcessMessage(&dragonfly, &inMsg);
		  if( !keep_running) {
			try_again = false;
			break;
		  }
		} else {
		  //fprintf(stdout, "Waiting for messages\n");
		}
      }
    }
    catch(UPipeClosedException) {
      fprintf(stderr, "Reconnecting to Dragonfly\n");
      Sleep(500); // milliseconds
    }
    catch(UPipeException) {
      fprintf(stderr, "Cannot connect to Dragonfly, waiting to reconnect\n");
      Sleep(500); // milliseconds
    }
  } 
}
