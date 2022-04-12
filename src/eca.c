// eca.c - code for elementary cellular automata

#include "eca.h"

#define RAND_BITS_LESS1 31

static uint32_t random = 1;

uint32_t eca_rand(void) {
  uint32_t accumulator = 0;

  for (int b = 0; b <= RAND_BITS_LESS1; ++b)
    accumulator |= (uint32_t) eca_rule30(
      (uint32_t) 1 << (b == RAND_BITS_LESS1 ? 0 : b + 1) & random,
      (uint32_t) 1 <<                             b      & random,
      (uint32_t) 1 << (b == 0 ? RAND_BITS_LESS1 : b - 1) & random) << b;

  return random = accumulator;
}

void eca_srand(uint32_t seed) {
  random = seed;
}
