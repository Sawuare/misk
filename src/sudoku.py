#! /usr/bin/env python3

# sudoku.py - print "sudoku" grid of subgrids filled sequentially with 1s to 9s

for row in range(9):
  for col in range(9):
    # Thanks to kanafutile
    print(chr(ord("1") + col // 3 + row // 3 * 3), end = " ")

    if col == 2 or col == 5:
      print(" ", end = "")

  print()

  if row == 2 or row == 5:
    print()
