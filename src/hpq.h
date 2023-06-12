// hpq.h - code for HPQ images

#include <stdint.h>
#include <stdlib.h>

#define Q hpq_q

#define P(id, formula)                                               \
  static void hpq_p##id(void) {                                      \
    uint32_t yn = hpq_y0 + hpq_height;                               \
    uint32_t xn = hpq_x0 + hpq_width;                                \
                                                                     \
    for (uint32_t y = hpq_y0; y != yn; ++y)                          \
      for (uint32_t x = hpq_x0; x != xn; ++x)                        \
        hpq_canvas[(y - hpq_y0) * hpq_width + x - hpq_x0] = formula; \
  }

static uint32_t hpq_id     = 0;
static uint32_t hpq_q      = 1;
static uint32_t hpq_x0     = 0;
static uint32_t hpq_y0     = 0;
static uint32_t hpq_width  = 256;
static uint32_t hpq_height = 256;

static _Bool *hpq_canvas;

static _Bool hpq_defined(void) {
  return hpq_id < 40 && (hpq_q || !(hpq_id / 5 % 2));
}

P(0, (x & y) & Q)
P(1, (x | y) & Q)
P(2, (x ^ y) & Q)
P(3, (x + y) & Q)
P(4, (x * y) & Q)

P(5, (x & y) % Q)
P(6, (x | y) % Q)
P(7, (x ^ y) % Q)
P(8, (x + y) % Q)
P(9, (x * y) % Q)

P(10, (x * x & y * y) & Q)
P(11, (x * x | y * y) & Q)
P(12, (x * x ^ y * y) & Q)
P(13, (x * x + y * y) & Q)
P(14, (x * x * y * y) & Q)

P(15, (x * x & y * y) % Q)
P(16, (x * x | y * y) % Q)
P(17, (x * x ^ y * y) % Q)
P(18, (x * x + y * y) % Q)
P(19, (x * x * y * y) % Q)

P(20, ((Q & x) * x & (Q & y) * y) & Q)
P(21, ((Q | x) * x & (Q | y) * y) & Q)
P(22, ((Q ^ x) * x & (Q ^ y) * y) & Q)
P(23, ((Q + x) * x & (Q + y) * y) & Q)
P(24, ((Q * x) * x & (Q * y) * y) & Q)

P(25, ((Q & x) * x & (Q & y) * y) % Q)
P(26, ((Q | x) * x & (Q | y) * y) % Q)
P(27, ((Q ^ x) * x & (Q ^ y) * y) % Q)
P(28, ((Q + x) * x & (Q + y) * y) % Q)
P(29, ((Q * x) * x & (Q * y) * y) % Q)

P(30, ((Q & x) * x + (Q & y) * y) & Q)
P(31, ((Q | x) * x + (Q | y) * y) & Q)
P(32, ((Q ^ x) * x + (Q ^ y) * y) & Q)
P(33, ((Q + x) * x + (Q + y) * y) & Q)
P(34, ((Q * x) * x + (Q * y) * y) & Q)

P(35, ((Q & x) * x + (Q & y) * y) % Q)
P(36, ((Q | x) * x + (Q | y) * y) % Q)
P(37, ((Q ^ x) * x + (Q ^ y) * y) % Q)
P(38, ((Q + x) * x + (Q + y) * y) % Q)
P(39, ((Q * x) * x + (Q * y) * y) % Q)

static void (*hpq_painters[40])(void) = {
  // &        |        ^        +        *
  hpq_p0,  hpq_p1,  hpq_p2,  hpq_p3,  hpq_p4,  // Class 0
  hpq_p5,  hpq_p6,  hpq_p7,  hpq_p8,  hpq_p9,  // Class 1
  hpq_p10, hpq_p11, hpq_p12, hpq_p13, hpq_p14, // Class 2
  hpq_p15, hpq_p16, hpq_p17, hpq_p18, hpq_p19, // Class 3
  hpq_p20, hpq_p21, hpq_p22, hpq_p23, hpq_p24, // Class 4
  hpq_p25, hpq_p26, hpq_p27, hpq_p28, hpq_p29, // Class 5
  hpq_p30, hpq_p31, hpq_p32, hpq_p33, hpq_p34, // Class 6
  hpq_p35, hpq_p36, hpq_p37, hpq_p38, hpq_p39  // Class 7
};

#undef Q
#undef P
