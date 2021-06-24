// pp.c - print a penis over time

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int main(int argc, char* argv[argc + 1]) {
	srand(time(0));
	setbuf(stdout, 0);

	int len = argv[1] ? atoi(argv[1]) : rand() % 127;
	struct timespec zzz = {.tv_nsec = 999999999 / len};

	putchar('8');

	for (int l = 0; l < len; ++l) {
		thrd_sleep(&zzz, 0);

		putchar('=');
	}

	putchar('D');
	putchar('\n');
}
