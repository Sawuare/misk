// eca.c - code for elementary cellular automata

#include "eca.h"

#define RAND_LSB 0
#define RAND_MSB 31

static uint32_t random = 1;

uint32_t eca_rand(void) {
  uint32_t accumulator = 0;

  for (int b = RAND_LSB; b <= RAND_MSB; ++b)
    accumulator |= (uint32_t) eca_rule30(
      (uint32_t) 1 << (b == RAND_MSB ? RAND_LSB : b + 1) & random,
      (uint32_t) 1 <<                             b      & random,
      (uint32_t) 1 << (b == RAND_LSB ? RAND_MSB : b - 1) & random) << b;

  return random = accumulator;
}

void eca_srand(uint32_t seed) {
  random = seed;
}
