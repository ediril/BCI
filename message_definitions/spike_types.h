#ifndef _SPIKE_TYPES_H_
#define _SPIKE_TYPES_H_

#include "common_defs.h"

#define MAX_SPIKE_SOURCES                 3
#define MAX_SPIKE_CHANS_PER_SOURCE       96
#define MAX_UNITS_PER_CHAN                6 // Units 1..5 are sorted, Unit 0 is unsorted threshold crossings (not including the sorted units)
#define MAX_TOTAL_SPIKE_CHANS_PER_SOURCE  (MAX_SPIKE_CHANS_PER_SOURCE * MAX_UNITS_PER_CHAN)
#define MAX_TOTAL_SPIKE_CHANS             (MAX_SPIKE_SOURCES * MAX_TOTAL_SPIKE_CHANS_PER_SOURCE)

#define RAW_COUNTS_PER_SAMPLE            2
#define MSEC_PER_RAW_SAMPLE              10
#define SAMPLE_DT                        (RAW_COUNTS_PER_SAMPLE * MSEC_PER_RAW_SAMPLE) * 0.001

typedef struct {
  int source_index;    // a zero-based index in the range 0..(N-1) for N spike sources (e.g. separate acquisition boxes)
  int reserved;        // for 64-bit alignment
  double source_timestamp;// [seconds]source timestamp of the event that caused this count to happen
  double count_interval;  // [seconds]time interval over which this count was integrated
  unsigned char counts[MAX_TOTAL_SPIKE_CHANS_PER_SOURCE];
} MDF_RAW_SPIKECOUNT;

typedef unsigned char SPIKE_COUNT_DATA_TYPE;
typedef struct {
  SAMPLE_HEADER sample_header;
  double source_timestamp;// [seconds] source timestamp of the event that caused this count to happen
  double count_interval;  // [seconds]
  SPIKE_COUNT_DATA_TYPE counts[MAX_TOTAL_SPIKE_CHANS];
} MDF_SPM_SPIKECOUNT;
typedef struct {
  SAMPLE_HEADER sample_header;
  double source_timestamp;// [seconds]source timestamp of the pulse that caused this count to happen
} MDF_SAMPLE_GENERATED;

typedef struct{
  double       sample_response_timestamp;
  double       sample_alignment_timestamp;
  unsigned int sample_response_count;
  unsigned int sample_alignment_count;
} MDF_SAMPLE_RESPONSE;

#endif //_SPIKE_TYPES_H_
