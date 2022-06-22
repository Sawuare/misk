// printable.c - print a table of printable ASCII characters in bases 16 and 10

#include <locale.h>
#include <stdio.h>
#include <wchar.h>

// Todo: Move this up when Clang defines the macro in the environment
#ifndef __STDC_ISO_10646__
#error
#endif

int main(void) {
  if (!setlocale(LC_ALL, ""))
    return 1;

  for (wint_t code = 32; code <= 126; ++code)
    printf("%lc | %x | %.3d\n", code, code, code);
}
