#! /usr/bin/env python3

# fbzs.py - write the interesting fb Z sequences

Z_MAX = 2 ** 32 - 1

def a19(f, m):
  n = 0 if m >= 0 else -m + 1

  zs = []

  while True:
    z = 2 ** (2 * n + m) - 2 ** n

    if z <= Z_MAX:
      zs.append(z)
    else:
      break

    n += 1

  print(*zs, file = f)

# https://oeis.org/A059153
with open('a19m-1.fb.txt', 'w') as f:
  a19(f, -1)

# https://oeis.org/A020522
with open('a19m0.fb.txt', 'w') as f:
  a19(f, 0)

# https://oeis.org/A171476
with open('a19m1.fb.txt', 'w') as f:
  a19(f, 1)

# https://oeis.org/A171499
with open('a19m2.fb.txt', 'w') as f:
  a19(f, 2)

# https://oeis.org/A171472
with open('a19m3.fb.txt', 'w') as f:
  a19(f, 3)
