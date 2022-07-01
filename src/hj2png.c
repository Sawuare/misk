// hj2png.c - write an HJ image to a PNG file

#include <getopt.h>
#include <inttypes.h>
#include <png.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#include "hj.h"

// A max length equal to 1 << 15 for a max area equal to 1 << 30 (gibipixel)
#define LENGTH_MAX 32768

int main(int argc, char *argv[]) {
  _Bool best_compression = 0;

  int opt;

  while ((opt = getopt(argc, argv, "i:j:x:y:o:w:h:l:mz")) != -1)
    switch (opt) {
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

      case 'w': hj_width = strtoul(optarg, 0, 10);
        break;

      case 'h': hj_height = strtoul(optarg, 0, 10);
        break;

      case 'l': hj_width = hj_height = strtoul(optarg, 0, 10);
        break;

      // Place the origin in the middle of the image
      case 'm':
        hj_x0 = -(hj_width  / 2);
        hj_y0 = -(hj_height / 2);
        break;

      case 'z': best_compression = 1;
        break;

      default: return 1;
    }

  if (!hj_defined() || !hj_width || !hj_height || hj_width > LENGTH_MAX || hj_height > LENGTH_MAX)
    return 2;

  png_struct *structp = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_info *infop = png_create_info_struct(structp);

  if (!(structp && infop))
    return 3;

  // The longest filename is
  // i10j1000000000x1000000000y1000000000w10000h10000.hj.png
  char filename[56];
  sprintf(filename, "i%" PRIu32 "j%" PRIu32 "x%" PRIu32 "y%" PRIu32 "w%" PRIu32 "h%" PRIu32 ".hj.png",
    hj_id, hj_j, hj_x0, hj_y0, hj_width, hj_height);

  FILE *file = fopen(filename, "wb");

  if (!file)
    return 4;

  if (setjmp(png_jmpbuf(structp))) {
    remove(filename);
    return 5;
  }

  png_text texts[2] = {
    {.key = "Author",   .text = "Sawuare", .compression = PNG_TEXT_COMPRESSION_NONE},
    {.key = "Software", .text = "hj2png",  .compression = PNG_TEXT_COMPRESSION_NONE}
  };

  png_set_compression_strategy(structp, Z_DEFAULT_STRATEGY);
  png_set_compression_level(structp, best_compression ? Z_BEST_COMPRESSION : Z_DEFAULT_COMPRESSION);
  png_set_filter(structp, PNG_FILTER_TYPE_BASE, PNG_FILTER_NONE);
  png_set_text(structp, infop, texts, 2);
  png_set_IHDR(structp, infop, hj_width, hj_height, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  hj_canvas = malloc(hj_width * hj_height * sizeof *hj_canvas);
  png_byte *row = malloc((hj_width + 7) / 8 * sizeof *row);

  if (!(hj_canvas && row)) {
    remove(filename);
    return 6;
  }

  hj_painters[hj_id]();
  png_init_io(structp, file);
  png_write_info(structp, infop);

  for (uint32_t y = 0; y < hj_height; ++y) {
    for (uint32_t x = 0; x < hj_width; ++x) {
      if (!(x % 8))
        row[x / 8] = 0;

      if (!hj_canvas[y * hj_width + x])
        row[x / 8] |= 1 << (7 - x % 8);
    }

    png_write_row(structp, row);
  }

  png_write_end(structp, 0);
  png_destroy_write_struct(&structp, &infop);
  free(hj_canvas);
  free(row);
  fclose(file);
  printf("Wrote %s\n", filename);
}
