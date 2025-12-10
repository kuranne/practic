def sieve_for_primes_to_n(n):
    size = int(n * (math.log(n) + math.log(math.log(n))))
    sieve = [True] * (size + 1)
    sieve[0] = sieve[1] = False
    for i in range(2, int(size**0.5) + 1):
        if sieve[i]:
            for multiple in range(i * i, size + 1, i):
                sieve[multiple] = False
    primes = [i for i, is_prime in enumerate(sieve) if is_prime]
    return primes


import math


def main(n):
    if n <= 0:
        return None
    primes = sieve_for_primes_to_n(n)
    return primes[n - 1]


def master(n):
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


prime_at_n = int(input("Prime at: "))
if prime_at_n < 6:
    print(master(prime_at_n))
else:
    print(main(prime_at_n))
