// fb.h - fb painters and macros for the framebuffer

#include <stdlib.h>

#define FB_PATH "/dev/fb0"

// UNPORTABLE
#define FB_SIZE 4227072
#define FB_XRES 1376
#define FB_YRES 768

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

#define FB_IS_VALID(id, j) ((id) < 33 && (j))

#define FB_IS_MONO_XOR_RAMP(id) ((id) < 29)

#define PAINTER(id) static inline void fb_p##id(unsigned j, unsigned c, unsigned xres, unsigned yres, unsigned a[])

#define FORYX \
  for (unsigned y = 0; y < yres; ++y) \
  for (unsigned x = 0; x < xres; ++x)

// UNPORTABLE
#define MONO(px) (px) * c
#define RAMP(px) (px) % 256 * c / 255

// UNPORTABLE
static inline unsigned fb_rrggbb_to_color(const char *s) {
  return strtoul(s, 0, 16);
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

// Class 0

PAINTER(0) {
  FORYX {
    a[y * xres + x] = FB_BLACK;
    a[y * x] = c;
  }
}

// Class 1

PAINTER(1) {
  FORYX
    a[y * xres + x] = MONO(!((x & y) & j));
}

PAINTER(2) {
  FORYX
    a[y * xres + x] = MONO(!((x | y) & j));
}

PAINTER(3) {
  FORYX
    a[y * xres + x] = MONO(!((x ^ y) & j));
}

PAINTER(4) {
  FORYX
    a[y * xres + x] = MONO(!((x * y) & j));
}

// Class 2

PAINTER(5) {
  FORYX
    a[y * xres + x] = MONO(!((x & y) % j));
}

PAINTER(6) {
  FORYX
    a[y * xres + x] = MONO(!((x | y) % j));
}

PAINTER(7) {
  FORYX
    a[y * xres + x] = MONO(!((x ^ y) % j));
}

PAINTER(8) {
  FORYX
    a[y * xres + x] = MONO(!((x * y) % j));
}

// Class 3

PAINTER(9) {
  FORYX
    a[y * xres + x] = MONO(!((x * x & y * y) & j));
}

PAINTER(10) {
  FORYX
    a[y * xres + x] = MONO(!((x * x | y * y) & j));
}

PAINTER(11) {
  FORYX
    a[y * xres + x] = MONO(!((x * x ^ y * y) & j));
}

PAINTER(12) {
  FORYX
    a[y * xres + x] = MONO(!((x * x * y * y) & j));
}

// Class 4

PAINTER(13) {
  FORYX
    a[y * xres + x] = MONO(!((x * x & y * y) % j));
}

PAINTER(14) {
  FORYX
    a[y * xres + x] = MONO(!((x * x | y * y) % j));
}

PAINTER(15) {
  FORYX
    a[y * xres + x] = MONO(!((x * x ^ y * y) % j));
}

PAINTER(16) {
  FORYX
    a[y * xres + x] = MONO(!((x * x * y * y) % j));
}

// Class 5

PAINTER(17) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x & j) & y * (y & j)) & j));
}

PAINTER(18) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x | j) & y * (y | j)) & j));
}

PAINTER(19) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x ^ j) & y * (y ^ j)) & j));
}

PAINTER(20) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x * j) & y * (y * j)) & j));
}

// Class 6

PAINTER(21) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x & j) & y * (y & j)) % j));
}

PAINTER(22) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x | j) & y * (y | j)) % j));
}

PAINTER(23) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x ^ j) & y * (y ^ j)) % j));
}

PAINTER(24) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x * j) & y * (y * j)) % j));
}

// Class 7

PAINTER(25) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x & j) + y * (y & j)) % j));
}

PAINTER(26) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x | j) + y * (y | j)) % j));
}

PAINTER(27) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x ^ j) + y * (y ^ j)) % j));
}

PAINTER(28) {
  FORYX
    a[y * xres + x] = MONO(!((x * (x * j) + y * (y * j)) % j));
}

// Class 8

PAINTER(29) {
  FORYX
    a[y * xres + x] = RAMP(x * (x & j) + y * (y & j));
}

PAINTER(30) {
  FORYX
    a[y * xres + x] = RAMP(x * (x | j) + y * (y | j));
}

PAINTER(31) {
  FORYX
    a[y * xres + x] = RAMP(x * (x ^ j) + y * (y ^ j));
}

PAINTER(32) {
  FORYX
    a[y * xres + x] = RAMP(x * (x * j) + y * (y * j));
}

static void (*fb_painters[])(unsigned, unsigned, unsigned, unsigned, unsigned[]) = {
  fb_p0,  fb_p1,  fb_p2,  fb_p3,  fb_p4,  fb_p5,  fb_p6,  fb_p7,  fb_p8,  fb_p9,
  fb_p10, fb_p11, fb_p12, fb_p13, fb_p14, fb_p15, fb_p16, fb_p17, fb_p18, fb_p19,
  fb_p20, fb_p21, fb_p22, fb_p23, fb_p24, fb_p25, fb_p26, fb_p27, fb_p28, fb_p29,
  fb_p30, fb_p31, fb_p32
};

#undef PAINTER
#undef FORYX
#undef MONO
#undef RAMP
