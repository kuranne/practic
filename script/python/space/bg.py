# Black Jack by Kuramais
import random as rd
import time
import os

winner, turn, cheats = None, 1, input("Want to cheat? Y/N: ")

usedcard = []

if cheats == "Y" or cheats == "y":
    cheats = True
elif cheats == "N" or cheats == "n":
    cheats = False
else:
    print("I think you are good boy so won't cheat, right?")
    cheats = False


class Hand:
    def __init__(self, number=None, symbol=None):
        self.number = [] if number == None else [number]
        self.symbol = [] if symbol == None else [f"{number}{symbol}"]
        self.cadidate = True

    def draw(self):
        while True:
            pick = int(rd.randrange(1, 11, 1))
            if pick == 1 and sum(self.number) + 11 <= 21:
                pick = 11

            symbl = {1: "♠︎", 2: "♣︎", 3: "♡", 4: "♢"}
            pksymbl = int(rd.randrange(1, 5, 1))
            pkten = int(rd.randrange(1, 5, 1))
            theten = {1: "K", 2: "Q", 3: "J", 4: pick}
            while_ten = theten[pkten]

            toOut = f"{"A" if pick == 1 or pick == 11 else while_ten if pick == 10 else pick }{symbl[pksymbl]}"
            if self.symbol in usedcard:
                continue

            usedcard.append(toOut)
            self.number.append(pick)
            self.symbol.append(toOut)
            break

    def chkifexceed(self):

        if sum(self.number) > 21 and 11 in self.number:
            for i in range(len(self.number)):
                if self.number[i] == 11:
                    self.number[i] = 1
                    break

        self.cadidate = False if sum(self.number) > 21 else True
        return True if sum(self.number) > 21 else False

    def chkbot(self):
        if sum(self.number) < 14:
            return False
        else:
            return True if sum(self.number) > 17 else False


yrhand = Hand()
ophand = Hand()

while True:
    os.system("cls" if os.name == "nt" else "clear")
    print("\n>>> d for draw, r for reval or q to quit <<<\n")
    try:
        print(f"U draw {yrhand.symbol[-1]}!")
    except:
        IndexError

    print(f"turn {turn}\nYours: {", ".join(yrhand.symbol)} >> {sum(yrhand.number)}")
    if cheats:
        print(f"Bot's: {", ".join(ophand.symbol)} >> {sum(ophand.number)}")

    match input("sel: "):
        case "q":
            break
        case "d":
            yrhand.draw()
            if ophand.chkbot():
                break
            else:
                ophand.draw()
        case "r":
            if not ophand.chkbot():
                ophand.draw()
            break
        case _:
            print("error, I will draw for you :)")
            yrhand.draw()
            if ophand.chkbot():
                break
            else:
                ophand.draw()

    if yrhand.chkifexceed() or ophand.chkifexceed():
        break

    turn += 1

if winner == None:
    yrhand.chkifexceed()
    ophand.chkifexceed()
    if not yrhand.cadidate or not ophand.cadidate:
        if yrhand.cadidate:
            winner = "You"
        else:
            winner = "Bot"
    else:
        if sum(yrhand.number) > sum(ophand.number):
            winner = "You"
        elif sum(yrhand.number) < sum(ophand.number):
            winner = "Bot"
        else:
            winner = "Draw"

os.system("cls" if os.name == "nt" else "clear")
print("reval hands\nyours|bot's")
for i in range(len(yrhand.number)):
    try:
        print(f"{i+1}: {yrhand.symbol[i]} {ophand.symbol[i]}")
    except:
        IndexError
        print(f"{i+1}: {yrhand.symbol[i]}")


(
    print(
        f"winner is {winner}, with score {sum(ophand.number) if winner == "Bot" else sum(yrhand.number)} : {sum(yrhand.number) if winner == "Bot" else sum(ophand.number)}"
    )
    if winner != "Draw"
    else print(
        f"Draw with score {sum(ophand.number) if winner == "Bot" else sum(yrhand.number)} : {sum(yrhand.number) if winner == "Bot" else sum(ophand.number)}"
    )
)
time.sleep(1)
