def decorator(func):
    def warpper():
        print("--- Before")
        func()
        print("After ---")
    return warpper

@decorator
def helloworld():
    print("Hello World!")

if __name__ == "__main__":
    helloworld()