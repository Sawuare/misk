// waves.c - write some fixed classic audio waves to WAVE files

#include <stdint.h>
#include <stdio.h>

#include "wafer.h"

#define RATE 44100

#define PERIOD_2 50
#define PERIOD_4 25

#define AMP 127
#define MAX 255
#define MID 128
#define MIN 1

static uint8_t audio[RATE];

static void write_wave(const char *filename) {
  wafer_wave *wave = wafer_open(filename);
  wafer_set_channels(wave, 1);
  wafer_set_samples_per_sec(wave, RATE);
  wafer_write_metadata(wave);
  wafer_write_data(audio, RATE, wave);
  wafer_close(wave);

  static int wave_counter = 1;

  printf("Wrote %d of 2: %s\n", wave_counter++, filename);
}

int main(void) {
  int i, j;

  // Square wave

  for (i = 0; i < RATE; ++i)
    audio[i] = i / PERIOD_2 % 2 ? MIN : MAX;

  write_wave("sqr.wav");

  // Triangle wave

  for (i = 0; i < RATE; ++i) {
    j = i % PERIOD_4 * AMP / PERIOD_4;
    j = i / PERIOD_4 % 2 ? AMP - j : j;
    audio[i] = i / PERIOD_2 % 2 ? MID - j : MID + j;
  }

  write_wave("tri.wav");
}
