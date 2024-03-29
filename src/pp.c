// pp.c - print a penis icon incrementally

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_LENGTH  3
#define MAX_LENGTH  80
#define ALL_LENGTHS 78 // == MAX_LENGTH - MIN_LENGTH + 1

int main(int argc, char *argv[]) {
  int length;

  if (argv[1]) {
    length = atoi(argv[1]);

    if (length < MIN_LENGTH || length > MAX_LENGTH)
      return 1;
  }
  else {
    srand(time(0));
    length = rand() % ALL_LENGTHS + MIN_LENGTH;
  }

  struct timespec zzz = {.tv_nsec = 1000000000 / length};

  length -= 2;

  setbuf(stdout, 0);
  putchar('8');
  nanosleep(&zzz, 0);

  while (length--) {
    putchar('=');
    nanosleep(&zzz, 0);
  }

  putchar('D');
  putchar('\n');
}
