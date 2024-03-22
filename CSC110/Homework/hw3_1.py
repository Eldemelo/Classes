# Ethan DeMelo | Due 25 September, 2023
# Homework 3 - Programming in python

# Get number of golfers and score for each then ask for the cutoff

# Declare global variables
scores = []
numGolf = int(input("How many golfers are in the tournament? "))
scoreMet = 0

# Get scores for each golfer
for i in range(numGolf):
    scores.append(int(input("Enter two-day score for golfer " + str(i + 1) + ": ")))

# Get cut-off score
cutoff = int(input("Enter the cut-off score: "))

# Get the percent of golfers that made the cut
for i in range(numGolf):
    if scores[i] < cutoff:
        scoreMet += 1

# Calculate the percentage met and print the output
if scoreMet == 0:
    print("No golfers made the cut")
else:
    percentMet = (scoreMet / len(scores)) * 100
    print("The percent of golfers that made the cut is", percentMet, "%.")