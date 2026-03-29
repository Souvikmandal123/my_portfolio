N = int(input())
powers = list(map(int, input().split()))

team_a_power = 0
team_b_power = 0

# Sort the powers
powers.sort(key=lambda x: (abs(x), -x), reverse=True)

# Assign Avengers to teams alternatively
ironman_turn = True

for power in powers:
    if ironman_turn:
        team_a_power += power
    else:
        team_b_power += power
    ironman_turn = not ironman_turn

power_difference = abs(team_a_power - team_b_power)
print(power_difference)