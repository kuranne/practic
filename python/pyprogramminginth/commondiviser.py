a, b = map(int, input("Two Number for หรม (Split):").split())
while b:
    a, b = b, a % b

print(a)