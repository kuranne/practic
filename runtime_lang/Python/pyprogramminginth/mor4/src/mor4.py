x = []
for i in range(10):
    for j in range(10):
        if i == j and i > j:
            print("*", end=" ")
        else:
            if i not in x and j not in x:
                x.append(i)

for i in x:
    print(i)