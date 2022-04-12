// hj2png.c - write an HJ image in the PNG format

#include <inttypes.h>
#include <setjmp.h>
#include <stdio.h>

#include <getopt.h>

#include <png.h>
#include <zlib.h>

#include "hj.h"

// This limit of one mebipixel replaces the libpng default limit of one megapixel
#define LENGTH_MAX 1048576

int main(int argc, char *argv[]) {
  _Bool best_compression = 0;

  int opt;

  while ((opt = getopt(argc, argv, "#:c:i:j:x:y:o:w:h:l:vz")) != -1)
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

      case 'w': hj_width = strtoul(optarg, 0, 10);
        break;

      case 'h': hj_height = strtoul(optarg, 0, 10);
        break;

      case 'l': hj_width = hj_height = strtoul(optarg, 0, 10);
        break;

      case 'v':
        printf("Compiled with libpng %s and zlib %s\n", PNG_LIBPNG_VER_STRING, ZLIB_VERSION);
        printf("Executed with libpng %s and zlib %s\n", png_libpng_ver, zlib_version);
        return 0;

      case 'z': best_compression = 1;
        break;

      default: return 1;
    }

  size_t area = hj_width * hj_height;

  if (!hj_defined() || !area || hj_width > LENGTH_MAX || hj_height > LENGTH_MAX || hj_color > 0xffffff)
    return 2;

  png_struct *structp = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_info *infop = png_create_info_struct(structp);

  if (!structp || !infop) {
    png_destroy_write_struct(&structp, &infop);
    return 3;
  }

  // The longest filename is
  // i10j1000000000x1000000000y1000000000w1000000000h1000000000#100000.hj.png
  char filename[73];
  sprintf(filename, "i%" PRIu32 "j%" PRIu32 "x%" PRIu32 "y%" PRIu32 "w%" PRIu32 "h%" PRIu32 "#%06" PRIx32 ".hj.png",
    hj_id, hj_j, hj_x0, hj_y0, hj_width, hj_height, hj_color);

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

  png_text texts[] = {
    {.key = "Author",   .text = "Sawuare", .compression = PNG_TEXT_COMPRESSION_NONE},
    {.key = "Software", .text = "hj2png",  .compression = PNG_TEXT_COMPRESSION_NONE}
  };

  png_set_compression_strategy(structp, Z_DEFAULT_STRATEGY);
  png_set_compression_level(structp, best_compression ? Z_BEST_COMPRESSION : Z_DEFAULT_COMPRESSION);
  png_set_user_limits(structp, LENGTH_MAX, LENGTH_MAX);
  png_set_filter(structp, PNG_FILTER_TYPE_BASE, hj_mono_xor_ramp() ? PNG_FILTER_NONE : PNG_FILTER_UP);
  png_set_text(structp, infop, texts, sizeof texts / sizeof *texts);
  png_set_IHDR(structp, infop, hj_width, hj_height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_byte *image, **rows;

  hj_canvas = malloc(area * sizeof *hj_canvas);
  image = malloc(3 * area * sizeof *image);
  rows = malloc(hj_height * sizeof *rows);

  if (!hj_canvas || !image || !rows) {
    png_destroy_write_struct(&structp, &infop);
    free(hj_canvas);
    free(image);
    free(rows);
    fclose(stream);
    remove(filename);
    return 6;
  }

  hj_painters[hj_id]();

  for (size_t i = 0, j = 0; i < area; i += 1, j += 3) {
    image[j    ] = HJ_R_SAMPLE(hj_canvas[i]);
    image[j + 1] = HJ_G_SAMPLE(hj_canvas[i]);
    image[j + 2] = HJ_B_SAMPLE(hj_canvas[i]);
  }

  free(hj_canvas);

  while (hj_height--)
    rows[hj_height] = &image[hj_height * hj_width * 3];

  png_init_io(structp, stream);
  png_write_info(structp, infop);
  png_write_image(structp, rows);
  png_write_end(structp, 0);

  png_destroy_write_struct(&structp, &infop);
  free(image);
  free(rows);
  fclose(stream);
  printf("Wrote %s\n", filename);
}
