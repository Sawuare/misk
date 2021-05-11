// padovans.c - print all Padovan numbers < 1 << 64

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define N 159

int main(void) {
	uint64_t ps[N];

	ps[0] = ps[1] = ps[2] = 1;

	for (uint8_t n = 3; n < N; ++n)
		printf("%" PRIu64 "\n", ps[n] = ps[n - 2] + ps[n - 3]);
}
