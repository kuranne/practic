day = {5 : "Monday", 6 : "Tuesday", 0 : "Wednesday", 1 : "Thursday", 2 : "Friday", 3 : "Saturday", 4 : "Sunday"}
months = {0 : 0, 1 : 31, 2 : 28, 3 : 31, 4 : 30, 5 : 31, 6 : 30, 7 : 31, 8 : 31, 9 : 30, 10 : 31, 11 : 30, 12 : 31}

date, month = map(int, input("Enter two number(dd/mm): ").split())
if month > 12 :
    while month > 12:
        date += months[month % 12]
        month -= 1
for i in range(1, month):
    date += months[i]

print(day[date % 7])