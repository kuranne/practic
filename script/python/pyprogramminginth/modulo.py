x = []
for i in range(10):
    x.append(int(input(f"Enter number {i+1}: ")))
    i += 1


def modulo(valu):
    frac = 0
    for i in x:
        if i < 42:
            frac = frac + 1
        else:
            a = i - 42*(i//42)
            frac = frac + a
    return frac

print(modulo(x))
