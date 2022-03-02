#! /usr/bin/env python3

# hjjs.py - write some HJ J-sequences

EXTENSION = ".hjjs.txt"
MODE = "w"

J_MAX = 2 ** 32 - 1

def i22a(f, m):
  n = 0
  js = []

  while True:
    j = 2 ** (2 * n + m) - 2 ** n

    if j > J_MAX:
      break

    js.append(j)
    n += 1

  print(*js, file = f)

for m in range(10):
  with open("i22a" + str(m) + EXTENSION, MODE) as f:
    i22a(f, m)
