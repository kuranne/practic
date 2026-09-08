b = {
    0 : "first number",
    1 : "operation",
    2 : "second number"
}

a = list(input(f"Enter for {b[i]}: ")for i in range(3))
if a[1] == "+":
    r = int(a[0]) + int(a[2])
elif a[1] == "*":
    r = int(a[0]) * int(a[2])
else: exit()
print(f"Result is {r}")