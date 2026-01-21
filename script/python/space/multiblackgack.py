import random as rd
import time
import os

os.system("cls" if os.name == "nt" else "clear")

while True:
    winner, turn, cheats, allbot = None, 1, input("Want to cheat? Y/N: "), False

    usedcard = []
    prewin = []
    alchk = []

    life = True
    alllose = 0
    revals = 0
    outed = 0

    if cheats == "Y" or cheats == "y":
        cheats = True
    elif cheats == "N" or cheats == "n":
        cheats = False
    elif cheats == "b":
        print("All is Bot")
        allbot = True
    else:
        print("I think you are good boy so won't cheat, right?")
        cheats = False

    class Hand:
        def __init__(self):
            self.number = []
            self.symbol = []
            self.cadidate = True
            self.stillplay = True

        def chkifexceed(self):

            if sum(self.number) > 21 and 11 in self.number:
                for i in range(len(self.number)):
                    if self.number[i] == 11:
                        self.number[i] = 1
                        break

            self.cadidate = False if sum(self.number) > 21 else True
            return False if sum(self.number) > 21 else True

        def draw(self):
            global outed
            global usedcard
            while True:

                pick = int(rd.randrange(1, 11, 1))
                if pick == 1 and sum(self.number) + 11 <= 21:
                    pick = 11

                symbl = {1: "♠︎", 2: "♣︎", 3: "♡", 4: "♢"}
                pksymbl = int(rd.randrange(1, 5, 1))
                pkten = int(rd.randrange(1, 5, 1))
                theten = {1: "K", 2: "Q", 3: "J", 4: pick}
                while_ten = theten[pkten]

                toOut = f"{'A' if pick == 1 or pick == 11 else while_ten if pick == 10 else pick }{symbl[pksymbl]}"
                if toOut in usedcard:
                    continue

                outed += 1
                usedcard.append(toOut)
                self.number.append(pick)
                self.symbol.append(toOut)
                break

        def inTurn(self, n):
            global revals
            print("<> d to draw, r to reval, q to quit <>\n")
            print(f"Turn {turn} | playername: {n}")
            input()
            if self.chkifexceed():
                print(f"hand: {', '.join(self.symbol)} >> {sum(self.number)}")
                match input("sel: "):
                    case "d":
                        self.draw()
                        print(f"You draw {self.symbol[-1]}!")
                    case "r":
                        self.stillplay = False
                        revals += 1
                    case "q":
                        life = False
                        return 0
                    case _:
                        print("error, I will draw for you :)")
                        self.draw()
                        print(f"You draw {self.symbol[-1]}!")
            else:
                if input("Whoa, u lose want to reval?(r to reval): ") == "r":
                    print("revaled")
                else:
                    print("Yeah, that mean reval too.")
                self.stillplay = False
                revals += 1
            time.sleep(1)
            return 1

    while True:
        try:
            szplayer = int(input("Enter the player size: "))
        except:
            ValueError
            print("Player size must be integer.")
            continue
        if szplayer <= 1:
            print(f"The player size must more than {szplayer}")
            continue
        break

    if allbot:
        player = list(
            {"name": f"Bot{i+1}", "hand": Hand(), "isBot": True, "canplay": True}
            for i in range(szplayer)
        )
    else:
        player = list(
            {
                "name": input(f"player {i+1}'s name(type bot for Bot): "),
                "hand": Hand(),
                "isBot": False,
                "canplay": True,
            }
            for i in range(szplayer)
        )
        w, ps = 1, 1
        for i in player:
            if i["name"] == "bot" or i["name"] == "Bot":
                i["name"] = f"{i['name']}{w}"
                w += 1
                i["isBot"] = True
            elif i["name"] == "":
                i["name"] = f"{ps}"
                ps += 1

    while life:
        if revals == szplayer // 2:
            break
        if alllose == szplayer:
            break
        for p in player:
            if outed >= 52:
                life = False
                break
            if p["name"] not in alchk:
                if p["hand"].stillplay and not p["isBot"]:
                    os.system("cls" if os.name == "nt" else "clear")
                    if cheats or allbot:
                        for d in player:
                            print(
                                f"{d['name']}: {', '.join(d['hand'].symbol)} >> {sum(d['hand'].number)}"
                            )
                    if p["hand"].inTurn(p["name"]) == 0:
                        break
                elif p["hand"].stillplay and p["isBot"]:
                    p["hand"].chkifexceed()
                    if sum(p["hand"].number) >= 17:
                        p["hand"].stillplay = False
                        revals += 1
                    else:
                        p["hand"].draw()
                elif p["canplay"]:
                    p["canplay"] = False
                    alchk.append(p["name"])
                    alllose += 1
        turn += 1

    for p in player:
        if p["hand"].cadidate and sum(p["hand"].number) <= 21:
            prewin.append({"name": p["name"], "score": sum(p["hand"].number)})

    if len(prewin) > 0:
        prewin.sort(key=lambda x: x["score"], reverse=True)
        top_score = prewin[0]["score"]
        winners = [p["name"] for p in prewin if p["score"] == top_score]
        if len(winners) == 1:
            winner = winners[0]
        else:
            winner = "due to many winner."
    else:
        winner = None

    os.system("cls" if os.name == "nt" else "clear")
    if winner is None:
        print("There is no winner")
    elif winner == "due to many winner.":
        print(f"There is no winner, {winner}, the highest points are {top_score}.")
    else:
        print(f"The Winner is {winner} with {prewin[0]['score']} point.")
    for p in player:
        print(f"{p['name']}: {', '.join(p['hand'].symbol)} >> {sum(p['hand'].number)}")

    if allbot:
        score = 0
        for sc in player:
            score += sum(sc["hand"].number)
        print(f"ave is {score/szplayer}")

    match input("Play again?[Y]: "):
        case "Y":
            continue
        case "y":
            continue
        case _:
            break
