scs = list(tuple(input(f"Enter 4 number with space for {i+1} racer :").split()) for i in range(5))
calced = []
for i in scs:
    calced.append(int(i[0])+int(i[1])+int(i[2])+int(i[3]))

winn = {
    calced[0]: 1,
    calced[1]: 2,
    calced[2]: 3,
    calced[3]: 4,
    calced[4]: 5
}

calced.sort()
print(f"{winn[calced[-1]]} {calced[-1]}")