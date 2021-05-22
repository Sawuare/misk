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

int main(int argc, char* argv[argc + 1]) {
	_Bool    counter = 0;
	unsigned id      = 0;
	unsigned step    = 1;
	unsigned z       = 1;
	unsigned hue     = FB_WHITE;

	int opt;

	while ((opt = getopt(argc, argv, "#:ch:i:s:z:")) != -1)
		switch (opt) {
			case '#':
				hue = strtoul(optarg, 0, 16);
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
				z = strtoul(optarg, 0, 10);
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

	while (z) {
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
