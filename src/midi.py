#! /usr/bin/env python3

# midi.py - print a table of MIDI note number, notation, and frequency

# Sequence of pitch classes
PCS = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]

PCN = 12  # Number of pitch classes
N   = 128 # Number of MIDI notes
A4N = 69  # Number of note A4
A4F = 440 # Frequency of note A4

for n in range(N):
  # 15 is the empirical maximum precision of frequency
  print(f"{n:03d} | {PCS[n % PCN]:2s}{n // PCN - 1:2d} | {pow(2, (n - A4N) / PCN) * A4F:#15.15g}")
