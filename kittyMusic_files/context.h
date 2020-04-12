

struct context
{
	struct waves waves;
	int sample_bank;

#ifdef debug
	struct Window *debug_Window = NULL;;
#endif
};

