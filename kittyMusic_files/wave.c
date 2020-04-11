
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <stdbool.h>
#include <string.h>
#include <proto/dos.h>
#include <math.h>

#include <proto/retroMode.h>
#include <amosKittens.h>

#include "wave.h"

#define harmonic(h,n,m) h * ((double) n) * 2.0f * M_PI / ((double) m) ;


struct wave *allocWave( int id, int size )
{
	struct wave *data;

	size =  sizeof(struct wave) + size -1;
	data = (struct wave *) malloc( size );

	if (data)
	{
		data -> id = id;
	}

	return data;
}

bool delWave( struct waves *waves, int id )
{
	unsigned int n;

	for (n=0;n<waves -> used;n++)
	{
		if (waves -> items[n] -> id == id )
		{
			free(waves -> items[n]);
			wavesRemove( waves, n );
			return true ;
		}
	}
	return false;
}

void make_wave_bell(struct waves *waves)
{
	int n;
	double r1,r3,r5;
	int bytes = 256;
	struct wave *newWave = allocWave( 1, bytes );
	char *data;

	r1 = 0x0f;
	r3 = M_PI ;
	r5 = 0.0f;

	if (newWave)
	{

		data = ( char *) &(newWave -> sample.ptr);

		for (n=0;n<bytes;n++)
		{

//			data[n] =  (signed char) ( (sin( r1 ) + sin( r3 ) ) /2.0 * 127.0)  ;
//			data[n] =  (signed char) ( (sin( r1 ) + sin( r3 ) + sin( r5)) /3.0 * 127.0)  ;
			r1=harmonic(1,n,bytes);
//			r3=harmonic(3,n,bytes) + M_PI;
//			r5=harmonic(5,n,bytes);

			data[n] =  (signed char) ( sin( r1 ) * 127.0)  +127;
		}

		newWave -> sample.bytes = bytes;
		newWave -> sample.frequency = bytes;

		wavesPushBack(waves,newWave);
	}
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

struct wave *getWave(struct waves *waves, int id)
{
	unsigned int n;

	for (n=0;n<waves -> used;n++)
	{
		if (waves -> items[n] -> id == id )
		{
			return waves -> items[n] ;
		}
	}
	return NULL;
}


