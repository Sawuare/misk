// hacc.c - print random characters in random colors and positions until interrupted

#if __STDC_NO_THREADS__ == 1
#error "No thrd_sleep()!"
#endif

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "dectcem.h"
#include "ecma-48.h"

_Noreturn static void stop(int unused) {
  fputs(RIS, stdout);
  exit(0);
}

int main(int argc, char *argv[]) {
  long pause = argv[1] ? atol(argv[1]) : 125000000;

  if (pause < 0 || pause > 999999999)
    return 1;

  struct timespec zzz = {.tv_nsec = pause};

  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return 2;

  srand(time(0));
  signal(SIGINT, stop);

  fputs(DECTCEM("l") ED("2"), stdout);

  while (1) {
    int row = rand() % ws.ws_row +  1;
    int col = rand() % ws.ws_col +  1;
    int clr = rand() %         8 + 30;
    int chr = rand() %        94 + 33;

    printf(CUP("%d;%d") SGR("%d") "%c", row, col, clr, chr);
    fflush(stdout);

    thrd_sleep(&zzz, 0);
  }
}
