// midi.c - print a table of MIDI note number, notation, and frequency

#include <math.h>
#include <stdio.h>

#define PCN 12  // Number of pitch classes
#define N   128 // Number of MIDI notes
#define A4N 69  // Number of note A4
#define A4F 440 // Frequency of note A4

int main(void) {
  // Sequence of pitch classes
  char pcs[PCN][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

  // 15 is the empirical maximum precision of frequency
  for (int n = 0; n < N; ++n)
    printf("%.3d | %-2s% d | %#.15g\n",
      n, pcs[n % PCN], n / PCN - 1, pow(2, (double) (n - A4N) / PCN) * A4F);
}
