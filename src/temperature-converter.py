#! /bin/env python3

# temperature-converter.py - convert temperature from K to °C, °F, and °R

from tkinter import *

def calc(event):
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

Tk().title('Temperature Converter')

Label(text='K').pack()
k_entry = Entry(justify=CENTER)
k_entry.pack()

Label(text='°C').pack()
c_entry = Entry(justify=CENTER)
c_entry.pack()

Label(text='°F').pack()
f_entry = Entry(justify=CENTER)
f_entry.pack()

Label(text='°R').pack()
r_entry = Entry(justify=CENTER)
r_entry.pack()

submit = Button(text='Submit')
submit.bind('<Button-1>', calc)
submit.pack()

mainloop()
