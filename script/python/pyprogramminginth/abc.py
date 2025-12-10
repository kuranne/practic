a, b, c = map(int, input("Enter 3 number(split): ").split())
tchar = input("Enter 3 characters (A,B,C) in any order: ")

intg = sorted([a, b, c])
forp = [intg[ord(char) - ord('A')] for char in tchar]

print(*forp)