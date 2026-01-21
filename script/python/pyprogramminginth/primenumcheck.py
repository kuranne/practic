n = int(input("Enter a number to check if it's prime: "))
i = 2

while True:
    if i >= n:
        print("Yep")
        break

    if n % i == 0:
        print(f"Nope, Because it can devided by {i}")
        break
    
    i+=1
