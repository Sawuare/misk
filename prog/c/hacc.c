// hacc.c - print random characters in random colors and positions over time

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "DECTCEM.h"
#include "ECMA-48.h"

#define ROW 48
#define COL 128
#define CLR 256
#define CHR 128

_Noreturn void bye(int unused) {
	fputs(RIS, stdout);
	exit(EXIT_FAILURE);
}

int main(void) {
	signal(SIGINT, bye);

	fputs(DECTCEM("l") ED("2"), stdout);

	for (unsigned i = 0; i < ROW * COL; ++i) {
		unsigned row = rand() % ROW + 1;
		unsigned col = rand() % COL + 1;
		unsigned clr = rand() % CLR;
		unsigned chr = rand() % CHR;

		fprintf(stdout, CUP("%u;%u") SGR("38;2;0;%u;0") "%c", row, col, clr, chr);
		fflush(stdout);

		thrd_sleep(&(struct timespec) {0, 19531250}, 0);
	}

	fgetc(stdin);
	fputs(RIS, stdout);
}
