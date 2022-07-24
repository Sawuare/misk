// hqz-fb.c - display HQZ images on the Linux framebuffer device

#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <termios.h>
#include <unistd.h>

#include "ecma48.h"
#include "hqz.h"
#include "tcem.h"

#define BLACK 0x000000
#define WHITE 0xffffff

int main(int argc, char *argv[]) {
  _Bool    line = 1;
  uint32_t step = 32;

  int opt;

  while ((opt = getopt(argc, argv, "p:q:x:y:o:s:l")) != -1)
    switch (opt) {
      case 'p': hqz_id = strtoul(optarg, 0, 10);
        break;

      case 'q': hqz_q = strtoul(optarg, 0, 10);
        break;

      case 'x': hqz_x0 = strtoul(optarg, 0, 10);
        break;

      case 'y': hqz_y0 = strtoul(optarg, 0, 10);
        break;

      case 'o': hqz_x0 = hqz_y0 = strtoul(optarg, 0, 10);
        break;

      case 's': step = strtoul(optarg, 0, 10);
        break;

      case 'l': line = 0;
        break;

      default: return 1;
    }

  int fb_descriptor = open("/dev/fb0", O_RDWR);

  if (fb_descriptor == -1)
    return 2;

  struct fb_fix_screeninfo fscreeninfo;
  struct fb_var_screeninfo vscreeninfo;

  if (ioctl(fb_descriptor, FBIOGET_FSCREENINFO, &fscreeninfo) == -1 ||
      ioctl(fb_descriptor, FBIOGET_VSCREENINFO, &vscreeninfo) == -1)
    return 3;

  uint32_t mid_x0 = 0x100000000 - vscreeninfo.xres / 2;
  uint32_t mid_y0 = 0x100000000 - vscreeninfo.yres / 2;

  hqz_width  = fscreeninfo.line_length / 4;
  hqz_height = vscreeninfo.yres;

  uint32_t *fb_map = mmap(0, fscreeninfo.smem_len, PROT_WRITE, MAP_SHARED, fb_descriptor, 0);
  close(fb_descriptor);

  if (fb_map == MAP_FAILED)
    return 4;

  size_t area = hqz_width * hqz_height;
  hqz_canvas = malloc(area * sizeof *hqz_canvas);

  if (!hqz_canvas)
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

    if (hqz_defined()) {
      warn = 0;
      hqz_painters[hqz_id]();

      for (size_t i = 0; i < area; ++i)
        fb_map[i] = hqz_canvas[i] ? BLACK : WHITE;
    }
    else {
      warn = 1;
      goto print;
    }

    if (line)
print:
      printf("p%-10" PRIu32 " q%-10" PRIu32 " x%-10" PRIu32 " y%-10" PRIu32 "%s\r",
        hqz_id, hqz_q, hqz_x0, hqz_y0, warn ? " !" : "");

get:
    switch (getchar()) {
      case '1': --hqz_id;
        break;

      case '2': ++hqz_id;
        break;

      case '3': --hqz_q;
        break;

      case '4': ++hqz_q;
        break;

      case '5': hqz_x0 -= step;
        break;

      case '6': hqz_x0 += step;
        break;

      case '7': hqz_y0 -= step;
        break;

      case '8': hqz_y0 += step;
        break;

      case 'p': scanf("%" PRIu32, &hqz_id);
        break;

      case 'q': scanf("%" PRIu32, &hqz_q);
        break;

      case 'x': scanf("%" PRIu32, &hqz_x0);
        break;

      case 'y': scanf("%" PRIu32, &hqz_y0);
        break;

      case 'l':
        if (line) {
          line = 0;
          break;
        }

        line = 1;
        goto print;

      // Place the origin in the middle of the image
      case 'm':
        hqz_x0 = mid_x0;
        hqz_y0 = mid_y0;
        break;

      case 'e': goto exit;

      default: goto get;
    }
  }

exit:
  free(hqz_canvas);
  munmap(fb_map, fscreeninfo.smem_len);
  fputs(TCEM("h") ECMA48_ED("3"), stdout);

  if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1)
    return 7;
}
