x = input().strip()
def modulo(valu, divind):
    result = 0
    for i in valu:
        result = (result*10 + int(i)) % divind
    return result
print(modulo(x, 3), modulo(x, 11))