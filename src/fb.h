// fb.h - code for fb images and macros for the framebuffer

#include <stdlib.h>

#define FB_PATH "/dev/fb0"

// UNPORTABLE
#define FB_SIZE   4227072
#define FB_WIDTH  1376
#define FB_HEIGHT 768

// UNPORTABLE
#define FB_BLACK   0x000000
#define FB_RED     0xff0000
#define FB_GREEN   0x00ff00
#define FB_BLUE    0x0000ff
#define FB_CYAN    0x00ffff
#define FB_MAGENTA 0xff00ff
#define FB_YELLOW  0xffff00
#define FB_WHITE   0xffffff

// UNPORTABLE
#define FB_PX_TO_R_BYTE(px) ((px) >> 16 & 255)
#define FB_PX_TO_G_BYTE(px) ((px) >>  8 & 255)
#define FB_PX_TO_B_BYTE(px) ((px)       & 255)

#define FB_IS_MONO_XOR_RAMP(id) ((id) < 36)

#define PAINTER(id) static inline void fb_p##id(unsigned j, unsigned color, unsigned width, unsigned height, unsigned canvas[])

#define FORYX \
  for (unsigned y = 0; y < height; ++y) \
  for (unsigned x = 0; x < width;  ++x)

#define MONO(px) (px) ? FB_BLACK : color
#define RAMP(px) (px) % 256 * color / 255 // UNPORTABLE

static inline unsigned fb_rrggbb_to_color(const char *s) {
  return strtoul(s, 0, 16); // UNPORTABLE
}

static inline unsigned fb_letter_to_color(const char *s) {
  switch (*s) {
    case 'r': return FB_RED;
    case 'g': return FB_GREEN;
    case 'b': return FB_BLUE;
    case 'c': return FB_CYAN;
    case 'm': return FB_MAGENTA;
    case 'y': return FB_YELLOW;
    default:  return FB_WHITE;
  }
}

static inline _Bool fb_is_valid(unsigned id, unsigned j) {
  if (id > 39)
    return 0;

  if (j)
    return 1;

  unsigned class = id / 4;

  if (class == 2 || class == 4 || class == 6 || class == 8)
    return 0;

  return 1;
}

// Class 0

PAINTER(0) {
  FORYX {
    canvas[y * width + x] = FB_BLACK;
    canvas[y * x] = color;
  }
}

PAINTER(1) {
}

PAINTER(2) {
}

PAINTER(3) {
}

// Class 1

PAINTER(4) {
  FORYX
    canvas[y * width + x] = MONO((x & y) & j);
}

PAINTER(5) {
  FORYX
    canvas[y * width + x] = MONO((x | y) & j);
}

PAINTER(6) {
  FORYX
    canvas[y * width + x] = MONO((x ^ y) & j);
}

PAINTER(7) {
  FORYX
    canvas[y * width + x] = MONO((x * y) & j);
}

// Class 2

PAINTER(8) {
  FORYX
    canvas[y * width + x] = MONO((x & y) % j);
}

PAINTER(9) {
  FORYX
    canvas[y * width + x] = MONO((x | y) % j);
}

PAINTER(10) {
  FORYX
    canvas[y * width + x] = MONO((x ^ y) % j);
}

PAINTER(11) {
  FORYX
    canvas[y * width + x] = MONO((x * y) % j);
}

// Class 3

PAINTER(12) {
  FORYX
    canvas[y * width + x] = MONO((x * x & y * y) & j);
}

PAINTER(13) {
  FORYX
    canvas[y * width + x] = MONO((x * x | y * y) & j);
}

PAINTER(14) {
  FORYX
    canvas[y * width + x] = MONO((x * x ^ y * y) & j);
}

PAINTER(15) {
  FORYX
    canvas[y * width + x] = MONO((x * x * y * y) & j);
}

// Class 4

PAINTER(16) {
  FORYX
    canvas[y * width + x] = MONO((x * x & y * y) % j);
}

PAINTER(17) {
  FORYX
    canvas[y * width + x] = MONO((x * x | y * y) % j);
}

PAINTER(18) {
  FORYX
    canvas[y * width + x] = MONO((x * x ^ y * y) % j);
}

PAINTER(19) {
  FORYX
    canvas[y * width + x] = MONO((x * x * y * y) % j);
}

// Class 5

PAINTER(20) {
  FORYX
    canvas[y * width + x] = MONO(((j & x) * x & (j & y) * y) & j);
}

PAINTER(21) {
  FORYX
    canvas[y * width + x] = MONO(((j | x) * x & (j | y) * y) & j);
}

PAINTER(22) {
  FORYX
    canvas[y * width + x] = MONO(((j ^ x) * x & (j ^ y) * y) & j);
}

PAINTER(23) {
  FORYX
    canvas[y * width + x] = MONO(((j * x) * x & (j * y) * y) & j);
}

// Class 6

PAINTER(24) {
  FORYX
    canvas[y * width + x] = MONO(((j & x) * x & (j & y) * y) % j);
}

PAINTER(25) {
  FORYX
    canvas[y * width + x] = MONO(((j | x) * x & (j | y) * y) % j);
}

PAINTER(26) {
  FORYX
    canvas[y * width + x] = MONO(((j ^ x) * x & (j ^ y) * y) % j);
}

PAINTER(27) {
  FORYX
    canvas[y * width + x] = MONO(((j * x) * x & (j * y) * y) % j);
}

// Class 7

PAINTER(28) {
  FORYX
    canvas[y * width + x] = MONO(((j & x) * x + (j & y) * y) & j);
}

PAINTER(29) {
  FORYX
    canvas[y * width + x] = MONO(((j | x) * x + (j | y) * y) & j);
}

PAINTER(30) {
  FORYX
    canvas[y * width + x] = MONO(((j ^ x) * x + (j ^ y) * y) & j);
}

PAINTER(31) {
  FORYX
    canvas[y * width + x] = MONO(((j * x) * x + (j * y) * y) & j);
}

// Class 8

PAINTER(32) {
  FORYX
    canvas[y * width + x] = MONO(((j & x) * x + (j & y) * y) % j);
}

PAINTER(33) {
  FORYX
    canvas[y * width + x] = MONO(((j | x) * x + (j | y) * y) % j);
}

PAINTER(34) {
  FORYX
    canvas[y * width + x] = MONO(((j ^ x) * x + (j ^ y) * y) % j);
}

PAINTER(35) {
  FORYX
    canvas[y * width + x] = MONO(((j * x) * x + (j * y) * y) % j);
}

// Class 9

PAINTER(36) {
  FORYX
    canvas[y * width + x] = RAMP((j & x) * x + (j & y) * y);
}

PAINTER(37) {
  FORYX
    canvas[y * width + x] = RAMP((j | x) * x + (j | y) * y);
}

PAINTER(38) {
  FORYX
    canvas[y * width + x] = RAMP((j ^ x) * x + (j ^ y) * y);
}

PAINTER(39) {
  FORYX
    canvas[y * width + x] = RAMP((j * x) * x + (j * y) * y);
}

static void (*fb_painters[])(unsigned, unsigned, unsigned, unsigned, unsigned[]) = {
  fb_p0,  fb_p1,  fb_p2,  fb_p3,  fb_p4,  fb_p5,  fb_p6,  fb_p7,  fb_p8,  fb_p9,
  fb_p10, fb_p11, fb_p12, fb_p13, fb_p14, fb_p15, fb_p16, fb_p17, fb_p18, fb_p19,
  fb_p20, fb_p21, fb_p22, fb_p23, fb_p24, fb_p25, fb_p26, fb_p27, fb_p28, fb_p29,
  fb_p30, fb_p31, fb_p32, fb_p33, fb_p34, fb_p35, fb_p36, fb_p37, fb_p38, fb_p39
};

#undef PAINTER
#undef FORYX
#undef MONO
#undef RAMP
