team = list({"tname":str(input(f"Name for team {i+1}: ")), "scs":0, "goaled":0, "goal":0}for i in range(4))
score = list(tuple(map(int, input(f"Score for team {i+1}(4 number with space by {i+1} should be 0): ").split()))for i in range(4))
for i in range(4):
    for j in range(4):
        if i != j:
            team[i]["goal"] += score[i][j]
            team[i]["goaled"] += (score[j][i] - score[i][j])
            if score[i][j] > score[j][i]:
                team[i]["scs"] += 3
            elif score[i][j] == score[j][i]:
                team[i]["scs"] += 1
team.sort(key=lambda x: (x["scs"], -x["goaled"], x["goal"]), reverse=True)
for i in team:
    print(i["tname"], i["scs"])