// amorse.c - play adapted International Morse code

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "amorse.schar"

#define FREQ 400  // Exact
#define RATE 8000 // Default aplay rate

int main(void)
{
	FILE* stream = fopen(FILENAME, "wb");

	unsigned dit = RATE / 10; // 100 ms
	unsigned dah = 3 * dit;   // 300 ms
	unsigned gap = 7 * dit;   // 700 ms

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
					return EXIT_FAILURE;
			}

			++cptr;

			if (*cptr == '.' || *cptr == '-')
				n_samples += dit;
		}

		signed char* audio = calloc(n_samples, 1);

		unsigned cycle_2 = RATE / FREQ / 2;

		unsigned i = 0;
		unsigned j = 0;

		cptr = cbuf;

		while (*cptr) {
			switch (*cptr) {
				case '.':
					for (j = 0; j < dit; ++j)
						audio[i + j] = j / cycle_2 % 2 ? SCHAR_MAX : SCHAR_MIN;

					i += dit;
					break;

				case '-':
					for (j = 0; j < dah; ++j)
						audio[i + j] = j / cycle_2 % 2 ? SCHAR_MAX : SCHAR_MIN;

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

	system("aplay -t raw -f S8 " FILENAME);

	remove(FILENAME);
}
