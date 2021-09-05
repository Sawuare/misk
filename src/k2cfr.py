#! /bin/env python3

# k2cfr.py - convert temperature from kelvin to Celsius, Fahrenheit, and Rankine

from tkinter import *

def convert(event):
  k = float(k_entry.get())

  c = k - 273.15
  f = k * 1.8 - 459.67
  r = k * 1.8

  c_entry.delete(0, END)
  f_entry.delete(0, END)
  r_entry.delete(0, END)

  c_entry.insert(0, round(c, 2))
  f_entry.insert(0, round(f, 2))
  r_entry.insert(0, round(r, 2))

Tk().title("k2cfr")

Label(text = "Kelvin").pack()
k_entry = Entry(justify = CENTER)
k_entry.bind("<Return>", convert)
k_entry.pack()

Label(text = "Celsius").pack()
c_entry = Entry(justify = CENTER)
c_entry.pack()

Label(text = "Fahrenheit").pack()
f_entry = Entry(justify = CENTER)
f_entry.pack()

Label(text = "Rankine").pack()
r_entry = Entry(justify = CENTER)
r_entry.pack()

button = Button(text = "Convert")
button.bind("<Button-1>", convert)
button.pack()

mainloop()
