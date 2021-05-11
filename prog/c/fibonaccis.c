// fibonaccis.c - print all Fibonacci numbers < 1 << 64

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define N 94

int main(void) {
	uint64_t fs[N];

	fs[0] = 0;
	fs[1] = 1;

	for (uint8_t n = 2; n < N; ++n)
		printf("%" PRIu64 "\n", fs[n] = fs[n - 1] + fs[n - 2]);
}
