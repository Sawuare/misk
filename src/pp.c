// pp.c - print a penis incrementally

#if __STDC_NO_THREADS__ == 1
#error "No thrd_sleep()!"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int main(int argc, char *argv[]) {
  int len = argv[1] ? atoi(argv[1]) : (srand(time(0)), rand() % 83 + 3);

  if (len < 3)
    return 1;

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
