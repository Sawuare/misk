// hacc.c - print random characters in random colors and positions until interrupted

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "dectcem.h"
#include "ecma-48.h"

_Noreturn static void bye(int unused) {
  fputs(RIS, stdout);
  exit(0);
}

int main(int argc, char* argv[argc + 1]) {
  srand(time(0));
  signal(SIGINT, bye);

  long ns = argv[1] ? atol(argv[1]) : 125000000;

  if (ns < 0 || ns > 999999999)
    return 1;

  struct timespec zzz = {.tv_nsec = ns};

  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return 2;

  fputs(DECTCEM("l") ED("2"), stdout);

  while (1) {
    int row = rand() % ws.ws_row + 1;
    int col = rand() % ws.ws_col + 1;
    int clr = rand() % 256;
    int chr = rand() % 128;

    printf(CUP("%d;%d") SGR("38;2;0;%d;0") "%c", row, col, clr, chr);
    fflush(stdout);

    thrd_sleep(&zzz, 0);
  }
}
