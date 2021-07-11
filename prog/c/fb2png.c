// fb2png.c - write fb images in the PNG format

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <png.h>
#include <zlib.h>

#include "fb.h"
#include "macros.h"

static inline unsigned ddig(unsigned n) {
	unsigned d = 1;

	while (n /= 10)
		++d;

	return d;
}

int main(int argc, char* argv[argc + 1]) {
	unsigned id    = 0;
	unsigned z     = 1;
	unsigned xres  = FB_XRES;
	unsigned yres  = FB_YRES;
	unsigned color = FB_WHITE;

	int opt;

	while ((opt = getopt(argc, argv, "#:c:i:x:y:z:v")) != -1)
		switch (opt) {
			case '#':
				color = fb_get_base16_color(optarg);
				break;

			case 'c':
				color = fb_get_letter_color(optarg);
				break;

			case 'i':
				id = strtoul(optarg, 0, 10);
				break;

			case 'x':
				xres = strtoul(optarg, 0, 10);
				break;

			case 'y':
				yres = strtoul(optarg, 0, 10);
				break;

			case 'z':
				z = strtoul(optarg, 0, 10);
				break;

			case 'v':
				fprintf(stdout, "Compiled with libpng %s and using libpng %s\n", PNG_LIBPNG_VER_STRING, png_libpng_ver);
				fprintf(stdout, "Compiled with zlib %s and using zlib %s\n", ZLIB_VERSION, zlib_version);
				return 0;

			default:
				return 1;
		}

	if (!FB_IS_VALID(id, z)) {
		fprintf(stderr, "%s: invalid ID or Z\n", argv[0]);
		return 2;
	}

	unsigned l_filename = ddig(id) + ddig(xres) + ddig(yres) + ddig(z) + 19;

	char filename[l_filename];

	snprintf(filename, l_filename, "i%ux%uy%uz%u#%06x.fb.png", id, xres, yres, z, color);

	FILE* stream = fopen(filename, "wb");

	if (!stream)
		return 3;

	png_struct* structp = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

	if (!structp)
		return 4;

	png_info* infop = png_create_info_struct(structp);

	if (!infop) {
		png_destroy_write_struct(&structp, 0);
		return 5;
	}

	if (setjmp(png_jmpbuf(structp))) {
		png_destroy_write_struct(&structp, &infop);
		return 6;
	}

	png_init_io(structp, stream);

	png_text texts[] = {
		{.key = "Author",   .text = "Sawuare", .compression = PNG_TEXT_COMPRESSION_NONE},
		{.key = "Software", .text = "fb2png",  .compression = PNG_TEXT_COMPRESSION_NONE}
	};

	png_set_IHDR(structp, infop, xres, yres, FB_BPS, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_set_text(structp, infop, texts, ARRLEN(texts));
	png_set_filter(structp, PNG_FILTER_TYPE_BASE, FB_IS_MONO_XOR_RAMP(id) ? PNG_FILTER_NONE : PNG_FILTER_UP);
	png_set_compression_level(structp, Z_DEFAULT_COMPRESSION);
	png_set_compression_strategy(structp, Z_DEFAULT_STRATEGY);

	// Safe max res == 1 << 29
	unsigned res = xres * yres;

	unsigned* original_image = calloc(res,  4);
	png_byte* stripped_image = malloc(res * 3);

	if (!original_image || !stripped_image) {
		png_destroy_write_struct(&structp, &infop);
		free(original_image);
		free(stripped_image);
		return 7;
	}

	fb_painters[id](xres, yres, z, color, original_image);

	// Convert BGRA to RGB
	for (unsigned i = 0, j = 0; i < res; i += 1, j += 3) {
		stripped_image[j + 0] = original_image[i] >> 16 & 255; // R
		stripped_image[j + 1] = original_image[i] >>  8 & 255; // G
		stripped_image[j + 2] = original_image[i] >>  0 & 255; // B
	}

	free(original_image);

	png_byte* row_pointers[yres];

	for (unsigned y = 0; y < yres; ++y)
		row_pointers[y] = stripped_image + xres * y * 3;

	png_write_info(structp, infop);
	png_write_image(structp, row_pointers);
	png_write_end(structp, 0);

	png_destroy_write_struct(&structp, &infop);
	free(stripped_image);
	fclose(stream);

	fprintf(stdout, "Wrote '%s'\n", filename);
}
