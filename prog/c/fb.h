// fb.h - constants and painters for fb.c and fb2png.c

#define FB_PATH "/dev/fb0"

#define FB_SIZE 3145728
#define FB_XRES 1024
#define FB_YRES 768

#define FB_BLACK   0xff000000u
#define FB_RED     0xffff0000u
#define FB_GREEN   0xff00ff00u
#define FB_BLUE    0xff0000ffu
#define FB_CYAN    0xff00ffffu
#define FB_MAGENTA 0xffff00ffu
#define FB_YELLOW  0xffffff00u
#define FB_WHITE   0xffffffffu

#define HUE(px) (px) * h
#define GRAY(px) (px) % 0x100u * 0x010101u

#define FORYX for (unsigned y = 0; y < yres; ++y) \
              for (unsigned x = 0; x < xres; ++x)

#define PAINTER(id) static inline void p##id(unsigned xres, unsigned yres, unsigned z, unsigned h, unsigned* a)

typedef void painter(unsigned, unsigned, unsigned, unsigned, unsigned*);

static painter
	p00, p01, p02, p03, p04, p05, p06, p07, p08, p09,
	p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
	p20, p21, p22, p23;

static painter* painters[] = {
	p00, p01, p02, p03, p04, p05, p06, p07, p08, p09,
	p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
	p20, p21, p22, p23,
};

PAINTER(00) {
	FORYX
		a[y * x] = HUE(1);
}

PAINTER(01) {
	FORYX
		a[y * xres + x] = HUE(1);
}

PAINTER(02) {
	FORYX
		a[y * xres + x] = HUE(!((x * y) & z));
}

PAINTER(03) {
	FORYX
		a[y * xres + x] = HUE(!((x & y) & z));
}

PAINTER(04) {
	FORYX
		a[y * xres + x] = HUE(!((x | y) & z));
}

PAINTER(05) {
	FORYX
		a[y * xres + x] = HUE(!((x ^ y) & z));
}

PAINTER(06) {
	FORYX
		a[y * xres + x] = HUE(!((x * y) % z));
}

PAINTER(07) {
	FORYX
		a[y * xres + x] = HUE(!((x & y) % z));
}

PAINTER(08) {
	FORYX
		a[y * xres + x] = HUE(!((x | y) % z));
}

PAINTER(09) {
	FORYX
		a[y * xres + x] = HUE(!((x ^ y) % z));
}

PAINTER(10) {
	FORYX
		a[y * xres + x] = HUE(!((x * x * y * y) % z));
}

PAINTER(11) {
	FORYX
		a[y * xres + x] = HUE(!((x * x & y * y) % z));
}

PAINTER(12) {
	FORYX
		a[y * xres + x] = HUE(!((x * x | y * y) % z));
}

PAINTER(13) {
	FORYX
		a[y * xres + x] = HUE(!((x * x ^ y * y) % z));
}

PAINTER(14) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) & y * (y ^ z)) & z));
}

PAINTER(15) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) & y * (y ^ z)) % z));
}

PAINTER(16) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x & z) + y * (y & z)) % z));
}

PAINTER(17) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x | z) + y * (y | z)) % z));
}

PAINTER(18) {
	FORYX
		a[y * xres + x] = HUE(!((x * (x ^ z) + y * (y ^ z)) % z));
}

PAINTER(19) {
	FORYX
		a[y * xres + x] = GRAY(x * (x & z) + y * (y & z));
}

PAINTER(20) {
	FORYX
		a[y * xres + x] = GRAY(x * (x | z) + y * (y | z));
}

PAINTER(21) {
	FORYX
		a[y * xres + x] = GRAY(x * (x ^ z) + y * (y ^ z));
}

PAINTER(22) {
	FORYX
		a[y * xres + x] = GRAY(((x ^ y) - (x + y)) * z);
}

PAINTER(23) {
	FORYX
		a[y * xres + x] = (x * x + y * y) * z;
}

#undef HUE
#undef GRAY
#undef FORYX
#undef PAINTER
