# Ethan DeMelo | 30 October, 2023
# Homework 6

# Program to read a file's data and output a new file sorted by percentage of female
# CS Graduates

# Function to get data from a file
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

# Function to calculate the percentage of female CS grads per year
def calcPercent(maleList, femaleList):
    percentList = []
    for i in range(len(maleList)):
        currPercent = femaleList[i] / (maleList[i] + femaleList[i])
        percentList.append(currPercent)
    return percentList

# Sorting function to sort both lists by the percentage of female CS grads
def dualSort(yearList, percentList):
    for i in range(1, len(percentList)):
        savePercent = percentList[i]
        saveYear = yearList[i]
        j = i
        while j > 0 and percentList[j - 1] < savePercent:
            percentList[j] = percentList[j - 1]
            yearList[j] = yearList[j - 1]
            j = j - 1
        percentList[j] = savePercent
        yearList[j] = saveYear
    return percentList, yearList

# Function to write sorted data to a file
def writeTofile(percentList, yearList):
    infile = open("pctWomen-sorted.csv", "w")
    infile.write("year,pctWomen\n")
    for i in range(len(percentList)):
        infile.write(str(yearList[i]) + ", " + str(percentList[i]) + "\n")
    infile.close()
    print("Your output has been saved in pctWomen-sorted.csv")
    return

# Main function to perform calls to other functions
def main():
    yearList, maleList, femaleList = getData()
    percentList = calcPercent(maleList, femaleList)
    percentList, yearList = dualSort(yearList, percentList)
    writeTofile(percentList, yearList)
    return
