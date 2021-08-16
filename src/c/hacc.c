// hacc.c - print random characters in random colors and positions until interrupted

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "dectcem.h"
#include "ecma-48.h"
#include "macros.h"

_Noreturn static void bye(int unused) {
  fputs(RIS, stdout);
  exit(0);
}

int main(int argc, char* argv[argc + 1]) {
  srand(time(0));
  signal(SIGINT, bye);

  long ns = argv[1] ? atol(argv[1]) : 125000000;

  struct timespec zzz = {.tv_nsec = CLMP(ns, 0, 999999999)};

  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

  fputs(DECTCEM("l") ED("2"), stdout);

  for (EVER) {
    int row = rand() % ws.ws_row + 1;
    int col = rand() % ws.ws_col + 1;
    int clr = rand() % 256;
    int chr = rand() % 128;

    fprintf(stdout, CUP("%d;%d") SGR("38;2;0;%d;0") "%c", row, col, clr, chr);
    fflush(stdout);

    thrd_sleep(&zzz, 0);
  }
}
