
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <proto/exec.h>
#include <proto/retroMode.h>
#include <amosKittens.h>

#include "wave.h"

extern void copy_sample_to_playback_voices(struct KittyInstance *instance, struct sampleHeader *sam, int voices);

void make_wave_test(struct waves *waves)
{
	int bytes = 30;
	unsigned int n;
	struct wave *newWave = allocWave(999, bytes);

	newWave->sample.bytes = bytes;

	if (newWave)
	{
		for (n = 0; n<newWave->sample.bytes; n++)
		{
			(&newWave->sample.ptr)[n] = (uint8_t)(sin((float)n * M_PI * 2 / (float)newWave->sample.bytes) * 126 + 127);
		}

		newWave->sample.frequency = newWave->sample.bytes;	// sample rate

		wavesPushBack(waves, newWave);
	}
}


void make_wave_noice(struct waves *waves)
{
	int n;
	struct wave *newWave = allocWave( 0, 256 );

	if (newWave)
	{
		for (n=0;n<256;n++)
		{
			(&newWave -> sample.ptr)[n] = rand() % 256;
		}

		newWave -> sample.bytes = 256;
		newWave -> sample.frequency = 44800/8;

		wavesPushBack(waves,newWave);
	}
}

struct sampleHeader *allocSample( int size )
{
	size =  sizeof(struct sampleHeader) + size -1;
	return (struct sampleHeader *) malloc( size );
}

void setEnval(struct wave *wave, int phase, int duration, int volume)
{
	int n;
	int startDuration = 0;
	if ((wave)&&(phase>-1)&&(phase<7))
	{
		for (n = 0; n < phase; n++) startDuration += wave->envels[n].duration;

		wave -> envels[phase].volume = volume;
		wave -> envels[phase].startDuration = startDuration;
		wave -> envels[phase].duration = duration;
	}
}

bool apply_wave(struct KittyInstance *instance,struct waves *waves, int waveId, int voices)
{
	struct wave *wave = getWave(waves,waveId);
	if (wave)
	{
		copy_sample_to_playback_voices( instance, &(wave -> sample),voices);
		return true;
	}
	return false;
}

void copy_sample_to_playback_voices(struct KittyInstance *instance, struct sampleHeader *sam, int voices)
{
	int n;
	int size;

	printf("sam -> bytes: %d\n", sam -> bytes);

	for (n=0;n<4;n++)
	{
		if (voices & (1<<n))
		{
			if (instance -> voicePlay[n]) free( instance -> voicePlay[n]);
			instance -> voicePlay[n]= allocSample( sam -> bytes );

			if (instance -> voicePlay[n])
			{
				size =  sizeof(struct sampleHeader) + sam -> bytes -1;
				memcpy( instance -> voicePlay[n] , sam, size );
			}
		}	
	}
}
