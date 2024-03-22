# Ethan DeMelo | Due 25 September, 2023
# Homework 3 - Programming in python

# find leading golfer

# Declare global variables
numGolf = int(input("How many golfers are in the tournament? "))
golfName = []
scores = []
leadIndex = 0

# Get scores for each golfer
for i in range(numGolf):
    golfName.append(input("Enter name of golfer " + str(i + 1) + ": "))
    scores.append(int(input("Enter score for golfer " + str(i + 1) + ": ")))

# find the highest golfer
for i in range(numGolf):
    if scores[i] < scores[leadIndex]:
        leadIndex = i

# Print the output
print("The current leader of the tournament is", golfName[leadIndex], "with a score of", scores[leadIndex])