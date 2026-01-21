def binary_search(arr, trgt):
    leftindex = 0
    rightindex = len(arr) - 1
    
    while leftindex <= rightindex:
        midindex = (leftindex + rightindex) // 2
        if trgt == arr[midindex]:
            return midindex
        elif trgt < arr[midindex]:
            rightindex = midindex - 1
        else:
            leftindex = midindex + 1
    
    return -1
    

def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    mid = [x for x in arr if x == pivot]
    left = [x for x in arr if x < pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + quicksort(mid) + quicksort(right)
    


def main():
    arr = [2,3,1,4,5,0,9,8,17,16,14,18,10,6]
    arr = quicksort(arr)

    while True:
        try: expect = int(input())
        except: 
            ValueError
            continue
        if expect == -1:
            break
        print(binary_search(arr, expect))


if __name__ == "__main__":
    main()