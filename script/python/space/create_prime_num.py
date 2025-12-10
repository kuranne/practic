from math import sqrt

ofnum = int(input("Prime number at N: "))  # selected order of number
prime = [2]
nxnm = 3  # next number

if ofnum <= 0:
    raise ValueError(f"N can't be {ofnum}, by the way it must be positive number.")
    quit


def chkprm(prime, nxnm):  # chkprm = check if it prime
    isprm = True
    limit = int(sqrt(nxnm)) + 1

    for prm in prime:
        if prm > limit:
            break
        if nxnm % prm == 0:
            isprm = False
            break

    return isprm


while len(prime) < ofnum:
    if chkprm(prime, nxnm):
        prime.append(nxnm)
    nxnm += 2

print(f"...,{prime[-3]},{prime[-2]},{prime[-1]}")
