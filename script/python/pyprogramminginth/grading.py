grade = { 80:"A", 75:"B+", 70:"B", 65:"C+", 60:"C", 55:"D+", 50:"D"}

def grading(n = 0):
    global grade
    for s, g in grade.items():
        if n >= s:
            return g
    return "F"

print( grading( sum([int(input()) for _ in range(3)]) ) )