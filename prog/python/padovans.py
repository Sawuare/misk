#! /usr/bin/env python3

# padovans.py - print all Padovan numbers < 2 ** 64

ps = [1, 1, 1]

print(ps[0])
print(ps[1])
print(ps[2])

while True:
	ps.append(ps[-2] + ps[-3])

	if ps[-1] < 2 ** 64:
		print(ps[-1])
	else:
		break
