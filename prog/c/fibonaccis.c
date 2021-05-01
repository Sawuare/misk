// fibonaccis.c - print all Fibonacci numbers < 2^64 - 1

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define N 94

int main(void) {
	uint64_t fs[N];

	for (uint64_t n = 0; n < N; ++n)
		printf("%" PRIu64 "\n", fs[n] = n == 0 ? 0 : n == 1 ? 1 : fs[n - 1] + fs[n - 2]);
}
