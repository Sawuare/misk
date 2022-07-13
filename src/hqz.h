// hqz.h - code for HQZ images

#include <stdint.h>
#include <stdlib.h>

#define Q hqz_q

#define PAINTER(id, formula)                                         \
  static void hqz_painter##id(void) {                                \
    uint32_t yn = hqz_y0 + hqz_height;                               \
    uint32_t xn = hqz_x0 + hqz_width;                                \
                                                                     \
    for (uint32_t y = hqz_y0; y != yn; ++y)                          \
      for (uint32_t x = hqz_x0; x != xn; ++x)                        \
        hqz_canvas[(y - hqz_y0) * hqz_width + x - hqz_x0] = formula; \
  }

static uint32_t
  hqz_id     = 0,
  hqz_q      = 1,
  hqz_x0     = 0,
  hqz_y0     = 0,
  hqz_width  = 512,
  hqz_height = 512;

static _Bool *hqz_canvas;

static _Bool hqz_defined(void) {
  return hqz_id < 40 && (hqz_q || !(hqz_id / 5 % 2));
}

PAINTER(0, (x & y) & Q)
PAINTER(1, (x | y) & Q)
PAINTER(2, (x ^ y) & Q)
PAINTER(3, (x + y) & Q)
PAINTER(4, (x * y) & Q)

PAINTER(5, (x & y) % Q)
PAINTER(6, (x | y) % Q)
PAINTER(7, (x ^ y) % Q)
PAINTER(8, (x + y) % Q)
PAINTER(9, (x * y) % Q)

PAINTER(10, (x * x & y * y) & Q)
PAINTER(11, (x * x | y * y) & Q)
PAINTER(12, (x * x ^ y * y) & Q)
PAINTER(13, (x * x + y * y) & Q)
PAINTER(14, (x * x * y * y) & Q)

PAINTER(15, (x * x & y * y) % Q)
PAINTER(16, (x * x | y * y) % Q)
PAINTER(17, (x * x ^ y * y) % Q)
PAINTER(18, (x * x + y * y) % Q)
PAINTER(19, (x * x * y * y) % Q)

PAINTER(20, ((Q & x) * x & (Q & y) * y) & Q)
PAINTER(21, ((Q | x) * x & (Q | y) * y) & Q)
PAINTER(22, ((Q ^ x) * x & (Q ^ y) * y) & Q)
PAINTER(23, ((Q + x) * x & (Q + y) * y) & Q)
PAINTER(24, ((Q * x) * x & (Q * y) * y) & Q)

PAINTER(25, ((Q & x) * x & (Q & y) * y) % Q)
PAINTER(26, ((Q | x) * x & (Q | y) * y) % Q)
PAINTER(27, ((Q ^ x) * x & (Q ^ y) * y) % Q)
PAINTER(28, ((Q + x) * x & (Q + y) * y) % Q)
PAINTER(29, ((Q * x) * x & (Q * y) * y) % Q)

PAINTER(30, ((Q & x) * x + (Q & y) * y) & Q)
PAINTER(31, ((Q | x) * x + (Q | y) * y) & Q)
PAINTER(32, ((Q ^ x) * x + (Q ^ y) * y) & Q)
PAINTER(33, ((Q + x) * x + (Q + y) * y) & Q)
PAINTER(34, ((Q * x) * x + (Q * y) * y) & Q)

PAINTER(35, ((Q & x) * x + (Q & y) * y) % Q)
PAINTER(36, ((Q | x) * x + (Q | y) * y) % Q)
PAINTER(37, ((Q ^ x) * x + (Q ^ y) * y) % Q)
PAINTER(38, ((Q + x) * x + (Q + y) * y) % Q)
PAINTER(39, ((Q * x) * x + (Q * y) * y) % Q)

static void (*hqz_painters[40])(void) = {
  // AND         OR             XOR            ADD            MUL
  hqz_painter0,  hqz_painter1,  hqz_painter2,  hqz_painter3,  hqz_painter4,  // Class 0
  hqz_painter5,  hqz_painter6,  hqz_painter7,  hqz_painter8,  hqz_painter9,  // Class 1
  hqz_painter10, hqz_painter11, hqz_painter12, hqz_painter13, hqz_painter14, // Class 2
  hqz_painter15, hqz_painter16, hqz_painter17, hqz_painter18, hqz_painter19, // Class 3
  hqz_painter20, hqz_painter21, hqz_painter22, hqz_painter23, hqz_painter24, // Class 4
  hqz_painter25, hqz_painter26, hqz_painter27, hqz_painter28, hqz_painter29, // Class 5
  hqz_painter30, hqz_painter31, hqz_painter32, hqz_painter33, hqz_painter34, // Class 6
  hqz_painter35, hqz_painter36, hqz_painter37, hqz_painter38, hqz_painter39  // Class 7
};

#undef Q
#undef PAINTER
