#include "SpikeCounter.h"
#include <iostream>

SpikeCounter::
SpikeCounter( int maxchannels, int maxunits)
{
	_maxChannels = maxchannels;
	_maxUnits = maxunits;
	int total_units = maxchannels * maxunits;
	_count = new int[total_units];

	ResetCount( );
}

SpikeCounter::
~SpikeCounter(void)
{
	delete [] _count;
}

inline
int
SpikeCounter::
unitIndex( int channel, int unit)
{
	// a quick check
	if( channel < 1)
	{
		throw std::exception("SpikeCounter::unitIndex(): Channel number is less than 1");
	}
	if( channel > _maxChannels)
	{
			throw std::exception("SpikeCounter::unitIndex(): Channel number exceeds max");
	}
	if( unit > _maxUnits-1)
	{
		if( channel != 255)
		{
			printf("WHAAA  %d  %d  %d\n", unit, channel, _maxUnits); 
			throw std::exception("SpikeCounter::unitIndex(): Unit number exceeds max\n");
		}
	}

	return (channel-1)*_maxUnits + unit;
}

void
SpikeCounter::
ResetCount( void)
{
	int total_units = _maxChannels * _maxUnits;
	for( int i = 0; i < total_units; i++) _count[i] = 0;
}

void
SpikeCounter::
AddSpike( int channel, int unit)
{
	int unit_index = unitIndex( channel, unit);
	_count[unit_index]++;
}

void
SpikeCounter::
GetAndResetCount( int *buffer, int buffer_length)
{
	int total_units = _maxChannels * _maxUnits;
	if( buffer_length < total_units) throw std::exception("SpikeCounter::GetAndResetCount: buffer is not big enough");
	for( int i = 0; i < total_units; i++) {
		buffer[i] = _count[i];
		_count[i] = 0;
	}
}

void 
SpikeCounter::
GetAndResetCount( unsigned char *buffer, int buffer_length)
{
	int total_units = _maxChannels * _maxUnits;
	if( buffer_length < total_units) throw std::exception("SpikeCounter::GetAndResetCount: buffer is not big enough");
	for( int i = 0; i < total_units; i++) {
		int count = _count[i];
		buffer[i] = (count <= 255) ? count : 255;
		_count[i] = 0;
	}
}
