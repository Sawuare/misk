#! /usr/bin/env python3

# projectile.py - dragless projectile motion analysis

from math import radians, sin

G0 = 9.80665

angle = float(input('Angle (deg) = '))
speed = float(input('Speed (m/s) = '))

angle = radians(angle)

print(f'Peak  (m)   = {pow(speed * sin(angle), 2) / 2 / G0:g}')
print(f'Range (m)   = {pow(speed, 2) * sin(2 * angle) / G0:g}')
print(f'Time  (s)   = {2 * speed * sin(angle) / G0:g}')
