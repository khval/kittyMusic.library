

struct Waves
{
	struct Wave **items;
	unsigned int used;
	unsigned int allocated;
};

extern struct Waves *newWaves( int size );
extern void wavesPushBack(struct Waves *waves,struct Wave *wave);
extern void wavesRemove( struct Waves *waves, int index );
extern void dumpWaves( struct Waves *waves);
extern void clean_up_waves( struct Waves *waves );

