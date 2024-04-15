import sys

if len(sys.argv) != 2:
    print("No file given!")
    exit()
else:
    filename = sys.argv[1]

inp = open(filename)

uni = set()
for word in inp:
    uni.add(word)

print(len(uni))

inp.close()