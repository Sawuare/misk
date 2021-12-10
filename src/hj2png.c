// hj2png.c - write an HJ image in the PNG format

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <png.h>
#include <zlib.h>

#include "hj.h"

static inline unsigned ddig(unsigned n) {
  unsigned d = 1;

  while (n /= 10)
    ++d;

  return d;
}

int main(int argc, char *argv[]) {
  _Bool best = 0;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:x:y:o:w:h:l:vz")) != -1)
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

      case 'w':
        hj_width = strtoul(optarg, 0, 10);
        break;

      case 'h':
        hj_height = strtoul(optarg, 0, 10);
        break;

      case 'l':
        hj_width = hj_height = strtoul(optarg, 0, 10);
        break;

      case 'v':
        printf("Compiled with libpng %s and zlib %s\n", PNG_LIBPNG_VER_STRING, ZLIB_VERSION);
        printf("Executed with libpng %s and zlib %s\n", png_libpng_ver, zlib_version);
        return 0;

      case 'z':
        best = 1;
        break;

      default:
        return 1;
    }

  unsigned area = hj_width * hj_height;

  if (!hj_is_valid() || !area || area > 1 << 30 || hj_color > 0xffffff)
    return 2;

  png_struct *structp = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_info *infop = png_create_info_struct(structp);

  if (!structp || !infop) {
    png_destroy_write_struct(&structp, &infop);
    return 3;
  }

  char filename[ddig(hj_id) + ddig(hj_j) + ddig(hj_x0) + ddig(hj_y0) + ddig(hj_width) + ddig(hj_height) + 21];
  sprintf(filename, "i%uj%ux%uy%uw%uh%u#%06x.hj.png", hj_id, hj_j, hj_x0, hj_y0, hj_width, hj_height, hj_color);

  FILE *stream = fopen(filename, "wb");

  if (!stream) {
    png_destroy_write_struct(&structp, &infop);
    return 4;
  }

  if (setjmp(png_jmpbuf(structp))) {
    png_destroy_write_struct(&structp, &infop);
    fclose(stream);
    remove(filename);
    return 5;
  }

  png_init_io(structp, stream);

  png_text texts[] = {
    {.key = "Author",   .text = "Sawuare", .compression = PNG_TEXT_COMPRESSION_NONE},
    {.key = "Software", .text = "hj2png",  .compression = PNG_TEXT_COMPRESSION_NONE}
  };

  png_set_IHDR(structp, infop, hj_width, hj_height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_set_text(structp, infop, texts, sizeof texts / sizeof *texts);
  png_set_filter(structp, PNG_FILTER_TYPE_BASE, HJ_IS_MONO_XOR_RAMP(hj_id) ? PNG_FILTER_NONE : PNG_FILTER_UP);
  png_set_compression_level(structp, best ? Z_BEST_COMPRESSION : Z_DEFAULT_COMPRESSION);
  png_set_compression_strategy(structp, Z_DEFAULT_STRATEGY);

  png_byte *image;

  image     = malloc(area * 3);
  hj_canvas = malloc(area * 4);

  if (!image || !hj_canvas) {
    png_destroy_write_struct(&structp, &infop);
    free(image);
    free(hj_canvas);
    fclose(stream);
    remove(filename);
    return 6;
  }

  hj_painters[hj_id]();

  for (unsigned i = 0, j = 0; i < area; i += 1, j += 3) {
    image[j    ] = HJ_PX_TO_R_BYTE(hj_canvas[i]);
    image[j + 1] = HJ_PX_TO_G_BYTE(hj_canvas[i]);
    image[j + 2] = HJ_PX_TO_B_BYTE(hj_canvas[i]);
  }

  free(hj_canvas);

  png_byte *row_pointers[hj_height];

  for (unsigned y = 0; y < hj_height; ++y)
    row_pointers[y] = &image[y * hj_width * 3];

  png_write_info(structp, infop);
  png_write_image(structp, row_pointers);
  png_write_end(structp, 0);

  png_destroy_write_struct(&structp, &infop);
  free(image);
  fclose(stream);

  printf("Wrote %s\n", filename);
}
