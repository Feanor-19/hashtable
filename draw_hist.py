import numpy as np
import sys
import matplotlib
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
    print("No file given!")
    exit()
else:
    filename = sys.argv[1]

inp = open(filename)
input_data = list(map(int, inp.readlines()))

plt.stairs(values=input_data, fill=True)
plt.grid(axis='y', alpha=0.75)
plt.xlabel('Hash')
plt.ylabel('Load')
plt.title(filename)

plt.show()