stu_sc = []
ope = 1
print("Enter for finish")
while True:
    score = input(f"Number {ope} student score: ")
    if score != "":
        stu_sc.append(float(score))
        ope+=1
    elif score == "" and len(stu_sc) == 0:
        print("Type the fucking scores.\n")
    else : break

if len(stu_sc) < 2 or sum(stu_sc)/len(stu_sc) == 1 :
    print("It good to do this, but not for me.\n")
    exit()

ave = sum(stu_sc) / len(stu_sc)
presd = []
for i in stu_sc:
    presd.append((i-ave)**2)
SD = (sum(presd)/(len(stu_sc)-1))**(1/2)

grade = {
    ave + 1.5 * SD : "A",
    ave + 1.0 * SD : "B+",
    ave + 0.5 * SD : "B",
    ave : "C+",
    ave - 0.5 * SD : "C",
    ave - 1.0 * SD : "D+",
    ave - 1.5 * SD : "D",
    float('-inf'): "F"
}

print(f"\nAverage Score: {ave:.2f}")
print(f"Standart Deviation: {SD:.2f} \n")

for i, scsore in enumerate(stu_sc):
    op_grade ="F"
    for tg, gd in sorted(grade.items(), reverse=True):
        if scsore >= tg:
            op_grade = gd
            break
    print(f"Number {i+1} student's score: {scsore} and grade: {op_grade}")
