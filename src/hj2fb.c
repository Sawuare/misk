// hj2fb.c - paint HJ images on the Linux framebuffer device

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <getopt.h>
#include <sys/mman.h>
#include <termios.h>
#include <unistd.h>

#include "dectcem.h"
#include "ecma-48.h"
#include "hj.h"

#define FB_PATH "/dev/fb0"

// UNPORTABLE
#define FB_SIZE   4227072
#define FB_WIDTH  1376
#define FB_HEIGHT 768

#define PRINTL(id, j, warning) printf("i%-10u j%-10u " warning "\r", id, j)

int main(int argc, char *argv[]) {
  _Bool    line  = 0;
  unsigned id    = 0;
  unsigned j     = 0;
  unsigned step  = 1;
  unsigned color = HJ_WHITE;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:s:l")) != -1)
    switch (opt) {
      case '#':
        color = hj_rrggbb_to_color(optarg);
        break;

      case 'c':
        color = hj_letter_to_color(optarg);
        break;

      case 'i':
        id = strtoul(optarg, 0, 10);
        break;

      case 'j':
        j = strtoul(optarg, 0, 10);
        break;

      case 's':
        step = strtoul(optarg, 0, 10);
        break;

      case 'l':
        line = 1;
        break;

      default:
        return 1;
    }

  if (color > 0xffffff)
    return 2;

  int fbd = open(FB_PATH, O_RDWR);

  if (fbd == -1)
    return 3;

  unsigned *fbm = mmap(0, FB_SIZE, PROT_WRITE, MAP_SHARED, fbd, 0);

  close(fbd);

  if (fbm == MAP_FAILED)
    return 4;

  struct termios otty, ntty;
  tcgetattr(STDIN_FILENO, &otty);
  ntty = otty;
  ntty.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &ntty);

  setbuf(stdout, 0);

  fputs(DECTCEM("l") ED("1") CUP(), stdout);

  while (1) {
    if (hj_is_valid(id, j)) {
      hj_painters[id](j, color, FB_WIDTH, FB_HEIGHT, fbm);
    }
    else {
      PRINTL(id, j, "N/A");
      goto get;
    }

    if (line)
print:
      PRINTL(id, j, "   ");

get:
    switch (getchar()) {
      case '{':
        --id;
        break;

      case '}':
        ++id;
        break;

      case '[':
        j -= step;
        break;

      case ']':
        j += step;
        break;

      case 'i':
        scanf("%u", &id);
        break;

      case 'j':
        scanf("%u", &j);
        break;

      case 'l':
        if (line) {
          line = 0;
          break;
        }

        line = 1;
        goto print;

      case 'e':
        goto exit;

      default:
        goto get;
    }
  }

exit:
  fputs(DECTCEM("h") ED("3"), stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &otty);
  munmap(fbm, FB_SIZE);
}
