// eca.c - code for elementary cellular automata

#include "eca.h"

#define RAND_BITS 32

static uint32_t rand = 1;

uint32_t eca_rand(void) {
  uint32_t accumulator = 0;

  for (uint32_t b = 0; b < RAND_BITS; ++b) {
    _Bool p = (uint32_t) 1 << (b == RAND_BITS - 1 ? 0 : b + 1) & rand;
    _Bool q = (uint32_t) 1 <<                           b      & rand;
    _Bool r = (uint32_t) 1 << (b == 0 ? RAND_BITS - 1 : b - 1) & rand;

    accumulator |= (uint32_t) eca_rule30(p, q, r) << b;
  }

  rand = accumulator;

  return rand;
}

void eca_srand(uint32_t seed) {
  rand = seed;
}
