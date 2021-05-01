// padovans.c - print all Padovan numbers < 2^64 - 1

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define N 159

int main(void) {
	uint64_t ps[N];

	for (uint64_t n = 0; n < N; ++n)
		printf("%" PRIu64 "\n", ps[n] = n == 0 || n == 1 || n == 2 ? 1 : ps[n - 2] + ps[n - 3]);
}
