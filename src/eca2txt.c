// eca2txt.c - print an elementary cellular automaton

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "eca.h"

#define GREATEST_HOOD 7
#define SMALLEST_HOOD 0

#define NEIGHBOR_P(hood) hood & 4
#define NEIGHBOR_Q(hood) hood & 2
#define NEIGHBOR_R(hood) hood & 1

int main(int argc, char *argv[]) {
  _Bool table      = 0;
  int   rule       = 18;
  int   seed       = 0;
  int   cell_count = 0;
  int   gen_count  = 0;
  char  *alive     = "\u2588"; // FULL BLOCK
  char  *dead      = "\u2591"; // LIGHT SHADE

  int opt;

  while ((opt = getopt(argc, argv, "a:d:r:s:c:g:t")) != -1)
    switch (opt) {
      case 'a': alive = optarg;
        break;

      case 'd': dead = optarg;
        break;

      case 'r': rule = atoi(optarg);
        break;

      case 's': seed = atoi(optarg);
        break;

      case 'c': cell_count = atoi(optarg);
        break;

      case 'g': gen_count = atoi(optarg);
        break;

      case 't': table = 1;
        break;

      default: return 1;
    }

  if (rule > 255 || rule < 0 || seed < 0)
    return 2;

  // Optionally print the rule as a truth table like this:
  // 111 110 101 100 011 010 001 000
  //  0   0   1   1   1   1   0   0
  if (table) {
    for (int h = GREATEST_HOOD; h >= SMALLEST_HOOD; --h) {
      if (h != GREATEST_HOOD)
        putchar(' ');

      fputs(NEIGHBOR_P(h) ? alive : dead, stdout);
      fputs(NEIGHBOR_Q(h) ? alive : dead, stdout);
      fputs(NEIGHBOR_R(h) ? alive : dead, stdout);
    }

    putchar('\n');

    for (int h = GREATEST_HOOD; h >= SMALLEST_HOOD; --h) {
      putchar(' ');

      if (h != GREATEST_HOOD)
        fputs("  ", stdout);

      fputs(eca_rule(rule, NEIGHBOR_P(h), NEIGHBOR_Q(h), NEIGHBOR_R(h)) ? alive : dead, stdout);
    }

    putchar('\n');
    return 0;
  }

  _Bool bad_cell_count = cell_count < 1;
  _Bool bad_gen_count  = gen_count  < 1;

  if (bad_cell_count || bad_gen_count) {
    struct winsize winsz;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz) == -1)
      return 3;

    if (bad_cell_count)
      cell_count = winsz.ws_col;

    if (bad_gen_count)
      gen_count = winsz.ws_row - 1;
  }

  _Bool *cells        = malloc(cell_count * sizeof *cells);
  _Bool *accumulators = malloc(cell_count * sizeof *accumulators);

  if (!(cells && accumulators))
    return 4;

  if (seed) {
    eca_srand(seed);

    for (int c = 0; c < cell_count; ++c)
      cells[c] = eca_rand() & 1;
  }
  else {
    for (int c = 0; c < cell_count; ++c)
      cells[c] = 0;

    cells[cell_count / 2] = 1;
  }

  int last_cell_pos = cell_count - 1;

  for (int g = 0; g < gen_count; ++g) {
    for (int c = 0; c < cell_count; ++c) {
      fputs(cells[c] ? alive : dead, stdout);

      accumulators[c] = eca_rule(rule,
        cells[c == 0 ? last_cell_pos : c - 1],
        cells[c],
        cells[c == last_cell_pos ? 0 : c + 1]);
    }

    memcpy(cells, accumulators, cell_count);
    putchar('\n');
  }
}
