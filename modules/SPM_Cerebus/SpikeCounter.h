#ifndef SPIKE_COUNTER_H
#define SPIKE_COUNTER_H

#include <vector>

class SpikeCounter
{
public:
	// default constructor
	SpikeCounter( int maxchannels, int maxunits);
	~SpikeCounter( void);

	void AddSpike( int channel, int unit);
	void GetAndResetCount( int *buffer, int buffer_length);
	void GetAndResetCount( unsigned char *buffer, int buffer_length);
	
protected:
	int _maxChannels;
	int _maxUnits;
	int *_count;

	int unitIndex( int channel, int unit);
	void ResetCount( void);
};


#endif //SPIKE_COUNTER_H
