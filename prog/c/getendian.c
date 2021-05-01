// getendian.c

#include <stdio.h>

int main(void) {
	union {unsigned value; unsigned char bytes[sizeof (unsigned)];} one = {1};

	puts(one.bytes[0] ? "little" : "big");
}
