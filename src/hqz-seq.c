// hqz-seq.c - write some HQZ Q-sequences

#include <stdio.h>

#define Q_MAX 0xffffffff

void i22a(FILE *f, int m) {
  int n = 0;
  _Bool first = 1;

  while (1) {
    long long q = (1ll << (2 * n + m)) - (1ll << n);

    if (q > Q_MAX)
      break;

    if (!first)
      fputc(' ', f);

    fprintf(f, "%lld", q);
    ++n;
    first = 0;
  }

  fputc('\n', f);
}

int main(void) {
  char filename[] = "p22a0.hqz-seq.txt";

  for (int m = 0; m <= 9; ++m) {
    filename[4] = '0' + m;
    FILE *f = fopen(filename, "w");

    if (!f)
      return 1;

    i22a(f, m);
    fclose(f);
  }
}
