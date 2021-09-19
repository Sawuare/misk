// fb2fb.c - paint fb images on the Linux framebuffer device

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <getopt.h>
#include <sys/mman.h>
#include <termios.h>
#include <unistd.h>

#include "dectcem.h"
#include "ecma-48.h"
#include "fb.h"

int main(int argc, char* argv[argc + 1]) {
  _Bool    line  = 0;
  unsigned id    = 0;
  unsigned j     = 1;
  unsigned step  = 1;
  unsigned color = FB_WHITE;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:s:l")) != -1)
    switch (opt) {
      case '#':
        color = fb_rrggbb_to_color(optarg);
        break;

      case 'c':
        color = fb_letter_to_color(optarg);
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

  int ret = 0;

  int fbd = open(FB_PATH, O_RDWR);

  if (fbd == -1)
    return 2;

  unsigned* fbm = mmap(0, FB_SIZE, PROT_WRITE, MAP_SHARED, fbd, 0);

  close(fbd);

  if (fbm == MAP_FAILED)
    return 3;

  struct termios otty, ntty;
  tcgetattr(STDIN_FILENO, &otty);
  ntty = otty;
  ntty.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &ntty);

  fputs(DECTCEM("l") CUP(), stdout);
  fflush(stdout);

  while (FB_IS_VALID(id, j)) {
    fb_painters[id](j, color, FB_XRES, FB_YRES, fbm);

    if (line) {
      fprintf(stdout, "i%uj%u\r", id, j);
      fflush(stdout);
    }

fgetc:
    switch (fgetc(stdin)) {
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
        fscanf(stdin, "%u", &id);
        break;

      case 'j':
        fscanf(stdin, "%u", &j);
        break;

      case 'l':
        line = !line;
        break;

      case 'e':
        goto exit;

      default:
        goto fgetc;
    }
  }

  ret = 4;

exit:
  fputs(DECTCEM("h") ED("3"), stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &otty);
  munmap(fbm, FB_SIZE);

  return ret;
}
