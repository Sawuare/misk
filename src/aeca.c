// aeca.c - play audio elementary cellular automata

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
  _Bool    delet   = 0;
  _Bool    quiet   = 0;
  unsigned n_cells = 256;
  unsigned n_gens  = 256;
  unsigned rule    = 60;
  unsigned seed    = 0;

  int opt;

  while ((opt = getopt(argc, argv, "c:g:r:s:dq")) != -1)
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

      case 'd':
        delet = 1;
        break;

      case 'q':
        quiet = 1;
        break;

      default:
        return 1;
    }

  if (!n_cells || !n_gens || rule > 255)
    return 2;

  unsigned n_samples = n_gens * n_cells;

  unsigned char* audio = malloc(n_samples);
  unsigned char* cells = malloc(n_cells);
  unsigned char* clone = malloc(n_cells);

  if (!audio || !cells || !clone)
    return 3;

  if (seed) {
    srand(seed);
    for (unsigned c = 0; c < n_cells; ++c)
      cells[c] = rand() & 1;
  }
  else {
    memset(cells, 0, n_cells);
    cells[n_cells / 2] = 1;
  }

  for (unsigned g = 0; g < n_gens; ++g) {
    for (unsigned c = 0; c < n_cells; ++c) {
      audio[g * n_cells + c] = cells[c] ? 255 : 0;

      unsigned char p = cells[c ? c - 1 : n_cells - 1];
      unsigned char q = cells[c];
      unsigned char r = cells[(c + 1) % n_cells];

      clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
    }

    memcpy(cells, clone, n_cells);
  }

  free(cells);
  free(clone);

  unsigned l_filename = ddig(n_cells) + ddig(n_gens) + ddig(rule) + ddig(seed) + 14;
  char filename[l_filename];
  snprintf(filename, l_filename, "c%ug%ur%us%u.aeca.pcm", n_cells, n_gens, rule, seed);

  FILE* stream = fopen(filename, "wb");

  if (!stream) {
    free(audio);
    return 4;
  }

  fwrite(audio, 1, n_samples, stream);
  fclose(stream);
  free(audio);

  printf("Wrote %s\n", filename);

  if (!quiet) {
    if (system(0)) {
      unsigned l_command = l_filename + 33;
      char command[l_command];
      snprintf(command, l_command, "aplay -t raw -f U8 -r 44100 -c 1 %s", filename);
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
