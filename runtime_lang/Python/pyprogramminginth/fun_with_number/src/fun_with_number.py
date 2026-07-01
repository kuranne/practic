n = int(input())
nums = list(map(int, input("Enter 4 numbers with space: ").split()))
nums.sort()
count = 1
while nums[0] == 0:
    nums[0], nums[count] = nums[count], nums[0]
    count += 1
print("".join(map(str, nums)))
