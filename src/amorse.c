// amorse.c - encode input into audible adapted International Morse code

// Unsigned 8 bit, Rate 8000 Hz, Mono

#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#define FILENAME "amorse.pcm"

#define RATE 8000 // Default aplay rate

int main(int argc, char* argv[argc + 1]) {
  _Bool    delet     = 0;
  _Bool    quiet     = 0;
  unsigned frequency = 400; // In Hz
  unsigned length    = 100; // In ms

  int opt;

  while ((opt = getopt(argc, argv, "f:l:dq")) != -1)
    switch (opt) {
      case 'f':
        frequency = strtoul(optarg, 0, 10);
        break;

      case 'l':
        length = strtoul(optarg, 0, 10);
        break;

      case 'd':
        delet = 1;
        break;

      case 'q':
        quiet = 1;
        break;

      default:
        return 1;
    }

  if (!frequency || !length)
    return 2;

  FILE* stream = fopen(FILENAME, "wb");

  if (!stream)
    return 3;

  unsigned dit = RATE * length / 1000;
  unsigned dah = 3 * dit;
  unsigned gap = 7 * dit;

  char cbuf[256];

  while (fgets(cbuf, sizeof cbuf, stdin)) {
    unsigned n_samples = 0;

    char* cptr = cbuf;

    while (*cptr) {
      switch (*cptr) {
        case '.':
          n_samples += dit;
          break;

        case '-':
        case ' ':
          n_samples += dah;
          break;

        case '\n':
          n_samples += gap;
          break;

        default:
          fclose(stream);
          remove(FILENAME);
          return 4;
      }

      ++cptr;

      if (*cptr == '.' || *cptr == '-')
        n_samples += dit;
    }

    unsigned char* audio = malloc(n_samples);

    if (!audio) {
      fclose(stream);
      remove(FILENAME);
      return 5;
    }

    for (unsigned i = 0; i < n_samples; ++i)
      audio[i] = 128;

    unsigned i = 0, period_2 = RATE / frequency / 2;

    cptr = cbuf;

    // Generate square waves for '.' and '-' or skip the silence for ' ' and '\n'
    while (*cptr) {
      switch (*cptr) {
        case '.':
          for (unsigned j = 0; j < dit; ++j)
            audio[i + j] = j / period_2 % 2 ? 0 : 255;

          i += dit;
          break;

        case '-':
          for (unsigned j = 0; j < dah; ++j)
            audio[i + j] = j / period_2 % 2 ? 0 : 255;

        case ' ':
          i += dah;
          break;

        case '\n':
          i += gap;
          break;
      }

      ++cptr;

      if (*cptr == '.' || *cptr == '-')
        i += dit;
    }

    fwrite(audio, 1, n_samples, stream);
    free(audio);
  }

  fclose(stream);

  puts("Wrote " FILENAME);

  if (!quiet) {
    if (system(0))
      system("aplay -t raw -f U8 -r 8000 -c 1 " FILENAME);
    else
      return 6;
  }

  if (delet) {
    remove(FILENAME);
    puts("Deleted " FILENAME);
  }
}
