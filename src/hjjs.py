#! /usr/bin/env python3

# hjjs.py - write some interesting HJ J-sequences

J_MAX = 2 ** 32 - 1

def i22(f, m):
  n = 0

  js = []

  while True:
    j = 2 ** (2 * n + m) - 2 ** n

    if j > J_MAX:
      break

    js.append(j)

    n += 1

  print(*js, file = f)

# https://oeis.org/A020522
with open("i22m0.hjjs.txt", "w") as f:
  i22(f, 0)

# https://oeis.org/A171476
with open("i22m1.hjjs.txt", "w") as f:
  i22(f, 1)

# https://oeis.org/A171499
with open("i22m2.hjjs.txt", "w") as f:
  i22(f, 2)

# https://oeis.org/A171472
with open("i22m3.hjjs.txt", "w") as f:
  i22(f, 3)

with open("i22m4.hjjs.txt", "w") as f:
  i22(f, 4)

with open("i22m5.hjjs.txt", "w") as f:
  i22(f, 5)

with open("i22m6.hjjs.txt", "w") as f:
  i22(f, 6)

with open("i22m7.hjjs.txt", "w") as f:
  i22(f, 7)

with open("i22m8.hjjs.txt", "w") as f:
  i22(f, 8)

with open("i22m9.hjjs.txt", "w") as f:
  i22(f, 9)
