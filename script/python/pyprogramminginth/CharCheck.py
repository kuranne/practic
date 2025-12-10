a = str(input("Enter any string in single line(don't space):"))
upper = 0
lower = 0
for char in a:
    if char.isupper():
        upper += 1
    elif char.islower():
        lower += 1

if upper != 0 and lower == 0:
    print("All Capital Letter")
elif upper == 0 and lower != 0:
    print("All Small Letter")
else:
    print("Mix")