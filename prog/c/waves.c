// waves.c - write standard sine and square waves

#include <math.h>
#include <stdio.h>

#include "macros.h"

#define TAU 6.283185307

#define F 440
#define N 44100

int main(void) {
	float sin_wave[N];
	float sqr_wave[N];

	for (int n = 0; n < N; ++n) {
		sin_wave[n] = sin(TAU * F * n / N);
		sqr_wave[n] = SGN(sin_wave[n]);
	}

	FILE* sin_stream = fopen("sin.flt", "wb");
	FILE* sqr_stream = fopen("sqr.flt", "wb");

	fwrite(sin_wave, sizeof *sin_wave, N, sin_stream);
	fwrite(sqr_wave, sizeof *sqr_wave, N, sqr_stream);

	fclose(sin_stream);
	fclose(sqr_stream);
}
