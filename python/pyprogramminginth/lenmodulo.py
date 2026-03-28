x = list(int(input(f"Number {i+1} :")) for i in range(10))
frac = []

for i in x:
    a = i%42
    if a not in frac:
        frac.append(a)
    else:
        continue

print(len(frac))