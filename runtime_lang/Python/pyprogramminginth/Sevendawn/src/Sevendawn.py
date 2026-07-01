dwaf = list(int(input(f"Number {i+1} dwaf:")) for i in range(9))
imposter = sum(dwaf) - 100
for i in dwaf:
    for j in dwaf:
        if i + j == imposter:
            dwaf.remove(i)
            dwaf.remove(j)
            break
    if len(dwaf) == 7:
        break

for i in dwaf:
    print(i)
