#! /usr/bin/env python3

# eca2fb.py - paint elementary cellular automata on the Linux framebuffer device

import random

RULE = int(input("Rule = "))
SEED = int(input("Seed = "))

FB_PATH = "/dev/fb0"

# UNPORTABLE
FB_BLACK = b"\x00\x00\x00\x00"
FB_WHITE = b"\xff\xff\xff\x00"

# UNPORTABLE
FB_WIDTH  = 1376
FB_HEIGHT = 768

cells = FB_WIDTH * [0]
clone = FB_WIDTH * [0]

if (SEED):
  random.seed(SEED)

  for x in range(FB_WIDTH):
    cells[x] = random.randint(0, 1)
else:
  cells[FB_WIDTH // 2] = 1

# Disable the text cursor
print("\x1b[?25l", end = "", flush = True)

with open(FB_PATH, "wb") as fb:
  for y in range(FB_HEIGHT):
    for x in range(FB_WIDTH):
      fb.write(FB_WHITE if cells[x] else FB_BLACK)

      # The neighbors
      p = cells[x - 1]
      q = cells[x]
      r = cells[x + 1 if x != FB_WIDTH - 1 else 0]

      clone[x] = RULE >> (p << 2 | q << 1 | r) & 1

    cells = [*clone]

input()

# Enable the text cursor, reset its position, and clear the screen
print("\x1b[?25h\x1b[H\x1b[3J", end = "")
