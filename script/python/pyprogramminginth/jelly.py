jelly = list(map(int, input("Enter 3 numbers with space: ").split()))
count = 0
while sum(jelly) != 3:
    jelly = sorted(jelly)
    if jelly[-1] % 2 != 0:
        jelly[-1] -= 1
        jelly[-1] = jelly[-1] // 2
        count += 1
    else:
        jelly[-1] = jelly[-1] // 2
        count += 1

print(count)
