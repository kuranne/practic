char = str(input("Input characters in any number(don't space):"))
c = ""
peterpan = [
    ".#..",
    "#.#."
]
wendy = [
    ".*..",
    "*.*."
]
line1 = ["."]
line2 = ["."]
line3 = ["#"]
line4 = ["."]
line5 = ["."]

i = 1
for c in char:
    if i == 3:
        line1.append(wendy[0])
        line2.append(wendy[1])
        line3.append(f"*.{c}.*")
        line4.append(wendy[1])
        line5.append(wendy[0])
        i -= 3
    elif i == 2:
        line1.append(peterpan[0])
        line2.append(peterpan[1])
        line3.append(f"#.{c}.")
        line4.append(peterpan[1])
        line5.append(peterpan[0])
    else:
        line1.append(peterpan[0])
        line2.append(peterpan[1])
        line3.append(f".{c}.")
        line4.append(peterpan[1])
        line5.append(peterpan[0])
    i += 1

if i != 1:
    line3.append("#")

print("".join(line1))
print("".join(line2))
print("".join(line3))
print("".join(line4))
print("".join(line5))