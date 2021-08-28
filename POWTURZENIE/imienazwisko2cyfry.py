
import string
import sys

# print(string.ascii_lowercase)


originString = ""
if len(sys.argv) == 2:
    originString = sys.argv[1]
else:
    originString = input("Podaj string do konwercji: ") # krzysztofjacekkukizjfk (22)

originString = originString.lower()

#zwiezle
print(originString, f"({len(originString)})",)
for ch in originString:
    print(string.ascii_lowercase.index(ch), end=",")
print()
print()

# szeroko
for ch in originString:
    print(ch, end="\t")
print()
for ch in originString:
    print(string.ascii_lowercase.index(ch), end="\t")
print()