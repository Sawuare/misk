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

static void write_wave(const char filename[]) {
  wafer_wave *wave = wafer_open(filename);

  if (!wave)
    exit(1);

  wafer_set_channels(wave, 1);
  wafer_set_samples_per_sec(wave, RATE);

  if (!(wafer_write_metadata(wave) &&
        wafer_write_data(audio, RATE, wave) &&
        wafer_close(wave))) {
    remove(filename);
    exit(2);
  }

  printf("Wrote %s\n", filename);
}

int main(void) {
  int i, j;

  // Square wave

  for (i = 0; i < RATE; ++i)
    audio[i] = i / PERIOD_2 % 2 ? MIN : MAX;

  write_wave("sqr.wav");

  // Saw wave

  for (i = 0; i < RATE; ++i) {
    j = i % PERIOD_2 * AMP / PERIOD_2;
    audio[i] = i / PERIOD_2 % 2 ? MIN + j : MID + j;
  }

  write_wave("saw.wav");

  // Triangle wave

  for (i = 0; i < RATE; ++i) {
    j = i % PERIOD_4 * AMP / PERIOD_4;
    j = i / PERIOD_4 % 2 ? AMP - j : j;
    audio[i] = i / PERIOD_2 % 2 ? MID - j : MID + j;
  }

  write_wave("tri.wav");
}
