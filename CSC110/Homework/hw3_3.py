# Ethan DeMelo | Due 25 September, 2023
# Homework 3 - Programming in python

# Declare Variables
numScores = int(input("How many golf scores have you collected? "))
golfScores = []
sampleScores = []

# Get scores
for i in range(numScores):
    golfScores.append(input("Enter score: "))

# Get sample rate and make a new list with it
sampleRate = int(input("Enter sample rate (k): "))
for i in range(numScores):
    if i % sampleRate == 0:
        sampleScores.append(int(golfScores[i]))

# print samples scores
print("The sampled scores are:")
print(sampleScores)