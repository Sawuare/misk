#! /usr/bin/env python3

# projectile.py - analyze dragless projectile motion

from math import radians, sin

ANGLE = radians(float(input("Angle (deg) = ")))
SPEED =         float(input("Speed (m/s) = "))

G0 = 9.80665

print(f"Peak  (m)   = {pow(SPEED * sin(ANGLE), 2) / 2 / G0:g}")
print(f"Range (m)   = {pow(SPEED, 2) * sin(2 * ANGLE) / G0:g}")
print(f"Time  (s)   = {2 * SPEED * sin(ANGLE) / G0:g}")
