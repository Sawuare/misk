// pp.c - print a penis icon incrementally

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH_MIN 3
#define LENGTH_MAX 80
#define LENGTHS    78 // == LENGTH_MAX - LENGTH_MIN + 1

int main(int argc, char *argv[]) {
  int length;

  if (argv[1]) {
    length = atoi(argv[1]);

    if (length < LENGTH_MIN || length > LENGTH_MAX)
      return 1;
  }
  else {
    srand(time(0));
    length = rand() % LENGTHS + LENGTH_MIN;
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
