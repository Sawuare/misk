#! /usr/bin/env python3

# print.py - print a table of printable ASCII characters in bin, oct, dec, and hex

for i in range(32, 127):
  print(f"{i:07b} | {i:03o} | {i:03d} | {i:2x} | {chr(i):1s}")
