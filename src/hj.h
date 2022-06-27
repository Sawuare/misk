// hj.h - code for HJ images

#include <stdint.h>
#include <stdlib.h>

#define J hj_j

#define PAINTER(id, formula)                                     \
  static void hj_painter##id(void) {                             \
    uint32_t yn = hj_y0 + hj_height;                             \
    uint32_t xn = hj_x0 + hj_width;                              \
                                                                 \
    for (uint32_t y = hj_y0; y != yn; ++y)                       \
      for (uint32_t x = hj_x0; x != xn; ++x)                     \
        hj_canvas[(y - hj_y0) * hj_width + x - hj_x0] = formula; \
  }

static uint32_t
  hj_id      = 0,
  hj_j       = 1,
  hj_x0      = 0,
  hj_y0      = 0,
  hj_width   = 512,
  hj_height  = 512;

static _Bool *hj_canvas;

static _Bool hj_defined(void) {
  return hj_id < 40 && (hj_j || !(hj_id / 5 % 2));
}

PAINTER(0, (x & y) & J)
PAINTER(1, (x | y) & J)
PAINTER(2, (x ^ y) & J)
PAINTER(3, (x + y) & J)
PAINTER(4, (x * y) & J)

PAINTER(5, (x & y) % J)
PAINTER(6, (x | y) % J)
PAINTER(7, (x ^ y) % J)
PAINTER(8, (x + y) % J)
PAINTER(9, (x * y) % J)

PAINTER(10, (x * x & y * y) & J)
PAINTER(11, (x * x | y * y) & J)
PAINTER(12, (x * x ^ y * y) & J)
PAINTER(13, (x * x + y * y) & J)
PAINTER(14, (x * x * y * y) & J)

PAINTER(15, (x * x & y * y) % J)
PAINTER(16, (x * x | y * y) % J)
PAINTER(17, (x * x ^ y * y) % J)
PAINTER(18, (x * x + y * y) % J)
PAINTER(19, (x * x * y * y) % J)

PAINTER(20, ((J & x) * x & (J & y) * y) & J)
PAINTER(21, ((J | x) * x & (J | y) * y) & J)
PAINTER(22, ((J ^ x) * x & (J ^ y) * y) & J)
PAINTER(23, ((J + x) * x & (J + y) * y) & J)
PAINTER(24, ((J * x) * x & (J * y) * y) & J)

PAINTER(25, ((J & x) * x & (J & y) * y) % J)
PAINTER(26, ((J | x) * x & (J | y) * y) % J)
PAINTER(27, ((J ^ x) * x & (J ^ y) * y) % J)
PAINTER(28, ((J + x) * x & (J + y) * y) % J)
PAINTER(29, ((J * x) * x & (J * y) * y) % J)

PAINTER(30, ((J & x) * x + (J & y) * y) & J)
PAINTER(31, ((J | x) * x + (J | y) * y) & J)
PAINTER(32, ((J ^ x) * x + (J ^ y) * y) & J)
PAINTER(33, ((J + x) * x + (J + y) * y) & J)
PAINTER(34, ((J * x) * x + (J * y) * y) & J)

PAINTER(35, ((J & x) * x + (J & y) * y) % J)
PAINTER(36, ((J | x) * x + (J | y) * y) % J)
PAINTER(37, ((J ^ x) * x + (J ^ y) * y) % J)
PAINTER(38, ((J + x) * x + (J + y) * y) % J)
PAINTER(39, ((J * x) * x + (J * y) * y) % J)

static void (*hj_painters[40])(void) = {
  // AND           OR            XOR           ADD           MUL
  hj_painter0,  hj_painter1,  hj_painter2,  hj_painter3,  hj_painter4,  // Class 0
  hj_painter5,  hj_painter6,  hj_painter7,  hj_painter8,  hj_painter9,  // Class 1
  hj_painter10, hj_painter11, hj_painter12, hj_painter13, hj_painter14, // Class 2
  hj_painter15, hj_painter16, hj_painter17, hj_painter18, hj_painter19, // Class 3
  hj_painter20, hj_painter21, hj_painter22, hj_painter23, hj_painter24, // Class 4
  hj_painter25, hj_painter26, hj_painter27, hj_painter28, hj_painter29, // Class 5
  hj_painter30, hj_painter31, hj_painter32, hj_painter33, hj_painter34, // Class 6
  hj_painter35, hj_painter36, hj_painter37, hj_painter38, hj_painter39, // Class 7
};

#undef J
#undef PAINTER
