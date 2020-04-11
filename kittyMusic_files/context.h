

struct context
{
	struct waves waves;
	bool sample_loop;
	int sample_bank;

#ifdef debug
	struct Window *debug_Window = NULL;;
#endif
};

