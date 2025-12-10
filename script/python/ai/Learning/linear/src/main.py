import numpy as np
from sklearn.linear_model import LinearRegression

x = np.array([[1], [2], [3], [4], [5], [6], [7]])
y = np.array([3, 6, 9, 12, 15, 18, 21])

model = LinearRegression()
model.fit(x, y)
print(model.predict([[-10]]))