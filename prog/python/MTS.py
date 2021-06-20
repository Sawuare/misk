#! /usr/bin/env python3

# MTS.py - print MIDI Tuning Standard table of note number, notation, and frequency

pc = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

PC, N, A4N, A4F = 12, 128, 69, 440

for n in range(N):
	print(f'{n:03d} | {pc[n % PC]:2s}{n // PC - 1:2d} | {pow(2, (n - A4N) / PC) * A4F:#15.15g}')
