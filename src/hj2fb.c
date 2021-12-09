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

static inline void printl(_Bool warn) {
  printf("i%-10u j%-10u x%-10u y%-10u #%06x%s\r",
    hj_id, hj_j, hj_x0, hj_y0, hj_color, warn ? " N/A" : "");
}

int main(int argc, char *argv[]) {
  _Bool    line = 0;
  unsigned step = 32;

  hj_width  = FB_WIDTH;
  hj_height = FB_HEIGHT;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:x:y:o:s:l")) != -1)
    switch (opt) {
      case '#':
        hj_color = hj_rrggbb_to_color(optarg);
        break;

      case 'c':
        hj_color = hj_letter_to_color(optarg);
        break;

      case 'i':
        hj_id = strtoul(optarg, 0, 10);
        break;

      case 'j':
        hj_j = strtoul(optarg, 0, 10);
        break;

      case 'x':
        hj_x0 = strtoul(optarg, 0, 10);
        break;

      case 'y':
        hj_y0 = strtoul(optarg, 0, 10);
        break;

      case 'o':
        hj_x0 = hj_y0 = strtoul(optarg, 0, 10);
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

  if (hj_color > 0xffffff)
    return 2;

  int fb_descriptor = open(FB_PATH, O_RDWR);

  if (fb_descriptor == -1)
    return 3;

  hj_canvas = mmap(0, FB_SIZE, PROT_WRITE, MAP_SHARED, fb_descriptor, 0);

  close(fb_descriptor);

  if (hj_canvas == MAP_FAILED)
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
      hj_painters[hj_id]();
    else {
      printl(1);
      goto get;
    }

    if (line)
print:
      printl(0);

get:
    switch (getchar()) {
      case '0':
        hj_id = hj_j = hj_x0 = hj_y0 = 0;
        break;

      case '1':
        --hj_id;
        break;

      case '2':
        ++hj_id;
        break;

      case '3':
        --hj_j;
        break;

      case '4':
        ++hj_j;
        break;

      case '5':
        hj_x0 -= step;
        break;

      case '6':
        hj_x0 += step;
        break;

      case '7':
        hj_y0 -= step;
        break;

      case '8':
        hj_y0 += step;
        break;

      case '#':
        scanf("%6x", &hj_color);
        break;

      case 'i':
        scanf("%u", &hj_id);
        break;

      case 'j':
        scanf("%u", &hj_j);
        break;

      case 'x':
        scanf("%u", &hj_x0);
        break;

      case 'y':
        scanf("%u", &hj_y0);
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
