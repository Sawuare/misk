// pp.c - print a penis incrementally

#if __STDC_NO_THREADS__ == 1
#error "No thrd_sleep()!"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define LEN_MIN 3
#define LEN_MAX 85

int main(int argc, char *argv[]) {
  int len;

  if (argv[1]) {
    len = atoi(argv[1]);

    if (len < LEN_MIN || len > LEN_MAX)
      return 1;
  }
  else {
    srand(time(0));
    len = rand() % (LEN_MAX - LEN_MIN + 1) + LEN_MIN;
  }

  struct timespec zzz = {.tv_nsec = 1000000000 / len};

  len -= 2;

  setbuf(stdout, 0);

  putchar('8');
  thrd_sleep(&zzz, 0);

  while (len--) {
    putchar('=');
    thrd_sleep(&zzz, 0);
  }

  putchar('D');
  putchar('\n');
}
