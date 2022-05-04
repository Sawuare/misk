// aeca.c - play audio elementary cellular automata

// Unsigned 8 bit, Rate 44100 Hz, Mono

#include <inttypes.h>
#include <limits.h>
#include <string.h>

#include <getopt.h>

#include "eca.h"
#include "wafer.h"

int main(int argc, char *argv[]) {
  _Bool    delet      = 0;
  _Bool    quiet      = 0;
  uint8_t  rule       = 60;
  uint32_t seed       = 0;
  uint32_t cell_count = 256;
  uint32_t gen_count  = 256;

  int opt;

  while ((opt = getopt(argc, argv, "r:s:c:g:dq")) != -1)
    switch (opt) {
      case 'r': rule = strtoul(optarg, 0, 10);
        break;

      case 's': seed = strtoul(optarg, 0, 10);
        break;

      case 'c': cell_count = strtoul(optarg, 0, 10);
        break;

      case 'g': gen_count = strtoul(optarg, 0, 10);
        break;

      case 'd': delet = 1;
        break;

      case 'q': quiet = 1;
        break;

      default: return 1;
    }

  size_t sample_count = gen_count * cell_count;

  if (!sample_count)
    return 2;

  uint8_t *audio = malloc(sample_count);

  _Bool *cells        = malloc(cell_count);
  _Bool *accumulators = malloc(cell_count);

  if (!(audio && cells && accumulators))
    return 3;

  if (seed) {
    eca_srand(seed);

    for (uint32_t c = 0; c < cell_count; ++c)
      cells[c] = eca_rand() & 1;
  }
  else {
    memset(cells, 0, cell_count);
    cells[cell_count / 2] = 1;
  }

  uint32_t last_cell_pos = cell_count - 1;

  for (uint32_t g = 0; g < gen_count; ++g) {
    for (uint32_t c = 0; c < cell_count; ++c) {
      audio[g * cell_count + c] = cells[c] ? 255 : 1;

      accumulators[c] = eca_rule(rule,
        cells[c == 0 ? last_cell_pos : c - 1],
        cells[c],
        cells[c == last_cell_pos ? 0 : c + 1]);
    }

    memcpy(cells, accumulators, cell_count);
  }

  free(cells);
  free(accumulators);

  // The longest filename is
  // r100s1000000000c1000000000g1000000000.aeca.wav
  char filename[47];
  sprintf(filename, "r%" PRIu8 "s%" PRIu32 "c%" PRIu32 "g%" PRIu32 ".aeca.wav",
    rule, seed, cell_count, gen_count);

  wafer_wave *wave = wafer_open(filename);

  if (!wave) {
    free(audio);
    return 4;
  }

  wafer_set_channels(wave, 1);
  wafer_set_samples_per_sec(wave, 44100);
  wafer_write_metadata(wave);
  wafer_write_data(audio, sample_count, wave);
  wafer_close(wave);
  free(audio);
  printf("Wrote %s\n", filename);

  if (!quiet) {
    if (system(0)) {
      char command[sizeof filename + 6];
      sprintf(command, "aplay %s", filename);
      system(command);
    }
    else
      return 5;
  }

  if (delet) {
    remove(filename);
    printf("Deleted %s\n", filename);
  }
}
