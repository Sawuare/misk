// eca.c - code for elementary cellular automata

#include "eca.h"

#define RAND_BITS       32
#define RAND_BITS_LESS1 31

static uint32_t random = 1;

uint32_t eca_rand(void) {
  uint32_t accumulator = 0;

  for (int b = 0; b < RAND_BITS; ++b) {
    _Bool p = (uint32_t) 1 << (b == RAND_BITS_LESS1 ? 0 : b + 1) & random;
    _Bool q = (uint32_t) 1 <<                             b      & random;
    _Bool r = (uint32_t) 1 << (b == 0 ? RAND_BITS_LESS1 : b - 1) & random;

    accumulator |= (uint32_t) eca_rule30(p, q, r) << b;
  }

  return random = accumulator;
}

void eca_srand(uint32_t seed) {
  random = seed;
}
