#! /usr/bin/env python3

# mts.py - print MIDI Tuning Standard table of note number, notation, and frequency

PCS = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

PCL, N, A4N, A4F = 12, 128, 69, 440

for n in range(N):
	print(f'{n:03d} | {PCS[n % PCL]:2s}{n // PCL - 1:2d} | {pow(2, (n - A4N) / PCL) * A4F:#15.15g}')
