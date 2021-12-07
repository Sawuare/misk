// hj.h - code for HJ images

#include <stdlib.h>

// The HJ color format must match that of the framebuffer for hj2fb to work

// UNPORTABLE
#define HJ_BLACK   0x000000
#define HJ_RED     0xff0000
#define HJ_GREEN   0x00ff00
#define HJ_BLUE    0x0000ff
#define HJ_CYAN    0x00ffff
#define HJ_MAGENTA 0xff00ff
#define HJ_YELLOW  0xffff00
#define HJ_WHITE   0xffffff

// UNPORTABLE
#define HJ_PX_TO_R_BYTE(px) ((px) >> 16 & 255)
#define HJ_PX_TO_G_BYTE(px) ((px) >>  8 & 255)
#define HJ_PX_TO_B_BYTE(px) ((px)       & 255)

#define HJ_IS_MONO_XOR_RAMP(id) ((id) < 45)

#define PAINTER(id) static inline void hj_p##id(void)

#define FORYX \
  unsigned yn = hj_y0 + hj_height; \
  unsigned xn = hj_x0 + hj_width; \
  for (unsigned y = hj_y0; y < yn; ++y) \
  for (unsigned x = hj_x0; x < xn; ++x)

#define SUBSCRIPT0 hj_canvas[(y - hj_y0) * hj_width + (x - hj_x0)]
#define SUBSCRIPT1 hj_canvas[(y - hj_y0) * (x - hj_x0)]

#define MONO(px) (px) ? HJ_BLACK : hj_color
#define RAMP(px) (px) % 256 * hj_color / 255 // UNPORTABLE

#define J hj_j

static inline unsigned hj_rrggbb_to_color(const char *s) {
  return strtoul(s, 0, 16); // UNPORTABLE
}

static inline unsigned hj_letter_to_color(const char *s) {
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

static unsigned
  hj_id      = 0,
  hj_j       = 0,
  hj_color   = HJ_WHITE,
  hj_x0      = 0,
  hj_y0      = 0,
  hj_width   = 512,
  hj_height  = 512,
  *hj_canvas = 0;

static inline _Bool hj_is_valid(void) {
  if (hj_id > 49)
    return 0;

  if (hj_j)
    return 1;

  unsigned class = hj_id / 5;

  if (class == 2 || class == 4 || class == 6 || class == 8)
    return 0;

  return 1;
}

// Class 0

PAINTER(0) {
  FORYX {
    SUBSCRIPT0 = HJ_BLACK;
    SUBSCRIPT1 = hj_color;
  }
}

PAINTER(1) {
}

PAINTER(2) {
}

PAINTER(3) {
}

PAINTER(4) {
}

// Class 1

PAINTER(5) {
  FORYX
    SUBSCRIPT0 = MONO((x & y) & J);
}

PAINTER(6) {
  FORYX
    SUBSCRIPT0 = MONO((x | y) & J);
}

PAINTER(7) {
  FORYX
    SUBSCRIPT0 = MONO((x ^ y) & J);
}

PAINTER(8) {
  FORYX
    SUBSCRIPT0 = MONO((x + y) & J);
}

PAINTER(9) {
  FORYX
    SUBSCRIPT0 = MONO((x * y) & J);
}

// Class 2

PAINTER(10) {
  FORYX
    SUBSCRIPT0 = MONO((x & y) % J);
}

PAINTER(11) {
  FORYX
    SUBSCRIPT0 = MONO((x | y) % J);
}

PAINTER(12) {
  FORYX
    SUBSCRIPT0 = MONO((x ^ y) % J);
}

PAINTER(13) {
  FORYX
    SUBSCRIPT0 = MONO((x + y) % J);
}

PAINTER(14) {
  FORYX
    SUBSCRIPT0 = MONO((x * y) % J);
}

// Class 3

PAINTER(15) {
  FORYX
    SUBSCRIPT0 = MONO((x * x & y * y) & J);
}

PAINTER(16) {
  FORYX
    SUBSCRIPT0 = MONO((x * x | y * y) & J);
}

PAINTER(17) {
  FORYX
    SUBSCRIPT0 = MONO((x * x ^ y * y) & J);
}

PAINTER(18) {
  FORYX
    SUBSCRIPT0 = MONO((x * x + y * y) & J);
}

PAINTER(19) {
  FORYX
    SUBSCRIPT0 = MONO((x * x * y * y) & J);
}

// Class 4

PAINTER(20) {
  FORYX
    SUBSCRIPT0 = MONO((x * x & y * y) % J);
}

PAINTER(21) {
  FORYX
    SUBSCRIPT0 = MONO((x * x | y * y) % J);
}

PAINTER(22) {
  FORYX
    SUBSCRIPT0 = MONO((x * x ^ y * y) % J);
}

PAINTER(23) {
  FORYX
    SUBSCRIPT0 = MONO((x * x + y * y) % J);
}

PAINTER(24) {
  FORYX
    SUBSCRIPT0 = MONO((x * x * y * y) % J);
}

// Class 5

PAINTER(25) {
  FORYX
    SUBSCRIPT0 = MONO(((J & x) * x & (J & y) * y) & J);
}

PAINTER(26) {
  FORYX
    SUBSCRIPT0 = MONO(((J | x) * x & (J | y) * y) & J);
}

PAINTER(27) {
  FORYX
    SUBSCRIPT0 = MONO(((J ^ x) * x & (J ^ y) * y) & J);
}

PAINTER(28) {
  FORYX
    SUBSCRIPT0 = MONO(((J + x) * x & (J + y) * y) & J);
}

PAINTER(29) {
  FORYX
    SUBSCRIPT0 = MONO(((J * x) * x & (J * y) * y) & J);
}

// Class 6

PAINTER(30) {
  FORYX
    SUBSCRIPT0 = MONO(((J & x) * x & (J & y) * y) % J);
}

PAINTER(31) {
  FORYX
    SUBSCRIPT0 = MONO(((J | x) * x & (J | y) * y) % J);
}

PAINTER(32) {
  FORYX
    SUBSCRIPT0 = MONO(((J ^ x) * x & (J ^ y) * y) % J);
}

PAINTER(33) {
  FORYX
    SUBSCRIPT0 = MONO(((J + x) * x & (J + y) * y) % J);
}

PAINTER(34) {
  FORYX
    SUBSCRIPT0 = MONO(((J * x) * x & (J * y) * y) % J);
}

// Class 7

PAINTER(35) {
  FORYX
    SUBSCRIPT0 = MONO(((J & x) * x + (J & y) * y) & J);
}

PAINTER(36) {
  FORYX
    SUBSCRIPT0 = MONO(((J | x) * x + (J | y) * y) & J);
}

PAINTER(37) {
  FORYX
    SUBSCRIPT0 = MONO(((J ^ x) * x + (J ^ y) * y) & J);
}

PAINTER(38) {
  FORYX
    SUBSCRIPT0 = MONO(((J + x) * x + (J + y) * y) & J);
}

PAINTER(39) {
  FORYX
    SUBSCRIPT0 = MONO(((J * x) * x + (J * y) * y) & J);
}

// Class 8

PAINTER(40) {
  FORYX
    SUBSCRIPT0 = MONO(((J & x) * x + (J & y) * y) % J);
}

PAINTER(41) {
  FORYX
    SUBSCRIPT0 = MONO(((J | x) * x + (J | y) * y) % J);
}

PAINTER(42) {
  FORYX
    SUBSCRIPT0 = MONO(((J ^ x) * x + (J ^ y) * y) % J);
}

PAINTER(43) {
  FORYX
    SUBSCRIPT0 = MONO(((J + x) * x + (J + y) * y) % J);
}

PAINTER(44) {
  FORYX
    SUBSCRIPT0 = MONO(((J * x) * x + (J * y) * y) % J);
}

// Class 9

PAINTER(45) {
  FORYX
    SUBSCRIPT0 = RAMP((J & x) * x + (J & y) * y);
}

PAINTER(46) {
  FORYX
    SUBSCRIPT0 = RAMP((J | x) * x + (J | y) * y);
}

PAINTER(47) {
  FORYX
    SUBSCRIPT0 = RAMP((J ^ x) * x + (J ^ y) * y);
}

PAINTER(48) {
  FORYX
    SUBSCRIPT0 = RAMP((J + x) * x + (J + y) * y);
}

PAINTER(49) {
  FORYX
    SUBSCRIPT0 = RAMP((J * x) * x + (J * y) * y);
}

static void (*hj_painters[])(void) = {
  hj_p0,  hj_p1,  hj_p2,  hj_p3,  hj_p4,  hj_p5,  hj_p6,  hj_p7,  hj_p8,  hj_p9,
  hj_p10, hj_p11, hj_p12, hj_p13, hj_p14, hj_p15, hj_p16, hj_p17, hj_p18, hj_p19,
  hj_p20, hj_p21, hj_p22, hj_p23, hj_p24, hj_p25, hj_p26, hj_p27, hj_p28, hj_p29,
  hj_p30, hj_p31, hj_p32, hj_p33, hj_p34, hj_p35, hj_p36, hj_p37, hj_p38, hj_p39,
  hj_p40, hj_p41, hj_p42, hj_p43, hj_p44, hj_p45, hj_p46, hj_p47, hj_p48, hj_p49
};

#undef PAINTER
#undef FORYX
#undef SUBSCRIPT0
#undef SUBSCRIPT1
#undef MONO
#undef RAMP
#undef J
