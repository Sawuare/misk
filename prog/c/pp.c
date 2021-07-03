// pp.c - print a penis over time

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int main(int argc, char* argv[argc + 1]) {
	srand(time(0));
	setbuf(stdout, 0);

	int len = argv[1] ? atoi(argv[1]) : rand() % 79 + 2;

	if (len < 2)
		len = 2;

	struct timespec zzz = {.tv_nsec = 1000000000 / len};

	len -= 2;

	putchar('8');
	thrd_sleep(&zzz, 0);

	while (len--) {
		putchar('=');
		thrd_sleep(&zzz, 0);
	}

	putchar('D');
	putchar('\n');
}
