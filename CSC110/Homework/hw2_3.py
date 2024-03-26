# Ethan DeMelo | Due 18 September, 2023
# Homework 2 - Programming in python

# Get input for first month
rainfall = float(input("Rainfall for month 1: "))

# Initialize variables
i = 1
lowest = rainfall
highest = rainfall

# Get input for the rest of the months
while i < 12:
    rainfall = float(input("Rainfall for month " + str(i + 1) + ": "))
    if rainfall > highest:
        highest = rainfall
    elif rainfall < lowest:
        lowest = rainfall
    i += 1

# Print the highest and lowest rainfall amounts
print("The highest monthly rainfall was", highest, "inches.")
print("The lowest monthly rainfall was", lowest, "inches.")