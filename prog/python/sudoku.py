#! /usr/bin/env python3

# sudoku.py - print "sudoku" grid of subgrids filled sequentially with 1s to 9s

from sys import stdout

for row in range(9):
	for col in range(9):
		# Thanks to kanafutile
		stdout.write(chr(ord('1') + col // 3 + row // 3 * 3))

		stdout.write(' ')

		if col == 2 or col == 5:
			stdout.write(' ')

	stdout.write('\n')

	if row == 2 or row == 5:
		stdout.write('\n')
