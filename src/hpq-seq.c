// hpq-seq.c - write some HPQ q-sequences

#include <stdio.h>
#include <stdlib.h>

#define MAX_M 7
#define MAX_Q 0xffffffff

void write_sequence(long long sequence[], int length, int painter) {
  // The longest filename is
  // p10q1000000000.hpq-seq.txt
  char filename[27];
  sprintf(filename, "p%dq%lld.hpq-seq.txt", painter, sequence[0]);

  FILE *file = fopen(filename, "w");

  if (!file)
    exit(1);

  --length;

  for (int i = 0; i < length; ++i)
    fprintf(file, "%lld ", sequence[i]);

  fprintf(file, "%lld\n", sequence[length]);
  fclose(file);
}

int main(void) {
  long long sequence[32];

  // Sequences for painter 22

  for (int m = 0; m <= MAX_M; ++m) {
    int n = 0;

    while (1) {
      sequence[n] = (1ll << (2 * n + m)) - (1ll << n);

      if (sequence[n] > MAX_Q)
        break;

      ++n;
    }

    write_sequence(sequence, n, 22);
  }

  // Sequences for painter 30

  for (int m = 0; m <= MAX_M; ++m) {
    int n = 0;

    while (1) {
      sequence[n] = (1ll << (2 * n + m)) + (1ll << n);

      if (sequence[n] > MAX_Q)
        break;

      ++n;
    }

    write_sequence(sequence, n, 30);
  }
}
