x, y = map(int, input("2 Number First for step and second for distant: ").split())
result = y // x

if y % x != 0:
    result += 1
if x > y:
    result = 2

print(f"Frog would jump for {result} times")