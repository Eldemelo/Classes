# Ethan DeMelo | Due 18 September, 2023
# Homework 2 - Programming in python

# create global variables
i = 0
total = 0
numberOfToys = int(input("How many toys are in the catalog? "))

# Get toy prices
while i < numberOfToys:
    total += float(input("Enter toy price $"))
    i += 1

# Find the average
average = total / numberOfToys

# Print the output
print("The average price of toys in the catalog is: $", round(average, 2))