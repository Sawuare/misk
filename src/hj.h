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
  unsigned yn = y0 + height; \
  unsigned xn = x0 + width; \
  for (unsigned y = y0; y < yn; ++y) \
  for (unsigned x = x0; x < xn; ++x)

#define SUBSCRIPT0 (y - y0) * width + (x - x0)
#define SUBSCRIPT1 (y - y0) * (x - x0)

#define MONO(px) (px) ? HJ_BLACK : color
#define RAMP(px) (px) % 256 * color / 255 // UNPORTABLE

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

static unsigned id = 0, j = 0, color = HJ_WHITE, x0 = 0, y0 = 0, width = 512, height = 512, *canvas = 0;

static inline _Bool hj_is_valid(void) {
  if (id > 49)
    return 0;

  if (j)
    return 1;

  unsigned class = id / 5;

  if (class == 2 || class == 4 || class == 6 || class == 8)
    return 0;

  return 1;
}

// Class 0

PAINTER(0) {
  FORYX {
    canvas[SUBSCRIPT0] = HJ_BLACK;
    canvas[SUBSCRIPT1] = color;
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
    canvas[SUBSCRIPT0] = MONO((x & y) & j);
}

PAINTER(6) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x | y) & j);
}

PAINTER(7) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x ^ y) & j);
}

PAINTER(8) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x + y) & j);
}

PAINTER(9) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * y) & j);
}

// Class 2

PAINTER(10) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x & y) % j);
}

PAINTER(11) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x | y) % j);
}

PAINTER(12) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x ^ y) % j);
}

PAINTER(13) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x + y) % j);
}

PAINTER(14) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * y) % j);
}

// Class 3

PAINTER(15) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x & y * y) & j);
}

PAINTER(16) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x | y * y) & j);
}

PAINTER(17) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x ^ y * y) & j);
}

PAINTER(18) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x + y * y) & j);
}

PAINTER(19) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x * y * y) & j);
}

// Class 4

PAINTER(20) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x & y * y) % j);
}

PAINTER(21) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x | y * y) % j);
}

PAINTER(22) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x ^ y * y) % j);
}

PAINTER(23) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x + y * y) % j);
}

PAINTER(24) {
  FORYX
    canvas[SUBSCRIPT0] = MONO((x * x * y * y) % j);
}

// Class 5

PAINTER(25) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j & x) * x & (j & y) * y) & j);
}

PAINTER(26) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j | x) * x & (j | y) * y) & j);
}

PAINTER(27) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j ^ x) * x & (j ^ y) * y) & j);
}

PAINTER(28) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j + x) * x & (j + y) * y) & j);
}

PAINTER(29) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j * x) * x & (j * y) * y) & j);
}

// Class 6

PAINTER(30) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j & x) * x & (j & y) * y) % j);
}

PAINTER(31) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j | x) * x & (j | y) * y) % j);
}

PAINTER(32) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j ^ x) * x & (j ^ y) * y) % j);
}

PAINTER(33) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j + x) * x & (j + y) * y) % j);
}

PAINTER(34) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j * x) * x & (j * y) * y) % j);
}

// Class 7

PAINTER(35) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j & x) * x + (j & y) * y) & j);
}

PAINTER(36) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j | x) * x + (j | y) * y) & j);
}

PAINTER(37) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j ^ x) * x + (j ^ y) * y) & j);
}

PAINTER(38) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j + x) * x + (j + y) * y) & j);
}

PAINTER(39) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j * x) * x + (j * y) * y) & j);
}

// Class 8

PAINTER(40) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j & x) * x + (j & y) * y) % j);
}

PAINTER(41) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j | x) * x + (j | y) * y) % j);
}

PAINTER(42) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j ^ x) * x + (j ^ y) * y) % j);
}

PAINTER(43) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j + x) * x + (j + y) * y) % j);
}

PAINTER(44) {
  FORYX
    canvas[SUBSCRIPT0] = MONO(((j * x) * x + (j * y) * y) % j);
}

// Class 9

PAINTER(45) {
  FORYX
    canvas[SUBSCRIPT0] = RAMP((j & x) * x + (j & y) * y);
}

PAINTER(46) {
  FORYX
    canvas[SUBSCRIPT0] = RAMP((j | x) * x + (j | y) * y);
}

PAINTER(47) {
  FORYX
    canvas[SUBSCRIPT0] = RAMP((j ^ x) * x + (j ^ y) * y);
}

PAINTER(48) {
  FORYX
    canvas[SUBSCRIPT0] = RAMP((j + x) * x + (j + y) * y);
}

PAINTER(49) {
  FORYX
    canvas[SUBSCRIPT0] = RAMP((j * x) * x + (j * y) * y);
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
