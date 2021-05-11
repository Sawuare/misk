// fb.h - constants and painters for a 1024x768x32 BGRA framebuffer

#define FB_PATH "/dev/fb0"

#define FB_SIZE 3145728
#define FB_XRES 1024
#define FB_YRES 768

#define FB_RED     0xff0000
#define FB_GREEN   0x00ff00
#define FB_BLUE    0x0000ff
#define FB_CYAN    0x00ffff
#define FB_MAGENTA 0xff00ff
#define FB_YELLOW  0xffff00
#define FB_WHITE   0xffffff

#define HUE(px) (px) * h
#define SHADE(px) (px) % 0x100 * h / 0xff

#define FORYX for (unsigned y = 0; y < yres; ++y) \
              for (unsigned x = 0; x < xres; ++x)

#define PAINTER(id) static inline void p##id(unsigned xres, unsigned yres, unsigned z, unsigned h, unsigned a[])

typedef void painter(unsigned, unsigned, unsigned, unsigned, unsigned[]);

static painter
	p00, p01, p02, p03, p04, p05, p06, p07, p08, p09,
	p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
	p20, p21, p22, p23, p24, p25, p26, p27, p28, p29,
	p30, p31, p32;

static painter* painters[] = {
	p00, p01, p02, p03, p04, p05, p06, p07, p08, p09,
	p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
	p20, p21, p22, p23, p24, p25, p26, p27, p28, p29,
	p30, p31, p32,
};

// Class 0

PAINTER(00) {
	FORYX
		a[y * x] = HUE(1);
}

// Class 1

PAINTER(01) {
	FORYX
		a[y * xres + x] = HUE(!((x & y) & z));
}

PAINTER(02) {
	FORYX
		a[y * xres + x] = HUE(!((x | y) & z));
}

PAINTER(03) {
	FORYX
		a[y * xres + x] = HUE(!((x ^ y) & z));
}

PAINTER(04) {
	FORYX
		a[y * xres + x] = HUE(!((x * y) & z));
}

// Class 2

PAINTER(05) {
	FORYX
		a[y * xres + x] = HUE(!((x & y) % z));
}

PAINTER(06) {
	FORYX
		a[y * xres + x] = HUE(!((x | y) % z));
}

PAINTER(07) {
	FORYX
		a[y * xres + x] = HUE(!((x ^ y) % z));
}

PAINTER(08) {
	FORYX
		a[y * xres + x] = HUE(!((x * y) % z));
}

// Class 3

PAINTER(09) {
	FORYX
		a[y * xres + x] = HUE(!((x * x & y * y) & z));
}

PAINTER(10) {
	FORYX
		a[y * xres + x] = HUE(!((x * x | y * y) & z));
}

PAINTER(11) {
	FORYX
		a[y * xres + x] = HUE(!((x * x ^ y * y) & z));
}

PAINTER(12) {
	FORYX
		a[y * xres + x] = HUE(!((x * x * y * y) & z));
}

// Class 4

PAINTER(13) {
	FORYX
		a[y * xres + x] = HUE(!((x * x & y * y) % z));
}

PAINTER(14) {
	FORYX
		a[y * xres + x] = HUE(!((x * x | y * y) % z));
}

PAINTER(15) {
	FORYX
		a[y * xres + x] = HUE(!((x * x ^ y * y) % z));
}

PAINTER(16) {
	FORYX
		a[y * xres + x] = HUE(!((x * x * y * y) % z));
}

// Class 5

PAINTER(17) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x & z) & y * (y & z)) & z));
}

PAINTER(18) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x | z) & y * (y | z)) & z));
}

// z == (1 << 2 * n + m) - (1 << n + 2)
PAINTER(19) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) & y * (y ^ z)) & z));
}

PAINTER(20) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x * z) & y * (y * z)) & z));
}

// Class 6

PAINTER(21) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x & z) & y * (y & z)) % z));
}

PAINTER(22) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x | z) & y * (y | z)) % z));
}

PAINTER(23) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) & y * (y ^ z)) % z));
}

PAINTER(24) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x * z) & y * (y * z)) % z));
}

// Class 7

PAINTER(25) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x & z) + y * (y & z)) % z));
}

PAINTER(26) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x | z) + y * (y | z)) % z));
}

PAINTER(27) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) + y * (y ^ z)) % z));
}

PAINTER(28) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x * z) + y * (y * z)) % z));
}

// Class 8

PAINTER(29) {
	FORYX
		a[y * xres + x] = SHADE(x * (x & z) + y * (y & z));
}

PAINTER(30) {
	FORYX
		a[y * xres + x] = SHADE(x * (x | z) + y * (y | z));
}

PAINTER(31) {
	FORYX
		a[y * xres + x] = SHADE(x * (x ^ z) + y * (y ^ z));
}

PAINTER(32) {
	FORYX
		a[y * xres + x] = SHADE(x * (x * z) + y * (y * z));
}

#undef HUE
#undef SHADE
#undef FORYX
#undef PAINTER
