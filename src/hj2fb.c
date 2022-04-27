// hj2fb.c - paint HJ images on the Linux framebuffer device

#include <inttypes.h>
#include <stdio.h>

#include <fcntl.h>
#include <getopt.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <termios.h>
#include <unistd.h>

#include "ecma48.h"
#include "hj.h"
#include "tcem.h"

static inline void printl(_Bool warn) {
  printf("i%-10" PRIu32 " j%-10" PRIu32 " x%-10" PRIu32 " y%-10" PRIu32 " #%06" PRIx32 " %c\r",
    hj_id, hj_j, hj_x0, hj_y0, hj_color, warn ? '!' : ' ');
}

int main(int argc, char *argv[]) {
  _Bool    line = 0;
  uint32_t step = 32;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:x:y:o:s:l")) != -1)
    switch (opt) {
      case '#': hj_color = hj_rrggbb_to_color(optarg);
        break;

      case 'c': hj_color = hj_letter_to_color(optarg);
        break;

      case 'i': hj_id = strtoul(optarg, 0, 10);
        break;

      case 'j': hj_j = strtoul(optarg, 0, 10);
        break;

      case 'x': hj_x0 = strtoul(optarg, 0, 10);
        break;

      case 'y': hj_y0 = strtoul(optarg, 0, 10);
        break;

      case 'o': hj_x0 = hj_y0 = strtoul(optarg, 0, 10);
        break;

      case 's': step = strtoul(optarg, 0, 10);
        break;

      case 'l': line = 1;
        break;

      default: return 1;
    }

  if (hj_color > 0xffffff)
    return 2;

  int fb_descriptor = open("/dev/fb0", O_RDWR);

  if (fb_descriptor == -1)
    return 3;

  struct fb_fix_screeninfo fscreeninfo;
  struct fb_var_screeninfo vscreeninfo;

  if (ioctl(fb_descriptor, FBIOGET_FSCREENINFO, &fscreeninfo) == -1 ||
      ioctl(fb_descriptor, FBIOGET_VSCREENINFO, &vscreeninfo) == -1)
    return 4;

  hj_width  = fscreeninfo.line_length / 4;
  hj_height = vscreeninfo.yres;

  hj_canvas = mmap(0, fscreeninfo.smem_len, PROT_WRITE, MAP_SHARED, fb_descriptor, 0);
  close(fb_descriptor);

  if (hj_canvas == MAP_FAILED)
    return 5;

  struct termios old_term, new_term;

  if (tcgetattr(STDIN_FILENO, &old_term) == -1)
    return 6;

  new_term = old_term;
  new_term.c_lflag &= ~(ECHO | ICANON);

  if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
    return 7;

  setbuf(stdout, 0);
  fputs(TCEM("l") ECMA48_ED("1") ECMA48_CUP(), stdout);

  while (1) {
    _Bool warn;

    if (hj_defined()) {
      hj_painters[hj_id]();
      warn = 0;
    }
    else {
      warn = 1;
      goto print;
    }

    if (line)
print:
      printl(warn);

get:
    switch (getchar()) {
      case '1': --hj_id;
        break;

      case '2': ++hj_id;
        break;

      case '3': --hj_j;
        break;

      case '4': ++hj_j;
        break;

      case '5': hj_x0 -= step;
        break;

      case '6': hj_x0 += step;
        break;

      case '7': hj_y0 -= step;
        break;

      case '8': hj_y0 += step;
        break;

      case '#': scanf("%6" PRIx32, &hj_color);
        break;

      case 'i': scanf("%" PRIu32, &hj_id);
        break;

      case 'j': scanf("%" PRIu32, &hj_j);
        break;

      case 'x': scanf("%" PRIu32, &hj_x0);
        break;

      case 'y': scanf("%" PRIu32, &hj_y0);
        break;

      case 'l':
        if (line) {
          line = 0;
          break;
        }

        line = 1;
        goto print;

      case 'e': goto exit;

      default: goto get;
    }
  }

exit:
  fputs(TCEM("h") ECMA48_ED("3"), stdout);

  if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1)
    return 7;
}
