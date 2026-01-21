import math


def main(n):
    if n <= 1:
        return 2
    else:
        prime = [2]
        necnum = 3
        while len(prime) < n:
            thatprime = True
            limit = math.isqrt(necnum)
            for i in prime:
                if i > limit:
                    break
                if necnum % i == 0:
                    thatprime = False
                    break
            if thatprime:
                prime.append(necnum)
            necnum += 2
        return prime[-1]


primeatn = int(input("Prime at: "))
print(main(primeatn))
