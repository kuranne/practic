import numpy as np
import matplotlib.pyplot as plt


def logistic_map(x_n, r):
    """
    ฟังก์ชันสำหรับคำนวณ Logistic Map: x_{n+1} = r * x_n * (1 - x_n)
    """
    return r * x_n * (1 - x_n)


# --- พารามิเตอร์และการตั้งค่าการจำลอง ---
num_iterations = 25  # จำนวนรอบของการจำลอง
initial_condition_1 = 0.5  # เงื่อนไขเริ่มต้นที่ 1
initial_condition_2 = 0.500001  # เงื่อนไขเริ่มต้นที่ 2 (ต่างกันเล็กน้อยมาก)

# --- กรณีที่แสดงพฤติกรรมอลวน ---
r_chaotic = 3.9

# --- เก็บผลลัพธ์ ---
x_values_1 = [initial_condition_1]
x_values_2 = [initial_condition_2]

# --- จำลอง Logistic Map สำหรับเงื่อนไขเริ่มต้นทั้งสอง ---
for _ in range(num_iterations - 1):
    x_next_1 = logistic_map(x_values_1[-1], r_chaotic)
    x_next_2 = logistic_map(x_values_2[-1], r_chaotic)
    x_values_1.append(x_next_1)
    x_values_2.append(x_next_2)

# --- พล็อตผลลัพธ์ ---
plt.figure(figsize=(10, 6))
plt.plot(x_values_1, label=f"Initial Condition 1: {initial_condition_1}")
plt.plot(
    x_values_2, label=f"Initial Condition 2: {initial_condition_2}", linestyle="--"
)
plt.title(f"Logistic Map: r = {r_chaotic} (Chaotic Regime)")
plt.xlabel("Iteration (n)")
plt.ylabel("x_n")
plt.grid(True)
plt.legend()
plt.show()

# --- ลองพล็อต Bifurcation Diagram (แสดงพฤติกรรมสำหรับ r ต่างๆ) ---
# นี่คือการแสดงว่าระบบเปลี่ยนจากเสถียรเป็นอลวนอย่างไร
# อาจใช้เวลานานขึ้นเล็กน้อย
print("\nGenerating Bifurcation Diagram (may take a moment)...")
num_r_values = 10000
num_transient = 100  # ทิ้งช่วงแรกออกไปเพื่อรอให้ระบบเข้าสู่สภาวะเสถียร/อลวน
num_plot = 1000  # เก็บค่าสุดท้ายเพื่อพล็อต

r_values = np.linspace(2.5, 4.0, num_r_values)
x_bifurcation = []
y_bifurcation = []

for r_val in r_values:
    x_n_bif = 0.5  # เริ่มต้นจากเงื่อนไขเดียวกัน
    for _ in range(num_transient):  # ทิ้งช่วง transient
        x_n_bif = logistic_map(x_n_bif, r_val)
    for _ in range(num_plot):  # เก็บค่าที่จะพล็อต
        x_n_bif = logistic_map(x_n_bif, r_val)
        x_bifurcation.append(r_val)
        y_bifurcation.append(x_n_bif)

plt.figure(figsize=(12, 7))
plt.plot(x_bifurcation, y_bifurcation, ",k", alpha=0.2)  # ใช้เครื่องหมายจุลภาคเพื่อให้จุดเล็กๆ
plt.title("Bifurcation Diagram of the Logistic Map")
plt.xlabel("Parameter r")
plt.ylabel("x_n")
plt.grid(True)
plt.show()
