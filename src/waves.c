// waves.c - write some fixed audio waves in the WAVE format

// Unsigned 8 bit, Rate 44100 Hz, Mono

#include <stdint.h>
#include <stdio.h>

#include "wafer.h"

#define WAVE_COUNT "2"

#define RATE 44100
#define FREQ 440

#define MAX 255
#define MID 128
#define MIN 1

static uint8_t data[RATE];

static void write_wave(const char *filename) {
  wafer_wave *wave = wafer_open(filename);
  wafer_set_channels(wave, 1);
  wafer_set_samples_per_sec(wave, RATE);
  wafer_write_metadata(wave);
  wafer_write_data(data, RATE, wave);
  wafer_close(wave);

  static int wave_counter = 1;

  printf("Wrote %d of " WAVE_COUNT ": %s\n", wave_counter++, filename);
}

int main(void) {
  int i, j;
  int period_2 = RATE / FREQ / 2, period_4 = period_2 / 2;
  int max_offset = MID - 1;

  // Square wave

  for (i = 0; i < RATE; ++i)
    data[i] = i / period_2 % 2 ? MIN : MAX;

  write_wave("sqr.wav");

  // Triangle wave

  for (i = 0; i < RATE; ++i) {
    j = i % period_4 * max_offset / period_4;
    j = i / period_4 % 2 ? max_offset - j : j;
    data[i] = i / period_2 % 2 ? MID - j : MID + j;
  }

  write_wave("tri.wav");
}
