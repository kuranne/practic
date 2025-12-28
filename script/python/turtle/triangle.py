import turtle

tt = turtle.Turtle()

length = int(input("L:"))
degree = int(input("C:"))

tt.speed('fastest')

while True:
    tt.forward(length)
    tt.left(degree)