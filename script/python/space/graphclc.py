import numpy as np
import matplotlib.pyplot as plt

print("Wait for a few hours...")
x_val = 2.0  ## ตรงนี้ x
h_step = 0.0001  ## อันนี้ h
analytederi = 3 * x_val**2 + 3  ## อนุพันธ์


def f(x):
    return x**3 + 3 * x + 1  ## function


def fpanaly(x):
    return 3 * x**2 + 3  ## อนุพันธ์สำหรับกาฟ


def numderivative(func, x, h=1e-6):
    return (func(x + h) - func(x)) / h


deatx = numderivative(f, x_val, h_step)
print(f"x = {x_val} (with h={h_step}): {deatx:.4f}")
print(f"a.d. of f(x) at x = {x_val}: {analytederi:.4f}")

x_range = np.linspace(-5, 5, 100)
y_function = f(x_range)

ydeana = fpanaly(x_range)
ydemun = [numderivative(f, val, h=1e-6) for val in x_range]

plt.figure(figsize=(10, 6))
plt.plot(x_range, y_function, label="f(x) = x^2 + 2x + 1")
plt.plot(x_range, ydemun, label="ND of f'(x)", linestyle="--")
plt.plot(x_range, ydeana, label="AD of f'(x)", linestyle=":")

plt.title("func& num &a.d.")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.show()
