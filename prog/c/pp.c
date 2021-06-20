// pp.c - print a penis over time

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int main(int argc, char* argv[argc + 1]) {
	int len = argv[1] ? atoi(argv[1]) : rand() % 127;

	setbuf(stdout, 0);

	putchar('8');

	for (int l = 0; l < len; ++l) {
		thrd_sleep(&(struct timespec) {0, 999999999 / len}, 0);

		putchar('=');
	}

	putchar('D');
	putchar('\n');
}
