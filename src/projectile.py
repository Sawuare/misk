#! /usr/bin/env python3

# projectile.py - analyze dragless projectile motion on Earth

from math import radians, sin

ANGLE = radians(float(input("Angle    (deg) = ")))
SPEED =         float(input("Speed    (m/s) = "))

GN = 9.80665

print(f"Peak     (m)   = {pow(SPEED * sin(ANGLE), 2) / 2 / GN:g}")
print(f"Range    (m)   = {pow(SPEED, 2) * sin(2 * ANGLE) / GN:g}")
print(f"Duration (s)   = {2 * SPEED * sin(ANGLE) / GN:g}")
