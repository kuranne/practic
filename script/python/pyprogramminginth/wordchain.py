length = int(input())
line = int(input())
array_str = [input()]

def match(a, b):
    count = 0
    for i, j in zip(a, b):
        if i != j:
            count += 1
        if count > 2:
            return False
    return True

for i in range(1, line):
    if match(array_str[i - 1], temp := input()):
        array_str.append(temp)
    else:
        break

print(array_str[-1])
