// amorse.c - encode input into audible International Morse code

// Unsigned 8 bit, Rate 8000 Hz, Mono

#include <stdio.h>
#include <stdlib.h>

#define FILENAME "amorse.pcm"

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

		unsigned char* audio = malloc(n_samples);

		for (unsigned i = 0; i < n_samples; ++i)
			audio[i] = 128;

		unsigned i = 0, period_2 = RATE / FREQ / 2;

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

	if (system(0))
		// Depend on aplay for playing raw audio
		system("aplay -t raw -f U8 -r 8000 " FILENAME);

	remove(FILENAME);
}
