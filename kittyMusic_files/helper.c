
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

#ifdef obsolete

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


#endif

#ifdef debug_waves_yes

void open_debug_window()
{
#define IDCMP_COMMON IDCMP_MOUSEBUTTONS | IDCMP_INACTIVEWINDOW | IDCMP_ACTIVEWINDOW  | \
	IDCMP_CHANGEWINDOW | IDCMP_MOUSEMOVE | IDCMP_REFRESHWINDOW | IDCMP_RAWKEY | \
	IDCMP_EXTENDEDMOUSE | IDCMP_CLOSEWINDOW | IDCMP_NEWSIZE | IDCMP_INTUITICKS | IDCMP_MENUPICK | IDCMP_GADGETUP

	debug_Window = OpenWindowTags( NULL,
				WA_Left,			820,
				WA_Top,			20,
				WA_InnerWidth,		800,
				WA_InnerHeight,	800,
				WA_SimpleRefresh,	TRUE,
				WA_CloseGadget,	FALSE,
				WA_DepthGadget,	TRUE,
				WA_DragBar,		TRUE,
				WA_Borderless,	FALSE,
				WA_SizeGadget,	FALSE,
				WA_SizeBBottom,	TRUE,
				WA_NewLookMenus,	TRUE,
				WA_Title, "Debug Window",
				WA_Activate,        TRUE,
				WA_Flags, WFLG_RMBTRAP| WFLG_REPORTMOUSE,
				WA_IDCMP,           IDCMP_COMMON,
			TAG_DONE);
}

void close_debug_window()
{
	if (debug_Window) CloseWindow(debug_Window);
	debug_Window = NULL;
}

void debug_draw_wave(struct wave *wave)
{
	unsigned int n;
	 char *data;
	data = ( char *) &(wave -> sample.ptr);

	open_debug_window();
	for (n=0;n<wave -> sample.bytes;n++) 	WritePixelColor( debug_Window -> RPort, 50+n, 400 + data[n] , 0xFF0000FF); 
	getchar();
	close_debug_window();
}

void debug_draw_hline(int x)
{
	int y;
	if (debug_Window)
	{
		for (y=-30;y<=30;y++)
		{
			WritePixelColor( debug_Window -> RPort, 50+x, 400+y, 0xFFFF0000); 
		}
	}
	else
	{
		printf("debug gfx window not open\n");
	}
}

#endif