// fb.c - paint fb images

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <termios.h>
#include <unistd.h>

#include "DECTCEM.h"
#include "ECMA-48.h"
#include "fb.h"

static inline void set_z_range(char* s, unsigned* first, unsigned* final) {
	char* comma = strchr(s, ',');

	if (comma) {
		*first = strtoul(s, 0, 10);
		*final = strtoul(comma + 1, 0, 10);
	} else
		*final = strtoul(s, 0, 10);
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
	_Bool    counter = 0;
	unsigned id      = 0;
	unsigned step    = 1;
	unsigned first_z = 1;
	unsigned final_z = 1;
	unsigned hue     = FB_WHITE;

	int chr;

	while ((chr = getopt(argc, argv, "#:ch:i:s:z:")) != -1)
		switch (chr) {
			case '#':
				hue = get_base16_hue(optarg);
				break;

			case 'c':
				counter = 1;
				break;

			case 'h':
				hue = get_letter_hue(optarg);
				break;

			case 'i':
				id = strtoul(optarg, 0, 10);
				break;

			case 's':
				step = strtoul(optarg, 0, 10);
				break;

			case 'z':
				set_z_range(optarg, &first_z, &final_z);
				break;

			default:
				return EXIT_FAILURE;
		}

	int fbd = open(FB_PATH, O_RDWR);

	unsigned* fbm = mmap(0, FB_SIZE, PROT_WRITE, MAP_SHARED, fbd, 0);

	struct termios otty, ntty;

	tcgetattr(STDIN_FILENO, &otty);

	ntty = otty;

	ntty.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSANOW, &ntty);

	fputs(DECTCEM("l") ED("2") CUP(), stdout);
	fflush(stdout);

	for (unsigned z = first_z; z >= first_z && z <= final_z;) {
		painters[id](FB_XRES, FB_YRES, z, hue, fbm);

		if (counter) {
			fprintf(stdout, "z: %u\r", z);
			fflush(stdout);
		}
fgetc:
		switch (fgetc(stdin)) {
			case '[':
				z -= step;
				break;

			case ']':
				z += step;
				break;

			case 'z':
				fscanf(stdin, "%u", &z);
				break;

			case 'c':
				counter = !counter;
				break;

			case 'q':
				goto quit;

			default:
				goto fgetc;
		}
	}
quit:
	fputs(DECTCEM("h"), stdout);

	tcsetattr(STDIN_FILENO, TCSANOW, &otty);

	munmap(fbm, FB_SIZE);
	close(fbd);
}
