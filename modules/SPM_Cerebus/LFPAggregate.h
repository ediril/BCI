#pragma once

class LFPAggregate
{
public:
	LFPAggregate(int maxchannels, int maxtimesteps);
	~LFPAggregate(void);

	bool AddSample( short* data);
	void GetAndReset( short *buffer, int* buffer_length);
	
protected:
	int _maxChannels;
	int _maxTimeSteps;
	short *_data;
	int _TimeIdx;

	void Reset( void);

};
