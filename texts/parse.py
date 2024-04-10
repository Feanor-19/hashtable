import re
import sys

if len(sys.argv) != 2:
    print("No file given!")
    exit()
else:
    filename = sys.argv[1]

inp = open(filename)

out = open("ready_" + filename, "w")

for line in inp:
    words = [x.lower() for x in re.findall(r'\w+', line) ]

    if len(words) > 0:
        for word in words:
            out.write(word + '\n')

inp.close()
out.close()
