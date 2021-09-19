#! /usr/bin/env python3

# k2cfr.py - convert temperature from kelvin to Celsius, Fahrenheit, and Rankine

K = float(input("Kelvin     = "))

print(f"Celsius    = {K - 273.15:g}")
print(f"Fahrenheit = {K * 1.8 - 459.67:g}")
print(f"Rankine    = {K * 1.8:g}")
