operation = input("Enter operation (2/10): ")

def two_to_ten(innum):
    count = 0
    realnum = 0

    lenght = len(innum)
    while count < lenght:
        realnum += int(innum[count]) * (2 ** (lenght - count -1))
        count += 1
    return realnum

def ten_to_two(innum):
    tennum = int(innum)
    if tennum < 0:
        return "ไม่เอาเลข 0 โว้ย"
    if tennum == 0:
        return "0"

    binarytems = []
    temps = tennum

    high_bit_power = 0
    while (2**(high_bit_power + 1)) <= temps:
        high_bit_power += 1
    
    for power in range(high_bit_power, -1, -1):
        pval = 2**power
        if temps >= pval:
            binarytems.append(1)
            temps -= pval
        else:
            binarytems.append(0)
            
    return ''.join(map(str, binarytems))

if operation == "2":
    innum = input("Enter num: ")
    result = two_to_ten(innum)
elif operation == "10":
    innum = input("Enter num: ")
    result = ten_to_two(innum)
else:
    result = "What the heck is that operation?"
print(result)