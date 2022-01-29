#! /usr/bin/env python3

# printable.py - print a table of printable ASCII characters in base 2, 8, 10, and 16

for i in range(32, 127):
  print(f"{i:07b} | {i:03o} | {i:03d} | {i:2x} | {chr(i):1s}")
