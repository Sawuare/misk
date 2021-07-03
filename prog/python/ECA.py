#! /usr/bin/env python3

# ECA.py - Elementary Cellular Automata on a 1376x768x32 BGRA framebuffer

import random

RULE = int(input('Rule: '))
SEED = int(input('Seed: '))

BLACK = b'\x00\x00\x00\x00'
WHITE = b'\xff\xff\xff\x00'

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

# Disable cursor
print('\x1b[?25l', end = '', flush = True)

with open('/dev/fb0', 'wb') as fb:
	for y in range(YRES):
		for x in range(XRES):
			fb.write(WHITE if cells[x] else BLACK)

			P = cells[x - 1]
			Q = cells[x]
			R = cells[(x + 1) % XRES]

			clone[x] = RULE >> (P << 2 | Q << 1 | R) & 1

		cells = [*clone]

input()

# Enable cursor
print('\x1b[?25h', end = '')
