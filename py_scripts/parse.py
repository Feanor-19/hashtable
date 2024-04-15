import re
import sys

if len(sys.argv) != 3:
    print("Wrong (or empty) args!")
    exit()
else:
    inp_filename = sys.argv[1]
    out_filename = sys.argv[2]

inp = open(inp_filename)

out = open(out_filename, "w")

for line in inp:
    words = [x.lower() for x in re.findall(r'\w+', line) ]

    if len(words) > 0:
        for word in words:
            out.write(word + '\n')

inp.close()
out.close()
