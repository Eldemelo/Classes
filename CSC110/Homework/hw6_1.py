# Ethan DeMelo | 30 October, 2023
# Homework 6

# Reads data from a file and determines whether a binary or linear
# Search is more efficient

# Function to get data from a file and append to lists
def getData():
    yearList = []
    maleList = []
    femaleList = []

    # Ask user for file name and determine if it exists
    validFile = False
    while validFile == False:
        fname = input("Please enter the name of the data file: ")
        try:
            infile = open(fname, "r")
            validFile = True
        except:
            print("Invalid file name, try again ...")

    # Appends data to lists, skipping over the first line
    currLine = infile.readline()
    currLine = infile.readline()
    currLine = currLine.strip()
    while currLine != "":
        currYear, currMale, currFemale = currLine.split(",")
        yearList.append(int(currYear))
        maleList.append(int(currMale))
        femaleList.append(int(currFemale))
        currLine = infile.readline()
        currLine = currLine.strip()
    
    # Close the open file and return the lists
    infile.close()
    return yearList, maleList, femaleList

# Function to get the year and test for input issues
def getUserYear(yearList):
    validYear = False
    while validYear == False:
        # Checks if user inputs a valid integer
        try:
            validInt = False
            currInput = int(input("Enter a year: "))
            # Checks if the year is in range assuming the years are in order
            maxYear = yearList[len(yearList) -1]
            minYear = yearList[0]
            validInt = True
            if currInput <= maxYear and currInput >= minYear:
                year = currInput
                validYear = True
            else:
                raise ValueError("Invalid range")
        except ValueError:
            if validInt == False:
                print("Invalid entry, try again...")
            else:
                print("Year not in range, try again...")
    return year

# Function to get the year using a linear search
def getYearLinear(yearList, year):
    # The worst case would be if the desired year is at the last element
    counter = 0
    yearFound = False
    i = 0
    while yearFound == False and i < len(yearList):
        counter += 1
        if yearList[i] == year:
            position = i
            yearFound = True
        i += 1
    print("Linear Search: comps = " + str(counter))
    return position

# function to use binary search method to find the year in the year list
def getYearBinary(yearList, year):
    # The worst case would be if the desired year is the first or last element
    indexFound = False
    low = 0
    high = len(yearList) - 1
    counter = 0
    # Performs binary counting and comparisons
    while low <= high and indexFound == False:
        mid = int((low + high) / 2)
        if yearList[mid] == year:
            indexFound = True
        elif year < yearList[mid]:
            high = mid - 1
        else:
            low = mid + 1
        counter += 1
    print("Binary Search: comps = " + str(counter))
    position = mid
    return position


# Main function to perform call to other functions and store variables
def main():
    yearList, maleList, femaleList = getData()
    year = getUserYear(yearList)
    binaryPosition = getYearBinary(yearList, year)
    linearPosition = getYearLinear(yearList, year)
    print("In", year, "there were", femaleList[binaryPosition], "women CS graduates.")
    return

main()