#! /usr/bin/env python3

# fbjs.py - write some interesting fb j-sequences

J_MAX = 2 ** 32 - 1

def a22(f, m):
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
with open("a22n1.fbjs.txt", "w") as f:
  a22(f, -1)

# https://oeis.org/A020522
with open("a22p0.fbjs.txt", "w") as f:
  a22(f, 0)

# https://oeis.org/A171476
with open("a22p1.fbjs.txt", "w") as f:
  a22(f, 1)

# https://oeis.org/A171499
with open("a22p2.fbjs.txt", "w") as f:
  a22(f, 2)

# https://oeis.org/A171472
with open("a22p3.fbjs.txt", "w") as f:
  a22(f, 3)

with open("a22p4.fbjs.txt", "w") as f:
  a22(f, 4)

with open("a22p5.fbjs.txt", "w") as f:
  a22(f, 5)

with open("a22p6.fbjs.txt", "w") as f:
  a22(f, 6)

with open("a22p7.fbjs.txt", "w") as f:
  a22(f, 7)

with open("a22p8.fbjs.txt", "w") as f:
  a22(f, 8)

with open("a22p9.fbjs.txt", "w") as f:
  a22(f, 9)
