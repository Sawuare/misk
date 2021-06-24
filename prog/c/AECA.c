// AECA.c - Audible Elementary Cellular Automata

// Amplitude = 0 dBFS
// Depth     = 8 b
// Rate      = 44100 Hz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

static inline unsigned ddig(unsigned n) {
	unsigned d = 1;

	while (n /= 10)
		++d;

	return d;
}

int main(int argc, char* argv[argc + 1]) {
	unsigned n_cells = 1024;
	unsigned n_gens  = 768;
	unsigned rule    = 120;
	unsigned seed    = 1;

	int opt;

	while ((opt = getopt(argc, argv, "c:g:r:s:")) != -1)
		switch (opt) {
			case 'c':
				n_cells = strtoul(optarg, 0, 10);
				break;

			case 'g':
				n_gens = strtoul(optarg, 0, 10);
				break;

			case 'r':
				rule = strtoul(optarg, 0, 10);
				break;

			case 's':
				seed = strtoul(optarg, 0, 10);
				break;

			default:
				return EXIT_FAILURE;
		}

	unsigned n_samples = n_gens * n_cells;

	signed char* audio = malloc(n_samples);

	_Bool cells[n_cells];
	_Bool clone[n_cells];

	if (seed) {
		srand(seed);
		for (unsigned c = 0; c < n_cells; ++c)
			cells[c] = rand() & 1;
	} else {
		memset(cells, 0, sizeof cells);
		cells[n_cells / 2] = 1;
	}

	for (unsigned g = 0; g < n_gens; ++g) {
		for (unsigned c = 0; c < n_cells; ++c) {
			audio[g * n_cells + c] = cells[c] ? 127 : -127;

			_Bool p = cells[c ? c - 1 : n_cells - 1];
			_Bool q = cells[c];
			_Bool r = cells[(c + 1) % n_cells];

			clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
		}

		memcpy(cells, clone, sizeof clone);
	}

	unsigned ddig_c = ddig(n_cells);
	unsigned ddig_g = ddig(n_gens);
	unsigned ddig_s = ddig(seed);

	unsigned l_filename = ddig_c + ddig_g + ddig_s + 19;
	unsigned l_command = l_filename + 29;

	char filename[l_filename];
	char command[l_command];

	snprintf(filename, l_filename, "r%03uc%*ug%*us%*u.aeca.schar", rule, ddig_c, n_cells, ddig_g, n_gens, ddig_s, seed);
	snprintf(command, l_command, "aplay -t raw -f S8 -r 44100 %s", filename);

	FILE* stream = fopen(filename, "wb");
	fwrite(audio, 1, n_samples, stream);
	fclose(stream);

	free(audio);

	if (system(0))
		// Depend on aplay for playing raw audio
		system(command);
}
