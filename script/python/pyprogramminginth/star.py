noun = int(input("Enter a number:"))
if noun % 2 == 0:
    mode = "even"
    noun -= 1
else:
    mode = "odd"

def star(noun):
    sontainer = []
    first_liner = "-" * (noun // 2) + "*" + "-" * (noun // 2)
    sontainer.append(first_liner)
    for i in range(0, noun // 2):
        sontainer.append("-" * (noun // 2 - 1 - i) + "*" + "-" * (2 * i + 1) + "*" + "-" * (noun // 2 - 1 - i))
    return sontainer

def even(sontainer):
    for i in range(len(sontainer)):
        print(sontainer[i])
    for i in reversed(sontainer):
        print("".join(i))

def odd(sontainer):
    for i in range(len(sontainer)):
        print(sontainer[i])
    sontainer.remove(sontainer[-1])
    for i in reversed(sontainer):
        print("".join(i))

if mode == "even":
    even(star(noun))
if mode == "odd":
    odd(star(noun))
else:
    exit()
