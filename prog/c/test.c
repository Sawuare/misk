// test.c - test some conditional feature macros and static assertions

#ifdef __STDC_NO_THREADS__
#error "No thrd_sleep()!"
#endif

#ifdef __STDC_NO_VLA__
#error "No VLA!"
#endif

_Static_assert(sizeof (unsigned) == 4, "unsigned is not 4 bytes!");
