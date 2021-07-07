// fb.h - constants and painters for a 1376x768x32 BGRA framebuffer

#include <stdlib.h>

#include "macros.h"

#define FB_PATH "/dev/fb0"

#define FB_SIZE 4227072
#define FB_XRES 1376
#define FB_YRES 768
#define FB_BPS  8

#define FB_RED     0xff0000
#define FB_GREEN   0x00ff00
#define FB_BLUE    0x0000ff
#define FB_CYAN    0x00ffff
#define FB_MAGENTA 0xff00ff
#define FB_YELLOW  0xffff00
#define FB_WHITE   0xffffff

#define FB_IS_VALID(id, z) ((id) < 33 && (z))

#define FB_IS_MONO_XOR_RAMP(id) ((id) < 29)

#define PAINTER(id) static inline void fb_p##id(unsigned xres, unsigned yres, unsigned z, unsigned c, unsigned a[])

#define FORYX \
	for (unsigned y = 0; y < yres; ++y) \
	for (unsigned x = 0; x < xres; ++x)

#define MONO(px) ((px) * c)
#define RAMP(px) ((px) % 0x100 * c / 0xff)

static inline unsigned fb_get_base16_color(char const* s) {
	return strtoul(s, 0, 16) % 0x1000000;
}

static inline unsigned fb_get_letter_color(char const* s) {
	switch (TOUPPER(*s)) {
		default:
		case 'W': return FB_WHITE;
		case 'R': return FB_RED;
		case 'G': return FB_GREEN;
		case 'B': return FB_BLUE;
		case 'C': return FB_CYAN;
		case 'M': return FB_MAGENTA;
		case 'Y': return FB_YELLOW;
	}
}

// Class 0

PAINTER(0) {
	FORYX
		a[y * x] = MONO(1);
}

// Class 1

PAINTER(1) {
	FORYX
		a[y * xres + x] = MONO(!((x & y) & z));
}

PAINTER(2) {
	FORYX
		a[y * xres + x] = MONO(!((x | y) & z));
}

PAINTER(3) {
	FORYX
		a[y * xres + x] = MONO(!((x ^ y) & z));
}

PAINTER(4) {
	FORYX
		a[y * xres + x] = MONO(!((x * y) & z));
}

// Class 2

PAINTER(5) {
	FORYX
		a[y * xres + x] = MONO(!((x & y) % z));
}

PAINTER(6) {
	FORYX
		a[y * xres + x] = MONO(!((x | y) % z));
}

PAINTER(7) {
	FORYX
		a[y * xres + x] = MONO(!((x ^ y) % z));
}

PAINTER(8) {
	FORYX
		a[y * xres + x] = MONO(!((x * y) % z));
}

// Class 3

PAINTER(9) {
	FORYX
		a[y * xres + x] = MONO(!((x * x & y * y) & z));
}

PAINTER(10) {
	FORYX
		a[y * xres + x] = MONO(!((x * x | y * y) & z));
}

PAINTER(11) {
	FORYX
		a[y * xres + x] = MONO(!((x * x ^ y * y) & z));
}

PAINTER(12) {
	FORYX
		a[y * xres + x] = MONO(!((x * x * y * y) & z));
}

// Class 4

PAINTER(13) {
	FORYX
		a[y * xres + x] = MONO(!((x * x & y * y) % z));
}

PAINTER(14) {
	FORYX
		a[y * xres + x] = MONO(!((x * x | y * y) % z));
}

PAINTER(15) {
	FORYX
		a[y * xres + x] = MONO(!((x * x ^ y * y) % z));
}

PAINTER(16) {
	FORYX
		a[y * xres + x] = MONO(!((x * x * y * y) % z));
}

// Class 5

PAINTER(17) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x & z) & y * (y & z)) & z));
}

PAINTER(18) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x | z) & y * (y | z)) & z));
}

PAINTER(19) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x ^ z) & y * (y ^ z)) & z));
}

PAINTER(20) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x * z) & y * (y * z)) & z));
}

// Class 6

PAINTER(21) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x & z) & y * (y & z)) % z));
}

PAINTER(22) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x | z) & y * (y | z)) % z));
}

PAINTER(23) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x ^ z) & y * (y ^ z)) % z));
}

PAINTER(24) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x * z) & y * (y * z)) % z));
}

// Class 7

PAINTER(25) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x & z) + y * (y & z)) % z));
}

PAINTER(26) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x | z) + y * (y | z)) % z));
}

PAINTER(27) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x ^ z) + y * (y ^ z)) % z));
}

PAINTER(28) {
	FORYX
		a[y * xres + x] = MONO(!((x * (x * z) + y * (y * z)) % z));
}

// Class 8

PAINTER(29) {
	FORYX
		a[y * xres + x] = RAMP(x * (x & z) + y * (y & z));
}

PAINTER(30) {
	FORYX
		a[y * xres + x] = RAMP(x * (x | z) + y * (y | z));
}

PAINTER(31) {
	FORYX
		a[y * xres + x] = RAMP(x * (x ^ z) + y * (y ^ z));
}

PAINTER(32) {
	FORYX
		a[y * xres + x] = RAMP(x * (x * z) + y * (y * z));
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
