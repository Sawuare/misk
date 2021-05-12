// fb2png.c - write fb.png images

#include <getopt.h>
#include <png.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <zlib.h>

#include "fb.h"

static inline unsigned ddigits(unsigned n) {
	unsigned d = 1;

	while (n /= 10)
		++d;

	return d;
}

static inline unsigned get_letter_hue(char* s) {
	switch (*s) {
		default :
		case 'w': return FB_WHITE;
		case 'r': return FB_RED;
		case 'g': return FB_GREEN;
		case 'b': return FB_BLUE;
		case 'c': return FB_CYAN;
		case 'm': return FB_MAGENTA;
		case 'y': return FB_YELLOW;
	}
}

static inline unsigned get_base16_hue(char* s) {
	return strtoul(s, 0, 16);
}

int main(int argc, char* argv[argc + 1]) {
	unsigned id   = 0;
	unsigned z    = 1;
	unsigned xres = FB_XRES;
	unsigned yres = FB_YRES;
	unsigned hue  = FB_WHITE;

	int ch;

	while ((ch = getopt(argc, argv, "#:h:i:x:y:z:")) != -1)
		switch (ch) {
			case '#':
				hue = get_base16_hue(optarg);
				break;

			case 'h':
				hue = get_letter_hue(optarg);
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
		}

	unsigned x_ddigits = ddigits(xres);
	unsigned y_ddigits = ddigits(yres);
	unsigned z_ddigits = ddigits(z);

	unsigned filename_len = x_ddigits + y_ddigits + z_ddigits + 20;

	char filename[filename_len + 1];

	if (sprintf(filename, "i%02ux%*uy%*uz%*u#%06x.fb.png", id, x_ddigits, xres, y_ddigits, yres, z_ddigits, z, hue) != filename_len)
		return 1;

	FILE* stream = fopen(filename, "wb");

	if (!stream)
		return 2;

	png_structp structp = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

	if (!structp) {
		fclose(stream);
		return 3;
	}

	png_infop infop = png_create_info_struct(structp);

	if (!infop) {
		png_destroy_write_struct(&structp, 0);
		fclose(stream);
		return 4;
	}

	if (setjmp(png_jmpbuf(structp))) {
		png_destroy_write_struct(&structp, &infop);
		fclose(stream);
		return 5;
	}

	png_init_io(structp, stream);

	png_text text = {0};

	text.key = "Author";
	text.text = "Sawuare";
	text.compression = PNG_TEXT_COMPRESSION_NONE;

	png_set_IHDR(structp, infop, xres, yres, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//	png_set_compression_level(structp, Z_BEST_COMPRESSION);
	png_set_text(structp, infop, &text, 1);
	png_set_invert_alpha(structp);
	png_set_bgr(structp);

	unsigned* image = calloc(xres * yres, sizeof *image);

	if (!image) {
		png_destroy_write_struct(&structp, &infop);
		fclose(stream);
		return 6;
	}

	painters[id](xres, yres, z, hue, image);

	png_bytep row_pointers[yres];

	for (unsigned y = 0; y < yres; ++y)
		row_pointers[y] = (png_bytep) (image + y * xres);

	png_write_info(structp, infop);
	png_write_image(structp, row_pointers);
	png_write_end(structp, infop);

	printf("fb2png: wrote '%s'\n", filename);

	png_destroy_write_struct(&structp, &infop);

	free(image);
	fclose(stream);

	return 0;
}
