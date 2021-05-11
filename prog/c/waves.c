// waves.c - write standard sine and square waves

#include <math.h>
#include <stdio.h>

#include "macros.h"

#define TAU 6.283185307

#define FREQ 440
#define RATE 44100

int main(void) {
	float sin_wave[RATE];
	float sqr_wave[RATE];

	for (unsigned i = 0; i < RATE; ++i) {
		sin_wave[i] = sin(TAU * FREQ * i / RATE);
		sqr_wave[i] = SGN(sin_wave[i]);
	}

	FILE* sin_stream = fopen("sin.flt", "wb");
	FILE* sqr_stream = fopen("sqr.flt", "wb");

	fwrite(sin_wave, sizeof *sin_wave, RATE, sin_stream);
	fwrite(sqr_wave, sizeof *sqr_wave, RATE, sqr_stream);

	fclose(sin_stream);
	fclose(sqr_stream);
}
