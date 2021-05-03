// sudoku.c - print "sudoku" grid of subgrids filled sequentially with [1, 9]

#include <stdio.h>

#include "macros.h"

int main(void) {
	char grid[9][9];

	// Formula by kanafutile
	for (unsigned i = 0; i < 9; ++i)
		for (unsigned j = 0; j < 9; ++j)
			grid[i][j] = DDTOC(j / 3 + i / 3 * 3 + 1);

	for (unsigned i = 0; i < 9; ++i) {
		for (unsigned j = 0; j < 9; ++j) {
			putchar(grid[i][j]);
			putchar(' ');

			if (j == 2 || j == 5)
				putchar(' ');
		}

		putchar('\n');

		if (i == 2 || i == 5)
			putchar('\n');
	}
}
