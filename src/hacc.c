// hacc.c - print random characters in random colors and positions until interrupted

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "ecma48.h"
#include "tcem.h"

_Noreturn static void stop(int unused) {
  fputs(ECMA48_RIS, stdout);
  exit(0);
}

int main(int argc, char *argv[]) {
  int pause; // In milliseconds

  if (argv[1]) {
    pause = atoi(argv[1]);

    if (pause < 0 || pause > 999)
      return 1;
  }
  else
    pause = 125;

  struct timespec zzz = {.tv_nsec = 1000000 * pause};

  struct winsize winsz;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz) == -1)
    return 2;

  srand(time(0));
  signal(SIGINT, stop);
  fputs(TCEM("l") ECMA48_ED("2"), stdout);

  while (1) {
    printf(ECMA48_CUP("%d;%d") ECMA48_SGR("%d") "%c",
      rand() % winsz.ws_row +  1,  // [1, winsz.ws_row]
      rand() % winsz.ws_col +  1,  // [1, winsz.ws_col]
      rand() %            8 + 30,  // [30,          37]
      rand() %           94 + 33); // [33,         126]

    fflush(stdout);
    nanosleep(&zzz, 0);
  }
}
