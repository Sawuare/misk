// hj.h - code for HJ images

#include <stdint.h>
#include <stdlib.h>

// The color format is 24-bit RGB

#define HJ_BLACK   0x000000
#define HJ_RED     0xff0000
#define HJ_GREEN   0x00ff00
#define HJ_BLUE    0x0000ff
#define HJ_CYAN    0x00ffff
#define HJ_MAGENTA 0xff00ff
#define HJ_YELLOW  0xffff00
#define HJ_WHITE   0xffffff

#define HJ_PX_TO_R_BYTE(px) ((px) >> 16 & 255)
#define HJ_PX_TO_G_BYTE(px) ((px) >>  8 & 255)
#define HJ_PX_TO_B_BYTE(px) ((px)       & 255)

#define PAINTER(id, formula)                                     \
  static inline void hj_painter##id(void) {                      \
    uint32_t yn = hj_y0 + hj_height;                             \
    uint32_t xn = hj_x0 + hj_width;                              \
                                                                 \
    for (uint32_t y = hj_y0; y < yn; ++y)                        \
      for (uint32_t x = hj_x0; x < xn; ++x)                      \
        hj_canvas[(y - hj_y0) * hj_width + x - hj_x0] = formula; \
  }

#define MONO(value) (value) ? HJ_BLACK : hj_color
#define RAMP(value) (value) % 256 * hj_color / 255

#define J hj_j

static inline uint32_t hj_rrggbb_to_color(const char *s) {
  return strtoul(s, 0, 16);
}

static inline uint32_t hj_letter_to_color(const char *s) {
  switch (*s) {
    case 'r': return HJ_RED;
    case 'g': return HJ_GREEN;
    case 'b': return HJ_BLUE;
    case 'c': return HJ_CYAN;
    case 'm': return HJ_MAGENTA;
    case 'y': return HJ_YELLOW;
    default:  return HJ_WHITE;
  }
}

static uint32_t
  hj_id      = 0,
  hj_j       = 1,
  hj_color   = HJ_WHITE,
  hj_x0      = 0,
  hj_y0      = 0,
  hj_width   = 512,
  hj_height  = 512,
  *hj_canvas = 0;

static inline _Bool hj_is_mono_xor_ramp(void) {
  return hj_id < 40;
}

static inline _Bool hj_is_defined(void) {
  if (hj_id > 44)
    return 0;

  if (hj_j)
    return 1;

  uint32_t class = hj_id / 5;

  if (class == 1 || class == 3 || class == 5 || class == 7)
    return 0;

  return 1;
}

// Class 0
PAINTER(0, MONO((x & y) & J))
PAINTER(1, MONO((x | y) & J))
PAINTER(2, MONO((x ^ y) & J))
PAINTER(3, MONO((x + y) & J))
PAINTER(4, MONO((x * y) & J))

// Class 1
PAINTER(5, MONO((x & y) % J))
PAINTER(6, MONO((x | y) % J))
PAINTER(7, MONO((x ^ y) % J))
PAINTER(8, MONO((x + y) % J))
PAINTER(9, MONO((x * y) % J))

// Class 2
PAINTER(10, MONO((x * x & y * y) & J))
PAINTER(11, MONO((x * x | y * y) & J))
PAINTER(12, MONO((x * x ^ y * y) & J))
PAINTER(13, MONO((x * x + y * y) & J))
PAINTER(14, MONO((x * x * y * y) & J))

// Class 3
PAINTER(15, MONO((x * x & y * y) % J))
PAINTER(16, MONO((x * x | y * y) % J))
PAINTER(17, MONO((x * x ^ y * y) % J))
PAINTER(18, MONO((x * x + y * y) % J))
PAINTER(19, MONO((x * x * y * y) % J))

// Class 4
PAINTER(20, MONO(((J & x) * x & (J & y) * y) & J))
PAINTER(21, MONO(((J | x) * x & (J | y) * y) & J))
PAINTER(22, MONO(((J ^ x) * x & (J ^ y) * y) & J))
PAINTER(23, MONO(((J + x) * x & (J + y) * y) & J))
PAINTER(24, MONO(((J * x) * x & (J * y) * y) & J))

// Class 5
PAINTER(25, MONO(((J & x) * x & (J & y) * y) % J))
PAINTER(26, MONO(((J | x) * x & (J | y) * y) % J))
PAINTER(27, MONO(((J ^ x) * x & (J ^ y) * y) % J))
PAINTER(28, MONO(((J + x) * x & (J + y) * y) % J))
PAINTER(29, MONO(((J * x) * x & (J * y) * y) % J))

// Class 6
PAINTER(30, MONO(((J & x) * x + (J & y) * y) & J))
PAINTER(31, MONO(((J | x) * x + (J | y) * y) & J))
PAINTER(32, MONO(((J ^ x) * x + (J ^ y) * y) & J))
PAINTER(33, MONO(((J + x) * x + (J + y) * y) & J))
PAINTER(34, MONO(((J * x) * x + (J * y) * y) & J))

// Class 7
PAINTER(35, MONO(((J & x) * x + (J & y) * y) % J))
PAINTER(36, MONO(((J | x) * x + (J | y) * y) % J))
PAINTER(37, MONO(((J ^ x) * x + (J ^ y) * y) % J))
PAINTER(38, MONO(((J + x) * x + (J + y) * y) % J))
PAINTER(39, MONO(((J * x) * x + (J * y) * y) % J))

// Class 8
PAINTER(40, RAMP((J & x) * x + (J & y) * y))
PAINTER(41, RAMP((J | x) * x + (J | y) * y))
PAINTER(42, RAMP((J ^ x) * x + (J ^ y) * y))
PAINTER(43, RAMP((J + x) * x + (J + y) * y))
PAINTER(44, RAMP((J * x) * x + (J * y) * y))

static void (*hj_painters[])(void) = {
  // AND           OR            XOR           ADD           MUL
  hj_painter0,  hj_painter1,  hj_painter2,  hj_painter3,  hj_painter4,  // Class 0
  hj_painter5,  hj_painter6,  hj_painter7,  hj_painter8,  hj_painter9,  // Class 1
  hj_painter10, hj_painter11, hj_painter12, hj_painter13, hj_painter14, // Class 2
  hj_painter15, hj_painter16, hj_painter17, hj_painter18, hj_painter19, // Class 3
  hj_painter20, hj_painter21, hj_painter22, hj_painter23, hj_painter24, // Class 4
  hj_painter25, hj_painter26, hj_painter27, hj_painter28, hj_painter29, // Class 5
  hj_painter30, hj_painter31, hj_painter32, hj_painter33, hj_painter34, // Class 6
  hj_painter35, hj_painter36, hj_painter37, hj_painter38, hj_painter39, // Class 7
  hj_painter40, hj_painter41, hj_painter42, hj_painter43, hj_painter44  // Class 8
};

#undef PAINTER
#undef MONO
#undef RAMP
#undef J
