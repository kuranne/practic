import numpy as np

n = int(input("Input the number at n: "))
max_product = -float("inf")

for i in range(2, n + 1):
    x_vals = [1]
    y_vals = [1]

    for j in range(1, i * 2 + 1):
        if j % 2 == 0:
            x_vals.append(y_vals[-1] / j)
        else:
            y_vals.append(x_vals[-1] * j)

    xplot = np.linspace(x_vals[-1], x_vals[0], len(x_vals))
    yplot = np.linspace(y_vals[0], y_vals[-1], len(y_vals))

    mid_index_x = int(len(xplot) / 2)
    mid_index_y = int(len(yplot) / 2)

    current_product = xplot[mid_index_x] * yplot[mid_index_y]

    if current_product > max_product:
        max_product = current_product

print(max_product)
