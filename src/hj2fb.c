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

#define PRINTL(warning) printf("i%-10u j%-10u x%-10u y%-10u #%06x " warning "\r", id, j, x0, y0, color)

int main(int argc, char *argv[]) {
  _Bool    line = 0;
  unsigned step = 32;

  width  = FB_WIDTH;
  height = FB_HEIGHT;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:x:y:o:s:l")) != -1)
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

      case 'x':
        x0 = strtoul(optarg, 0, 10);
        break;

      case 'y':
        y0 = strtoul(optarg, 0, 10);
        break;

      case 'o':
        x0 = y0 = strtoul(optarg, 0, 10);
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

  int fb_descriptor = open(FB_PATH, O_RDWR);

  if (fb_descriptor == -1)
    return 3;

  canvas = mmap(0, FB_SIZE, PROT_WRITE, MAP_SHARED, fb_descriptor, 0);

  close(fb_descriptor);

  if (canvas == MAP_FAILED)
    return 4;

  struct termios old_term, new_term;
  tcgetattr(STDIN_FILENO, &old_term);
  new_term = old_term;
  new_term.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

  setbuf(stdout, 0);

  fputs(DECTCEM("l") ED("1") CUP(), stdout);

  while (1) {
    if (hj_is_valid())
      hj_painters[id]();
    else {
      PRINTL("N/A");
      goto get;
    }

    if (line)
print:
      PRINTL("   ");

get:
    switch (getchar()) {
      case '0':
        id = j = x0 = y0 = 0;
        break;

      case '1':
        --id;
        break;

      case '2':
        ++id;
        break;

      case '3':
        --j;
        break;

      case '4':
        ++j;
        break;

      case '5':
        x0 -= step;
        break;

      case '6':
        x0 += step;
        break;

      case '7':
        y0 -= step;
        break;

      case '8':
        y0 += step;
        break;

      case '#':
        scanf("%6x", &color);
        break;

      case 'i':
        scanf("%u", &id);
        break;

      case 'j':
        scanf("%u", &j);
        break;

      case 'x':
        scanf("%u", &x0);
        break;

      case 'y':
        scanf("%u", &y0);
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
  tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}
