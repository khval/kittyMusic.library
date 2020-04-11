

struct Envals
{
	int volume;
	int startDuration;
	int duration;
};


struct Sample
{
	int bytes;
	int frequency;
	int size;
	char ptr; 
};

struct waves
{
	struct wave **items;
	unsigned int used;
	unsigned int allocated;
};


// wave

extern struct wave *allocWave( int id, int size );
extern struct wave *getWave(struct waves *waves, int id);
extern bool delWave( struct waves *waves, int id );
extern void make_wave_bell(struct waves *waves);
extern void setEnval(struct wave *wave, int phase, int duration, int volume);

// waves

extern struct Waves *newWaves( int size );
extern void wavesPushBack(struct waves *waves,struct wave *wave);
extern void wavesRemove( struct waves *waves, int index );
extern void dumpWaves( struct waves *waves);
extern void clean_up_waves( struct waves *waves );

