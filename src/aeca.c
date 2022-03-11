// aeca.c - play audio elementary cellular automata

// Unsigned 8 bit, Rate 44100 Hz, Mono

#if __STDC_NO_VLA__ == 1
#error "No VLA!"
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

_Static_assert(CHAR_BIT == 8, "The width of (unsigned char) is not 8 bits!");

static inline unsigned ddig(unsigned n) {
  unsigned d = 1;

  while (n /= 10)
    ++d;

  return d;
}

int main(int argc, char *argv[]) {
  _Bool    delet      = 0;
  _Bool    quiet      = 0;
  unsigned rule       = 60;
  unsigned seed       = 0;
  unsigned cell_count = 256;
  unsigned gen_count  = 256;

  int opt;

  while ((opt = getopt(argc, argv, "r:s:c:g:dq")) != -1)
    switch (opt) {
      case 'r':
        rule = strtoul(optarg, 0, 10);
        break;

      case 's':
        seed = strtoul(optarg, 0, 10);
        break;

      case 'c':
        cell_count = strtoul(optarg, 0, 10);
        break;

      case 'g':
        gen_count = strtoul(optarg, 0, 10);
        break;

      case 'd':
        delet = 1;
        break;

      case 'q':
        quiet = 1;
        break;

      default:
        return 1;
    }

  unsigned sample_count = gen_count * cell_count;

  if (!sample_count || rule > 255)
    return 2;

  unsigned char *audio = malloc(sample_count);
  unsigned char *cells = malloc(cell_count);
  unsigned char *clone = malloc(cell_count);

  if (!audio || !cells || !clone)
    return 3;

  if (seed) {
    srand(seed);

    for (unsigned c = 0; c < cell_count; ++c)
      cells[c] = rand() & 1;
  }
  else {
    memset(cells, 0, cell_count);
    cells[cell_count / 2] = 1;
  }

  for (unsigned g = 0; g < gen_count; ++g) {
    for (unsigned c = 0; c < cell_count; ++c) {
      audio[g * cell_count + c] = cells[c] ? 255 : 0;

      // The neighbors
      unsigned char p = cells[c ? c - 1 : cell_count - 1];
      unsigned char q = cells[c];
      unsigned char r = cells[(c + 1) % cell_count];

      clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
    }

    memcpy(cells, clone, cell_count);
  }

  free(cells);
  free(clone);

  unsigned filename_size = ddig(cell_count) + ddig(gen_count) + ddig(rule) + ddig(seed) + 14;
  char filename[filename_size];
  sprintf(filename, "r%us%uc%ug%u.aeca.pcm", rule, seed, cell_count, gen_count);

  FILE *stream = fopen(filename, "wb");

  if (!stream) {
    free(audio);
    return 4;
  }

  fwrite(audio, 1, sample_count, stream);
  free(audio);
  fclose(stream);
  printf("Wrote %s\n", filename);

  if (!quiet) {
    if (system(0)) {
      char command[filename_size + 33];
      sprintf(command, "aplay -t raw -f U8 -r 44100 -c 1 %s", filename);
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
