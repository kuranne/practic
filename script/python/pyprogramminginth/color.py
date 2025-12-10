import numpy as np

# ฟังก์ชันจำลอง deuteranomaly (พร่องสีเขียว) แบบประมาณค่า
# ใช้ matrix transformation ที่ใกล้เคียงการรับรู้จริงจาก Brettel et al., 1997
def simulate_deuteranomaly(rgb, severity=0.5):
    """
    rgb: tuple (R, G, B) ในช่วง 0-255
    severity: 0=ปกติ, 1=deuteranopia, 0.5=deuteranomaly กลางๆ
    """
    # normalize
    r, g, b = [x / 255.0 for x in rgb]
    rgb_lin = np.array([r, g, b])
    
    # matrix แปลงสำหรับ deuteranopia (บอดเขียวเต็ม)
    transform = np.array([
        [1.0,       0.0,       0.0],
        [0.494207,  0.0,       1.24827],
        [0.0,       0.0,       1.0]
    ])
    simulated = rgb_lin @ transform.T
    
    # blend ระหว่างปกติ (severity=0) กับบอดเขียว (severity=1)
    out = (1 - severity) * rgb_lin + severity * simulated
    return tuple(max(0, min(1, v)) for v in out)

# ฟังก์ชันค้นหาโค้ดสีชดเชย
def find_compensation(target_rgb, severity=0.5, step=8):
    """
    target_rgb: สีเป้าหมายที่เราต้องการให้เขาเห็น (ในสายตาคนปกติ)
    severity: ความรุนแรงของพร่องสีเขียว
    step: ความละเอียดการค้นหา (8=เร็วพอใช้, 1=ละเอียดมาก)
    """
    target_sim = np.array(target_rgb) / 255.0
    best_rgb = None
    best_diff = float('inf')
    
    for r in range(0, 256, step):
        for g in range(0, 256, step):
            for b in range(0, 256, step):
                sim = np.array(simulate_deuteranomaly((r, g, b), severity))
                diff = np.linalg.norm(sim - target_sim)
                if diff < best_diff:
                    best_diff = diff
                    best_rgb = (r, g, b)
    return best_rgb, best_diff

# Control
target_rgb = tuple(map(int, input("Enter RGB here: ").split()))
comp_rgb, diff_val = find_compensation(target_rgb, severity=0.5, step=4)

# แปลงเป็น HEX
comp_hex = "#{:02X}{:02X}{:02X}".format(*comp_rgb)

print(f"RGB: {comp_rgb}\nHexcode: {comp_hex}\ndegree: {diff_val}")