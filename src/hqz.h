// hqz.h - code for HQZ images

#include <stdint.h>
#include <stdlib.h>

#define Q hqz_q

#define P(id, formula)                                               \
  static void hqz_p##id(void) {                                      \
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

static void (*hqz_painters[40])(void) = {
  // AND   OR       XOR      ADD      MUL
  hqz_p0,  hqz_p1,  hqz_p2,  hqz_p3,  hqz_p4,  // Class 0
  hqz_p5,  hqz_p6,  hqz_p7,  hqz_p8,  hqz_p9,  // Class 1
  hqz_p10, hqz_p11, hqz_p12, hqz_p13, hqz_p14, // Class 2
  hqz_p15, hqz_p16, hqz_p17, hqz_p18, hqz_p19, // Class 3
  hqz_p20, hqz_p21, hqz_p22, hqz_p23, hqz_p24, // Class 4
  hqz_p25, hqz_p26, hqz_p27, hqz_p28, hqz_p29, // Class 5
  hqz_p30, hqz_p31, hqz_p32, hqz_p33, hqz_p34, // Class 6
  hqz_p35, hqz_p36, hqz_p37, hqz_p38, hqz_p39  // Class 7
};

#undef Q
#undef P
