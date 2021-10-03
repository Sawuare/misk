// waves.c - write some fixed audio waves in the FLAC format

// Signed 16 bit, Rate 44100 Hz, Mono

#include <stdio.h>
#include <stdlib.h>

#include <FLAC/stream_encoder.h>

#define MAX +32767
#define MIN -32767

#define RATE 44100
#define FREQ 440

static FLAC__int32 wave[RATE];
static FLAC__StreamEncoder *encoder;

static void write_wave(char *filename) {
  FLAC__stream_encoder_set_verify(encoder, true);
  FLAC__stream_encoder_set_channels(encoder, 1);
  FLAC__stream_encoder_set_sample_rate(encoder, RATE);
  FLAC__stream_encoder_set_bits_per_sample(encoder, 16);
  FLAC__stream_encoder_set_compression_level(encoder, 0);
  FLAC__stream_encoder_set_total_samples_estimate(encoder, RATE);

  if (FLAC__stream_encoder_init_file(encoder, filename, 0, 0) != FLAC__STREAM_ENCODER_INIT_STATUS_OK)
    exit(2);

  if (!FLAC__stream_encoder_process_interleaved(encoder, wave, RATE))
    exit(3);

  if (!FLAC__stream_encoder_finish(encoder))
    exit(4);

  static int counter = 1;

  printf("Wrote %d of 2: %s\n", counter++, filename);
}

int main(void) {
  encoder = FLAC__stream_encoder_new();

  if (!encoder)
    return 1;

  FLAC__int32 i, j, period_2 = RATE / FREQ / 2, period_4 = period_2 / 2;

  // Square wave

  for (i = 0; i < RATE; ++i)
    wave[i] = i / period_2 % 2 ? MIN : MAX;

  write_wave("sqr.flac");

  // Triangle wave

  for (i = 0; i < RATE; ++i) {
    j = i % period_4 * (MAX / period_4);
    j = i / period_4 % 2 ? MAX - j : j;
    wave[i] = i / period_2 % 2 ? -j : j;
  }

  write_wave("tri.flac");

  FLAC__stream_encoder_delete(encoder);
}
