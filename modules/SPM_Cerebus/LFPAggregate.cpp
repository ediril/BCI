#include "LFPAggregate.h"


LFPAggregate::
LFPAggregate( int maxchannels, int maxtimesteps)
{
	_maxChannels = maxchannels;
	_maxTimeSteps = maxtimesteps;
	_data = new short[_maxTimeSteps*_maxChannels];
	
	Reset( );
}

LFPAggregate::
~LFPAggregate(void)
{
	delete [] _data;
}


void
LFPAggregate::
Reset( void)
{
	for( int i = 0; i < _maxChannels; i++) 
	{
		for( int ii = 0; ii < _maxTimeSteps; ii++)
			_data[_maxChannels*(ii) + i] = 0;
	}
	_TimeIdx = 0;
}

bool
LFPAggregate::
AddSample( short* data)
{
	for (int i = 0; i<_maxChannels; i++)
		_data[_maxChannels*_TimeIdx+i] = data[i];

	_TimeIdx++;

	return _TimeIdx == _maxTimeSteps;
}

void
LFPAggregate::
GetAndReset( short *buffer , int* buffer_length)
{
	*buffer_length = _maxTimeSteps*_maxChannels;

	for( int i = 0; i < _maxChannels; i++) 
	{
		for( int ii = 0; ii < _maxTimeSteps; ii++)
		{
			buffer[_maxChannels*ii+i] = _data[_maxChannels*ii+i];
			_data[_maxChannels*ii+i] = 0;
		}
	}
	_TimeIdx = 0;
}
