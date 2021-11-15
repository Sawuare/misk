#! /usr/bin/env python3

# hjjs.py - write some interesting HJ J-sequences

J_MAX = 2 ** 32 - 1

def a27(f, m):
  n = 0 if m >= 0 else -m + 1

  js = []

  while True:
    j = 2 ** (2 * n + m) - 2 ** n

    if j <= J_MAX:
      js.append(j)
    else:
      break

    n += 1

  print(*js, file = f)

# https://oeis.org/A059153
with open("a27n1.hjjs.txt", "w") as f:
  a27(f, -1)

# https://oeis.org/A020522
with open("a27p0.hjjs.txt", "w") as f:
  a27(f, 0)

# https://oeis.org/A171476
with open("a27p1.hjjs.txt", "w") as f:
  a27(f, 1)

# https://oeis.org/A171499
with open("a27p2.hjjs.txt", "w") as f:
  a27(f, 2)

# https://oeis.org/A171472
with open("a27p3.hjjs.txt", "w") as f:
  a27(f, 3)

with open("a27p4.hjjs.txt", "w") as f:
  a27(f, 4)

with open("a27p5.hjjs.txt", "w") as f:
  a27(f, 5)

with open("a27p6.hjjs.txt", "w") as f:
  a27(f, 6)

with open("a27p7.hjjs.txt", "w") as f:
  a27(f, 7)

with open("a27p8.hjjs.txt", "w") as f:
  a27(f, 8)

with open("a27p9.hjjs.txt", "w") as f:
  a27(f, 9)
