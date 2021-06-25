// test.c - test some macros and static assertions

#if __STDC__ != 1
#error "Not a conforming implementation!"
#endif

#if __STDC_VERSION__ < 201112
#error "Not a modern implementation!"
#endif

#if __STDC_NO_THREADS__ == 1
#error "No thrd_sleep()!"
#endif

#if __STDC_NO_VLA__ == 1
#error "No VLA!"
#endif

#include <limits.h>

_Static_assert(CHAR_BIT == 8, "char is not 8 bits!");
_Static_assert(sizeof (unsigned) == 4, "unsigned is not 4 bytes!");
