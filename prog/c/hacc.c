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
#define SEC 120

_Noreturn static void bye(int unused) {
	fputs(RIS, stdout);
	exit(EXIT_FAILURE);
}

int main(void) {
	srand(time(0));
	signal(SIGINT, bye);

	int area = ROW * COL;
	struct timespec zzz = {.tv_nsec = 999999999 / area * SEC};

	fputs(DECTCEM("l") ED("2"), stdout);

	for (int a = 0; a < area; ++a) {
		int row = rand() % ROW + 1;
		int col = rand() % COL + 1;
		int clr = rand() % CLR;
		int chr = rand() % CHR;

		fprintf(stdout, CUP("%d;%d") SGR("38;2;0;%d;0") "%c", row, col, clr, chr);
		fflush(stdout);

		thrd_sleep(&zzz, 0);
	}

	fgetc(stdin);
	fputs(RIS, stdout);
}
