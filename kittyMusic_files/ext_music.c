
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#ifdef __linux__
#include <string.h>
#include "os/linux/stuff.h"
#include <retromode.h>
#include <retromode_lib.h>
#endif

#include <amosKittens.h>
#include <amosString.h>
#include "stack.h"

#include "kittyErrors.h"
#include "ext_music.h"
#include "wave.h"
#include "context.h"
#include "debug.h"

#include <proto/ptreplay.h>

#define kittyError instance->kittyError
#define api instance -> api
#define last_var instance -> last_var
#define cmdTmp instance -> cmdTmp

void setEnval(struct wave *wave, int phase, int duration, int volume);

extern struct sampleHeader *allocSample( int size );

uint32 file_size(FILE *fd);
void free_mod( struct context *context );

double noteFreq[12] = {
		261.63,
		277.18,
		293.66,
		311.13,
		329.63,
		349.23,
		369.99,
		392.0,
		415.3,
		440.0,
		466.16,
		493.88
	};


char *musicBell KITTENS_CMD_ARGS
{
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	struct wave *wave;
	struct wave *localwave;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.audioDeviceFlush(0xF);
	getchar();

	wave = getWave( &context -> waves, 1);
	if (wave)
	{
		localwave = allocWave( wave -> id,  wave -> sample.bytes );

		if (localwave)
		{
			int len;

			*localwave = *wave;
			localwave -> bytesPerSecond = wave -> sample.bytes ;

			memcpy( &(localwave->sample.ptr), &(wave -> sample.ptr), wave -> sample.bytes);

			setEnval( localwave, 0, 1, 0 );
			setEnval( localwave, 1, 1, 63 );
			setEnval( localwave, 2, 1, 50);
			setEnval( localwave, 3, 1, 63 );
			setEnval( localwave, 4, 1, 50 );
			setEnval( localwave, 5, 1, 25 );
			setEnval( localwave, 6, 1, 0 );

			localwave->sample = wave->sample;
			localwave->sample.frequency = localwave -> bytesPerSecond;
			len = localwave -> bytesPerSecond * localwave -> envels[6].startDuration;

			api.audioPlayWave( localwave, len, 0xF );

#ifdef debug
			debugDrawWave( localwave );
#endif
			free( localwave );
		}
	}
	else api.setError(22,tokenBuffer);

	return tokenBuffer;
}


char *musicBoom KITTENS_CMD_ARGS
{
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	struct wave *wave;
	struct wave *localwave;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.audioDeviceFlush(0xF);
	getchar();

	wave = getWave(&context -> waves,0);
	if (wave)
	{
		localwave = allocWave( wave -> id,  wave -> sample.bytes );

		if (localwave)
		{
			int len;

			*localwave = *wave;
			localwave -> bytesPerSecond = 50;

			memcpy( &(localwave->sample.ptr), &(wave -> sample.ptr), wave -> sample.bytes);

			setEnval( localwave, 0, 1, 63 );
			setEnval( localwave, 1, 1, 63 );
			setEnval( localwave, 2, 1, 63 );
			setEnval( localwave, 3, 1, 63 );
			setEnval( localwave, 4, 1, 63 );
			setEnval( localwave, 5, 1, 63 );
			setEnval( localwave, 6, 1, 63 );

			localwave->sample = wave->sample;
			localwave->sample.frequency = localwave -> bytesPerSecond;
			len = localwave -> bytesPerSecond * localwave -> envels[6].startDuration;

			api.audioPlayWave( localwave, localwave -> sample.bytes, 0xF );

			free( localwave );
		}
	}
	else api.setError(22,tokenBuffer);

	return tokenBuffer;
}

char *_musicDelWave( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int args =__stack - data->stack +1;
	int waveId;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			waveId = getStackNum( instance,__stack  );
			if (delWave( &context -> waves, waveId)==false)
			{
				api.setError(22,data->tokenBuffer);
			}
			return  NULL ;
			break;

		default:
			popStack( instance, __stack - data->stack );
	}

	api.setError(22,data->tokenBuffer);

	return  NULL ;
}

char *musicDelWave KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicDelWave, tokenBuffer );
	return tokenBuffer;
}

char *musicLedOff KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	instance -> audio_3k3_lowpass = false;
	return tokenBuffer;
}

char *musicLedOn KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	instance -> audio_3k3_lowpass = true;
	return tokenBuffer;
}

char *musicMedCont KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMedLoad KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMedMidiOn KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMedPlay KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMedStop KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMouthHeight KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMouthRead KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMouthWidth KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMubase KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMusic KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef strict_rules_yes
	api.setError(22, tokenBuffer);
#endif
	return tokenBuffer;
}

char *musicMusicOff KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef strict_rules_yes
	api.setError(22, tokenBuffer);
#endif
	return tokenBuffer;
}

char *musicMusicStop KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicMvolume KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicNoiseTo KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_musicPlay( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;

	int pitch,delay;
	int note,octav;

#ifdef show_wave
	int s;
	int x;
	int pixelWidth;
#endif

	int y;
	double freq;
	double r;
	int byteOffset;
	int secOfData;
	int totData;

	double totNumberOfFreq;
	uint8_t	*wavedata;
	struct wave *localwave;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);


#if show_wave
	open_debug_window();
#endif

	switch (args)
	{
		case 2:
			pitch = getStackNum( instance,__stack-1 );
			delay = getStackNum( instance,__stack );

			octav = (pitch-1) / 12;
			note = (pitch-1) % 12;
			freq = noteFreq[ note ] * (double) (1L << octav) / 4;

//			printf( "pitch: %d note: %d octav: %d freq %f\n", pitch, note, octav , freq );

			secOfData = 44800;
			totData = delay * secOfData;
			totNumberOfFreq = freq * delay ;

#if show_wave

			pixelWidth = 700;
			for (s=0;s<delay;s++)
			{
				byteOffset = secOfData * s;
				x = pixelWidth * byteOffset / totData;
				draw_hline( x );
			}
#endif
			localwave = allocWave( 0, totData );
			if (localwave)
			{
				localwave -> bytesPerSecond = secOfData;

				wavedata = &(localwave -> sample.ptr);

				for (byteOffset=0;byteOffset<totData;byteOffset++)
				{
					r =  (double) byteOffset * (2.0 * M_PI * freq) / (double) secOfData;
					y= sin(r)*64.0f;

					wavedata[ byteOffset ] = y;
#ifdef show_wave
					x = pixelWidth * byteOffset / totData;
					WritePixelColor( debug_Window -> RPort, 50+x, 400+y, 0xFFFFFFFF); 
#endif
				}

				setEnval( localwave, 0, 1, 63 );
				setEnval( localwave, 1, 1, 63 );
				setEnval( localwave, 2, 1, 63 );
				setEnval( localwave, 3, 1, 63 );
				setEnval( localwave, 4, 1, 63 );
				setEnval( localwave, 5, 1, 63 );
				setEnval( localwave, 6, 1, 63 );

				localwave->sample.frequency = localwave -> bytesPerSecond;
				localwave -> sample.bytes = totData;

				api.audioDeviceFlush(0x1);
				api.audioPlayWave( localwave, localwave -> sample.bytes, 0x1 );

				free( localwave );
			}


			Delay( delay  );

			break;
		default:
			api.setError(22,data->tokenBuffer);
	}

#if show_wave
	close_debug_window();
#endif

	popStack( instance,__stack - data->stack );

	return  NULL ;
}

char *musicPlay KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicPlay, tokenBuffer );
	return tokenBuffer;
}

char *musicPlayOff KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_musicSamBank( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int args =__stack - data->stack +1;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			context -> sample_bank = getStackNum( instance,__stack );
			break;

		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSamBank KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamBank, tokenBuffer );
	return tokenBuffer;
}

char *_musicSamLoopOff( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			api.audioSetSampleLoop( getStackNum( instance,__stack ), false );
			return  NULL ;

		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSamLoopOff KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamLoopOff, tokenBuffer );
	setStackNum( instance, 0xF ); 	// set default value
	return tokenBuffer;
}

char *_musicSamLoopOn( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			api.audioSetSampleLoop(getStackNum( instance,__stack ), true );
			return  NULL ;

		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSamLoopOn KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamLoopOn, tokenBuffer );
	setStackNum( instance, 0xF ); 	// set default value
	return tokenBuffer;
}

char *_musicSamPlay( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int voices,sample;
	int args =__stack - data->stack +1;
	struct kittyBank *bank;
	uint32_t	*offset;
	struct sampleHeader *sam;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			sample = getStackNum( instance,__stack )-1;
			voices = 0xF;
			break;
		case 2:	// Sam Play 	voices, sample
			voices = getStackNum( instance,__stack-1 );		
			sample = getStackNum( instance,__stack )-1;
			break;
		default:
			api.setError(22,data->tokenBuffer);
			popStack( instance,__stack - data->stack );
			return  NULL ;
	}

	popStack( instance,__stack - data->stack );

	bank = api.findBankById( context -> sample_bank );
	if (bank)
	{
		uint16_t samples = *((uint16_t *) bank -> start);

		if ((sample>=0) && (sample < samples))
		{
			offset = ((uint32_t *) (bank -> start + sizeof( uint16_t )));
			sam = (struct sampleHeader *) ( (uint8_t *) bank -> start + offset[ sample ] );
			api.audioPlay( &sam -> ptr, sam -> bytes, voices, sam -> frequency );
		}
		else api.setError(22,data->tokenBuffer);
	}

	return  NULL ;
}

char *musicSamPlay KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamPlay, tokenBuffer );
	return tokenBuffer;
}

char *_musicSamRaw( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int ret = 0,voice,length, frequency;
	uint8_t *start;
	int args =__stack - data->stack +1;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 4:
			voice = getStackNum( instance,__stack-2 );
			start = (uint8_t *) getStackNum( instance,__stack-2 );
			length = getStackNum( instance,__stack-1 );
			frequency = getStackNum( instance,__stack );
	
			printf("play sound form start: %08x, length %d, frequency %d\n",start,length,frequency);

			if (start)	api.audioPlay( start, length, voice, frequency );

			break;
		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );
	setStackNum( instance, ret );

	return  NULL ;
}

char *musicSamRaw KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamRaw, tokenBuffer );
	return tokenBuffer;
}

char *_musicSamStop( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	int voices;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			voices = getStackNum( instance,__stack );
			api.audioDeviceFlush(voices);
			return NULL;
			break;
	}

	api.setError(22,data->tokenBuffer);
	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSamStop KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSamStop, tokenBuffer );
	setStackNum( instance, 15 );		// set default value.
	return tokenBuffer;
}

char *musicSamSwap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicSamSwapped KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}


char *_musicSample( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int args =__stack - data->stack +1;
	int sample,voices;
	struct kittyBank *bank;
	struct sampleHeader *sam;
	uint32_t	*offset;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 2:
			sample = getStackNum( instance,__stack-1 );
			voices = getStackNum( instance,__stack );

			printf("%d,%d\n",sample, voices);

			bank = api.findBankById( context -> sample_bank );
			if (bank)
			{
				uint16_t samples = *((uint16_t *) bank -> start);

				if ((sample>=0) && (sample < samples))
				{
					offset = ((uint32_t *) (bank -> start + sizeof( uint16_t )));
					sam = (struct sampleHeader *) ( (uint8_t *) bank -> start + offset[ sample ] );
#ifdef obsolete
					copy_sample_to_playback_voices(instance,sam,voices);
#endif
				}
				else api.setError(22,data->tokenBuffer);
			}

			break;
		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );

	return  NULL ;
}

char *musicSample KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSample, tokenBuffer );
	return tokenBuffer;
}

char *musicSay KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_musicSetEnvel( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int args =__stack - data->stack +1;
	int waveId,phase, duration, volume;
	struct wave *wave;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 4:
			waveId = getStackNum( instance,__stack -3  );
			phase = getStackNum( instance,__stack -2 );
			duration = getStackNum( instance,__stack -1 );
			volume = getStackNum( instance,__stack );

			wave = getWave(&context -> waves, waveId);
			setEnval( wave, phase, duration, volume );
			break;
		default:
			api.setError(22,data->tokenBuffer);
			popStack( instance,__stack - data->stack );
			return  NULL ;
			break;
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSetEnvel KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSetEnvel, tokenBuffer );
	return tokenBuffer;
}

char *musicSetTalk KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_musicSetWave( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int args =__stack - data->stack +1;
	unsigned int waveId;
	struct stringData *waveStr;
	struct wave *newWave;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 2:
			waveId = getStackNum( instance,__stack-1  );
			waveStr = getStackString( instance,__stack );

			if (waveStr)
			{
				printf("string length %d\n",waveStr->size);

				delWave( &context -> waves, waveId);

				newWave = allocWave( waveId, waveStr->size );
				if (newWave)
				{
					printf("yes we have a new wave\n");

					memcpy( &newWave -> sample.ptr, &waveStr -> ptr, waveStr->size );
					newWave -> sample.bytes = waveStr->size;
					newWave -> sample.frequency = 44800;
					wavesPushBack( &context -> waves, newWave );
				}
			}
			getchar();

			break;
		default:
			api.setError(22,data->tokenBuffer);
			popStack( instance,__stack - data->stack );
			return  NULL ;
			break;
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSetWave KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSetWave, tokenBuffer );
	return tokenBuffer;
}

char *musicShoot KITTENS_CMD_ARGS
{
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	struct wave *wave;
	struct wave *localwave;
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.audioDeviceFlush(0xF);
	getchar();

	wave = getWave( &context -> waves, 0);
	if (wave)
	{
		localwave = allocWave( wave -> id,  wave -> sample.bytes );

		if (localwave)
		{
			int len;

			*localwave = *wave;
			localwave -> bytesPerSecond = wave -> sample.bytes *4;

			memcpy( &(localwave->sample.ptr), &(wave -> sample.ptr), wave -> sample.bytes);

			setEnval( localwave, 0, 1, 15 );
			setEnval( localwave, 1, 1, 63 );
			setEnval( localwave, 2, 1, 40);
			setEnval( localwave, 3, 1, 40 );
			setEnval( localwave, 4, 1, 30 );
			setEnval( localwave, 5, 1, 15 );
			setEnval( localwave, 6, 1, 0 );

			localwave->sample = wave->sample;
			localwave->sample.frequency = localwave -> bytesPerSecond;
			len = localwave -> bytesPerSecond * localwave -> envels[6].startDuration;

			api.audioPlayWave( localwave, len, 1 );

			free( localwave );
		}
	}
	else api.setError(22,tokenBuffer);

	return tokenBuffer;
}


char *_musicSload( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	int voices;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 3:
			{
				int fileChannel = getStackNum( instance,__stack -2 );
				char *address = (char *) getStackNum( instance,__stack -1 );
				int length = getStackNum( instance,__stack );

				FILE *fd;
				ULONG r;

				if ((fileChannel>0)&&(fileChannel<11))
				{
					fd = instance -> files[fileChannel-1].fd ;
					if (fd) r = fread( address, 1, length, fd );
				}
			}
			break;

		default:
			api.setError(22,data->tokenBuffer);
			break;
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSload KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSload, tokenBuffer );
	return tokenBuffer;
}

char *_musicSsave( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 3:
			{
				int fileChannel = getStackNum( instance,__stack-2 );
				char *start = getStackNum( instance,__stack-1 );
				char *end = getStackNum( instance,__stack );

				FILE *fd;
				ULONG r;

				if ((fileChannel>0)&&(fileChannel<11))
				{
					fd = instance -> files[fileChannel-1].fd ;
					if (fd) r = fwrite( start,1,end - start, fd );
				}
			}
			break;

		default:
			api.setError(22,data->tokenBuffer);
	}

	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicSsave KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicSsave, tokenBuffer );
	return tokenBuffer;
}

char *musicTalkMisc KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicTalkStop KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *musicTempo KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef strict_rules_yes
	api.setError(22, tokenBuffer);
#endif
	return tokenBuffer;
}

char *_musicTrackLoad(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	int args = instance -> stack - data -> stack  +1;
	struct stringData *file_name;
	struct kittyBank *bank = NULL;
	int bank_num = 0;
	int size;
	FILE *fd;

	switch (args)
	{
		case 2:
			file_name = getStackString( instance, instance_stack-1);
			bank_num = getStackNum( instance, instance_stack);
	
			fd = fopen( &file_name -> ptr , "r");
			if (fd)
			{
				size = file_size(fd);
				bank = data -> api.reserveAs( 0, bank_num , size, "Module", NULL );
				if (bank)
				{
					if (bank -> start)
					{
						printf("loaded: %d\n",
							fread( bank -> start,size,1,fd)
							);
					}
				}
				fclose(fd);
			}
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicTrackLoad KITTENS_CMD_ARGS
{
	stackCmdNormal( _musicTrackLoad, tokenBuffer );
	return tokenBuffer;
}

char *musicTrackLoopOf KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef strict_rules_yes
	api.setError(22, tokenBuffer);
#endif
	return tokenBuffer;
}

char *musicTrackLoopOn KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef strict_rules_yes
	api.setError(22, tokenBuffer);
#endif
	return tokenBuffer;
}

char *_musicTrackPlay(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	int args = instance -> stack - data -> stack  +1;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	struct kittyBank *bank = NULL;
	int bank_num = 0;

	switch (args)
	{
		case 1:
			{
				int error = 36;	// default error.

				bank_num = getStackNum( instance, instance_stack);
				bank = data -> api.findBankById( bank_num );
				free_mod( context );

				if (bank) if (bank -> start)
				{
					context -> module = PTSetupMod( bank -> start );
					if (context -> module)
					{
						 PTPlay( context -> module );
						error = 0; // no error found..
					}
				}

				if (error)  api.setError(error, data->tokenBuffer);	// wrong number of args.
			}
			break;

		default:
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicTrackPlay KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicTrackPlay, tokenBuffer );
	return tokenBuffer;
}

char *_musicTrackStop(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance ;
	int args = instance -> stack - data -> stack  +1;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	switch (args)
	{
		case 0:
			if (context -> module) PTStop( context -> module );
			break;

		default:
			printf("setting error: 22\n");
			api.setError(22, data->tokenBuffer);	// wrong number of args.
			popStack( instance, instance_stack - data->stack );
			return NULL;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *musicTrackStop KITTENS_CMD_ARGS
{
	stackCmdNormal( _musicTrackStop, tokenBuffer );
	return tokenBuffer;
}

char *musicVoice KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_musicVolume( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			instance -> volume = (LONG) (( uint32_t) (0x10000 * getStackNum( instance,__stack )) / 63);
			return  NULL ;
			break;
	}

	api.setError(22,data->tokenBuffer);
	popStack( instance,__stack - data->stack );
	return  NULL ;
}

char *musicVolume KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicVolume, tokenBuffer );
	return tokenBuffer;
}

int cVol[4]={63,63,63,63};

char *_musicVumeter( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	int rVol =0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			{
				int channel = getStackNum( instance, instance_stack);

				if ( context -> module)
				{
					int32 pos=PTSongPos( context -> module);
					int32 PatternNum=PTSongPattern( context -> module, pos);
					int32 rowNum = PTPatternPos( context -> module );
					char *RowData=PTPatternData( context -> module, PatternNum, rowNum);

					if (RowData)
					{
						char *cData = RowData + (channel << 2);
						//cmd = CData[1];
						rVol = cData[0] ? cVol[ channel ] : 0;		// check if we have a instrument...
					}
				}
			}
			break;

		default:

			api.setError(22,data->tokenBuffer);
			break;
	}

	popStack( instance,__stack - data->stack );

//	rVol = 63;

	setStackNum( instance, rVol);
	return  NULL ;
}

char *musicVumeter KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _musicVumeter, tokenBuffer );
	return tokenBuffer;
}


char *_musicWave( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args =__stack - data->stack +1;
	int waveId,voices;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 2:
			waveId = getStackNum( instance,__stack-1  );
			voices = getStackNum( instance,__stack );

#ifdef obsolete
			if ( apply_wave( waveId,  voices)  == false)
			{
				api.setError(178,data->tokenBuffer);
			}
#endif
			popStack( instance,__stack - data->stack  );
			return  NULL;

		default:
			api.setError(22,data->tokenBuffer);
			popStack( instance,__stack - data->stack  );
			return  NULL ;
	}

	popStack( instance,__stack - data->stack  );
	return  NULL ;
}

char *musicWave KITTENS_CMD_ARGS
{
	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _musicWave, tokenBuffer );
	return tokenBuffer;
}

uint32 file_size(FILE *fd)
{
	uint32 size;
	fseek(fd , 0, SEEK_END );			
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET );
	return size;
}

void free_mod( struct context *context )
{
	if ( context -> module )
	{
		PTStop( context -> module );
		Delay(2);	// dangures!!!
		PTFreeMod(context -> module );
		context -> module = NULL;
	}
}
