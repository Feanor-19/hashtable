# Usage:
# python3 abs_error.py *file_name* 
# Note: *file name must have numbers each on a separate line*

import sys
import numpy as np
import math

if len(sys.argv) != 2:
    print("Wrong number of args!")
    exit(-1)

file = open(sys.argv[1])

str_nums = file.read().splitlines()
str_nums = [x.replace(',', '.') for x in str_nums ]

nums = list(map( float, str_nums ) )

std = np.std( nums )

avg = np.average(nums)
abs_err_avg = std / math.sqrt( len(nums) )
rel_err_avg = abs_err_avg / avg  * 100

print( f"Average: {avg}" )
print( f"Abs error of average: {abs_err_avg}" )
print( f"Rel error of average: {rel_err_avg}%" )