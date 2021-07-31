// aeca.c - play audible elementary cellular automata

// Unsigned 8 bit, Rate 44100 Hz, Mono

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

static inline unsigned ddig(unsigned n) {
  unsigned d = 1;

  while (n /= 10)
    ++d;

  return d;
}

int main(int argc, char* argv[argc + 1]) {
  unsigned n_cells = 1024;
  unsigned n_gens  = 512;
  unsigned rule    = 90;
  unsigned seed    = 0;

  int opt;

  while ((opt = getopt(argc, argv, "c:g:r:s:")) != -1)
    switch (opt) {
      case 'c':
        n_cells = strtoul(optarg, 0, 10);
        break;

      case 'g':
        n_gens = strtoul(optarg, 0, 10);
        break;

      case 'r':
        rule = strtoul(optarg, 0, 10);
        break;

      case 's':
        seed = strtoul(optarg, 0, 10);
        break;

      default:
        return 1;
    }

  unsigned n_samples = n_gens * n_cells;

  unsigned char* audio = malloc(n_samples);

  _Bool cells[n_cells];
  _Bool clone[n_cells];

  if (seed) {
    srand(seed);
    for (unsigned c = 0; c < n_cells; ++c)
      cells[c] = rand() & 1;
  }
  else {
    memset(cells, 0, sizeof cells);
    cells[n_cells / 2] = 1;
  }

  for (unsigned g = 0; g < n_gens; ++g) {
    for (unsigned c = 0; c < n_cells; ++c) {
      audio[g * n_cells + c] = cells[c] ? 255 : 0;

      _Bool p = cells[c ? c - 1 : n_cells - 1];
      _Bool q = cells[c];
      _Bool r = cells[(c + 1) % n_cells];

      clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
    }

    memcpy(cells, clone, sizeof clone);
  }

  unsigned l_filename = ddig(n_cells) + ddig(n_gens) + ddig(rule) + ddig(seed) + 14;
  unsigned l_command = l_filename + 28;

  char filename[l_filename];
  char command[l_command];

  snprintf(filename, l_filename, "c%ug%ur%us%u.aeca.pcm", n_cells, n_gens, rule, seed);
  snprintf(command, l_command, "aplay -t raw -f U8 -r 44100 %s", filename);

  FILE* stream = fopen(filename, "wb");

  if (!stream) {
    free(audio);
    return 2;
  }

  fwrite(audio, 1, n_samples, stream);
  fclose(stream);

  printf("Wrote '%s'\n", filename);

  free(audio);

  if (system(0))
    // Depend on aplay for playing raw audio
    system(command);
}
