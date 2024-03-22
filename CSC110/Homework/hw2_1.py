# Ethan DeMelo | Due 18 September, 2023
# Homework 2 - Programming in python

# Get user input for amount of a sale
subtotal = float(input("Enter amount of sale $"))

# Determine the discount and apply it to the final
if subtotal > 600:
    total = subtotal - subtotal * 0.3
elif subtotal > 300 and subtotal <= 600:
    total = subtotal - subtotal * 0.2
elif subtotal > 100 and subtotal <= 300:
    total = subtotal - subtotal * 0.1
else:
    total = subtotal - subtotal * 0.05

# Print the final output
print("The final sale amount is $", "{:,.2f}".format(total))