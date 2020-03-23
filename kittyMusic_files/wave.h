

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

struct Wave
{
	int id;
	struct Envals envels[7];
	struct Sample sample;
};

