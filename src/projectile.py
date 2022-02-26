#! /usr/bin/env python3

# projectile.py - analyze dragless projectile motion on Earth

from math import radians, sin

ANGLE = radians(float(input("Launch Angle    (deg) = ")))
SPEED =         float(input("Launch Speed    (m/s) = "))

# Standard acceleration due to gravity
GN = 9.80665

print(f"Flight Peak     (m)   = {pow(SPEED * sin(ANGLE), 2) / 2 / GN:g}")
print(f"Flight Range    (m)   = {pow(SPEED, 2) * sin(2 * ANGLE) / GN:g}")
print(f"Flight Duration (s)   = {2 * SPEED * sin(ANGLE) / GN:g}")
