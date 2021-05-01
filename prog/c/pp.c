// pp.c - print a penis over time

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int main(int argc, char* argv[argc + 1]) {
	int len = atoi(argv[1]);

	setbuf(stdout, 0);

	putchar('8');

	for (int i = 0; i < len; ++i) {
		thrd_sleep(&(struct timespec) {0, 999999999 / len}, 0);

		putchar('=');
	}

	putchar('D');
	putchar('\n');
}
