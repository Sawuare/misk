// AECA.c - Audible Elementary Cellular Automata

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "AECA.schar"

int main(void) {
	unsigned seed, rule, n_cells, n_generations;

	printf("Seed: ");
	scanf("%u", &seed);

	printf("Rule: ");
	scanf("%u", &rule);

	printf("Number of cells: ");
	scanf("%u", &n_cells);

	printf("Number of generations: ");
	scanf("%u", &n_generations);

	unsigned n_samples = n_generations * n_cells;

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

	signed char* audio = malloc(n_samples);

	for (unsigned g = 0; g < n_generations; ++g) {
		for (unsigned c = 0; c < n_cells; ++c) {
			audio[g * n_cells + c] = cells[c] ? SCHAR_MAX : SCHAR_MIN;

			_Bool p = cells[c ? c - 1 : n_cells - 1];
			_Bool q = cells[c];
			_Bool r = cells[(c + 1) % n_cells];

			clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
		}

		memcpy(cells, clone, sizeof clone);
	}

	FILE* stream = fopen(FILENAME, "wb");
	fwrite(audio, 1, n_samples, stream);
	fclose(stream);

	free(audio);

	system("aplay -q -t raw -f S8 -r 44100 " FILENAME);
}
