

// --------- debug options --------------- (most common debug options)

#define show_proc_names_no




// ----- macro's

#ifdef show_proc_names_yes
#define proc_names_printf printf
#else
#define proc_names_printf(fmt,...)
#endif


