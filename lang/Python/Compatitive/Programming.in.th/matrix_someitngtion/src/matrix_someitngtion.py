m, n = map(int, input("1st for row, 2nd for colum(Space): ").split())
firmatrix = [list(map(int,input(f"first matrix row {i+1} ({n} number with space):").split())) for i in range(m)]
secmatrix = [list(map(int,input(f"second matrix row {i+1} ({n} number with space):").split())) for i in range(m)]

resmatrix = []
for i in range(m):
    row = []
    for j in range(n):
        row.append(firmatrix[i][j] + secmatrix[i][j])
    
    resmatrix.append(row)

for row in resmatrix:
    print(" ".join(map(str, row)))