// AECA.c - Audible Elementary Cellular Automata

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "AECA.schar"

int main(void) {
	int seed, rule, gen_len, gen_cnt;

	printf("Seed: ");
	scanf("%d", &seed);

	printf("Rule: ");
	scanf("%d", &rule);

	printf("Generation length: ");
	scanf("%d", &gen_len);

	printf("Generation count: ");
	scanf("%d", &gen_cnt);

	int samples = gen_cnt * gen_len;

	_Bool cells[gen_len];
	_Bool clone[gen_len];

	if (seed) {
		srand(seed);

		for (int c = 0; c < gen_len; ++c)
			cells[c] = rand() & 1;
	} else {
		memset(cells, 0, sizeof cells);
		cells[gen_len / 2] = 1;
	}

	signed char* audio = malloc(samples);

	for (int g = 0; g < gen_cnt; ++g) {
		for (int c = 0; c < gen_len; ++c) {
			audio[g * gen_len + c] = cells[c] ? SCHAR_MAX : SCHAR_MIN;

			_Bool p = cells[c ? c - 1 : gen_len - 1];
			_Bool q = cells[c];
			_Bool r = cells[(c + 1) % gen_len];

			clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
		}

		memcpy(cells, clone, sizeof clone);
	}

	FILE* stream = fopen(FILENAME, "wb");

	fwrite(audio, 1, samples, stream);

	fclose(stream);

	free(audio);

	system("aplay -q -t raw -f S8 -r 44100 " FILENAME);
}
