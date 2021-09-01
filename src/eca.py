#! /usr/bin/env python3

# eca.py - paint elementary cellular automata on the framebuffer

import random

RULE = int(input("Rule = "))
SEED = int(input("Seed = "))

# UNPORTABLE
BLACK = b"\x00\x00\x00\x00"
WHITE = b"\xff\xff\xff\x00"

# UNPORTABLE
XRES = 1376
YRES = 768

cells = XRES * [0]
clone = XRES * [0]

if (SEED):
  random.seed(SEED)
  for x in range(XRES):
    cells[x] = random.randint(0, 1)
else:
  cells[XRES // 2] = 1

# Disable the cursor
print("\x1b[?25l", end = "", flush = True)

with open("/dev/fb0", "wb") as fb:
  for y in range(YRES):
    for x in range(XRES):
      fb.write(WHITE if cells[x] else BLACK)

      p = cells[x - 1]
      q = cells[x]
      r = cells[(x + 1) % XRES]

      clone[x] = RULE >> (p << 2 | q << 1 | r) & 1

    cells = [*clone]

input()

# Enable the cursor and clear the screen
print("\x1b[?25h\x1b[3J", end = "")
