def main():
    txt = []
    tmp = input()
    for i in tmp:
        txt.append(i)

    retxt = txt.reverse()

    for i, j in zip(retxt, txt):
        if i != j:
            return False

    return True

if __name__ == "__main__":
    if main():
        print("palindome")
    else:
        print("non-palindome")