from random import randrange

def random_order(maximum):
    arr = list(range(0, maximum, 1))
    unarr = []

    while len(arr) > 0:
        rdi = randrange(0, len(arr), 1);
        unarr.append(arr[rdi])
        arr.remove(unarr[-1])

    return unarr

if __name__ == "__main__":
    print(*random_order(int(input())), sep=' ', end='\n')
