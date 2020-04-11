
#include <stdlib.h>
#include <string.h>
#include <proto/dos.h>

struct Envals
{
	int volume;
	int startDuration;
	int duration;
};

struct Wave
{
	struct Envals envels[7];
};

struct Waves
{
	struct Wave **items;
	unsigned int used;
	unsigned int allocated;
};

struct Waves *newWaves( int size )
{
	struct Waves *_new_;

	_new_ = (struct Waves *) malloc(sizeof( struct Waves ) );
	if (_new_)
	{
		_new_ -> items = (struct Wave **) malloc(sizeof(struct Wave *) * size );
		_new_ -> allocated = size;
		_new_ -> used = 0;

		if (_new_ -> items == NULL)
		{
			free(_new_);
			_new_ = NULL;
		}
	}

	return _new_;
}

void wavesPushBack(struct Waves *waves,struct Wave *wave)
{
	// check if allocated table is ok

	if (waves -> used >= waves -> allocated )
	{
		int _new_size_ = waves -> allocated + 20;
		struct Wave **_new_items = (struct Wave **) malloc(sizeof(struct Wave *) * _new_size_ );

		if (_new_items)
		{
			if (waves -> used) memcpy( _new_items, waves -> items, sizeof(struct Wave *) * waves -> used );
			free(waves -> items);
			waves -> items = _new_items;
		}
	}

	if (waves -> items)
	{	
		waves -> items[ waves -> used ] = wave;
		waves -> used ++;
	}
}

void wavesRemove( struct Waves *waves, int index )
{
	unsigned int n;
	for (n=waves -> used-1;n>index;n--)
	{
		waves -> items[n-1] = waves -> items[n];
	}
}

void dumpWaves( struct Waves *waves)
{
	struct Wave *wave;

	unsigned int n,nn;

	Printf("-- waves --\n");
	for (n=0;n<waves -> used;n++)
	{
		wave = waves -> items[n];

		for (nn=0;nn<7;nn++)
		{

			Printf("waves[%ld] -> envels[%ld] = {%ld,%ld,%ld}\n",n, nn,
				wave -> envels[nn].volume, 
				wave -> envels[nn].startDuration,
				wave -> envels[nn].duration );
		}
	}
}

void clean_up_waves( struct Waves *waves )
{
	struct Wave *wave;

	if (waves -> items )
	{
		while (waves -> used)
		{
			wave = waves -> items[ waves -> used - 1];
			if( wave )  free( wave );
			waves -> used --;
		}
		free (waves -> items);
	}
	free (waves);	
}
