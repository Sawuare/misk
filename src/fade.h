// fade.h - linear or power fade in or out of floats

#include <math.h>
#include <stddef.h>

static inline void lin_fade_in(size_t n, float a[]) {
  size_t m = n - 1;

  for (size_t i = 0; i < n; ++i)
    a[i] *= (float) i / m;
}

static inline void lin_fade_out(size_t n, float a[]) {
  size_t m = n - 1;

  for (size_t i = 0; i < n; ++i)
    a[i] *= (float) (m - i) / m;
}

static inline void pow_fade_in(size_t n, float a[], float p) {
  size_t m = n - 1;

  for (size_t i = 0; i < n; ++i)
    a[i] *= powf((float) i / m, p);
}

static inline void pow_fade_out(size_t n, float a[], float p) {
  size_t m = n - 1;

  for (size_t i = 0; i < n; ++i)
    a[i] *= powf((float) (m - i) / m, p);
}
