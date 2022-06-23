// hjjs.c - write some HJ J-sequences

#include <stdio.h>

#define J_MAX 0xffffffff

void i22a(FILE *f, int m) {
  int n = 0;
  _Bool first = 1;

  while (1) {
    long long j = (1ll << (2 * n + m)) - (1ll << n);

    if (j > J_MAX)
      break;

    if (!first)
      fputc(' ', f);

    fprintf(f, "%lld", j);
    ++n;
    first = 0;
  }

  fputc('\n', f);
}

int main(void) {
  char filename[] = "i22a0.hjjs.txt";

  for (int m = 0; m <= 9; ++m) {
    filename[4] = '0' + m;
    FILE *f = fopen(filename, "w");

    if (!f)
      return 1;

    i22a(f, m);
    fclose(f);
  }
}
