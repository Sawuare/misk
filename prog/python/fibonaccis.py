#! /usr/bin/env python3

# fibonaccis.py - print all Fibonacci numbers < 2 ** 64

fs = [0, 1]

print(fs[0])
print(fs[1])

while True:
	fs.append(fs[-1] + fs[-2])

	if fs[-1] < 2 ** 64:
		print(fs[-1])
	else:
		break
