// limits.c - print every limit in <limits.h>

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
  printf("MB_LEN_MAX = %ju\n", (uintmax_t) MB_LEN_MAX);
  printf("CHAR_BIT   = %ju\n", (uintmax_t) CHAR_BIT);
  printf("CHAR_MIN   = %+jd\n", (intmax_t) CHAR_MIN);
  printf("CHAR_MAX   = %+jd\n", (intmax_t) CHAR_MAX);
  printf("SCHAR_MIN  = %+jd\n", (intmax_t) SCHAR_MIN);
  printf("SCHAR_MAX  = %+jd\n", (intmax_t) SCHAR_MAX);
  printf("UCHAR_MAX  = %ju\n", (uintmax_t) UCHAR_MAX);
  printf("SHRT_MIN   = %+jd\n", (intmax_t) SHRT_MIN);
  printf("SHRT_MAX   = %+jd\n", (intmax_t) SHRT_MAX);
  printf("USHRT_MAX  = %ju\n", (uintmax_t) USHRT_MAX);
  printf("INT_MIN    = %+jd\n", (intmax_t) INT_MIN);
  printf("INT_MAX    = %+jd\n", (intmax_t) INT_MAX);
  printf("UINT_MAX   = %ju\n", (uintmax_t) UINT_MAX);
  printf("LONG_MIN   = %+jd\n", (intmax_t) LONG_MIN);
  printf("LONG_MAX   = %+jd\n", (intmax_t) LONG_MAX);
  printf("ULONG_MAX  = %ju\n", (uintmax_t) ULONG_MAX);
  printf("LLONG_MIN  = %+jd\n", (intmax_t) LLONG_MIN);
  printf("LLONG_MAX  = %+jd\n", (intmax_t) LLONG_MAX);
  printf("ULLONG_MAX = %ju\n", (uintmax_t) ULLONG_MAX);
}
