# Ethan DeMelo | 23 October, 2023
# Movies Data Programming Project

# Program to get data from a file for movies, append it to lists
# then ask a user what to do with the received data and output it
# to a file if needed

# Function to request file name and retrieve data from it
def getData():
    goodFile = False
    while goodFile != True:
        fname = input("Please enter a file name: ")
        # Begin exception handling
        try:
            # Try to open the file using the name given
            inFile = open(fname, 'r')
            # If the name is valid, set Boolean to true to exit loop
            goodFile = True
        except IOError:
            # If the name is not valid - IOError exception is raised
            print("Invalid filename try again ... ")
    
    # Declare lists to append data to
    titleList, genreList, directorList, yearList, lengthList, revenueList = [], [], [], [], [], []
    # skip over the first line to avoid appending column headers
    line = inFile.readline()
    line = inFile.readline()
    line = line.strip()
    # Append each line of data to different lists
    while line != "":
        currTitle, currGenre, currDirector, currYear, currLength, currRevenue = line.split(",")
        titleList.append(currTitle)
        genreList.append(currGenre)
        directorList.append(currDirector)
        yearList.append(int(currYear))
        lengthList.append(int(currLength))
        revenueList.append(float(currRevenue))
        line = inFile.readline()
        line = line.strip()
    return titleList, genreList, directorList, yearList, lengthList, revenueList

# Function to ask the user what they would like to do wih the data retrieved
def pickFunction():
    print("Please choose one of the following options: ")
    print("1 -- Find all films made by a specified director")
    print("2 -- Find the highest grossing film made in a specific year")
    print("3 -- Find all films made in a given year range in a specified genre")
    print("4 -- Search for a film by title")
    print("5 -- Find average runtime of films with higher revenue than specified value")
    print("6 -- Sort all lists by revenue and write the results to a new file")
    print("7 -- Quit")
    # Determine whether the user input is a valid value
    validInt = False
    while validInt == False:
        # Try statement to determine whether value is valid, and exits loop if true
        try:
            choice = int(input("Choice ==> "))
            if choice < 1 or choice > 7:
                raise ValueError("Value out of range. Select 1-7")
            else:
                validInt = True
        # catches the raised exception for handling
        except ValueError as error:
            if str(error) == "Value out of range. Select 1-7":
                print("Choice must be between 1 and 7")
            else:
                print("Invalid entry - Try again")
    print()
    
    return choice

# Function to display all films made by a director
def getDirector(directorList):
    indexList = []
    valid = False
    # Gets all movies by a specific director
    while valid == False:
        directorName = input("Enter director: ")
        if directorName in directorList:
            valid = True
            for i in range(len(directorList)):
                if directorList[i] == directorName:
                    indexList.append(i)
        # If no movies are found, print error
        else:
            print("Invalid entry - Try again")
    return indexList


# Function to get and return the highest grossing film in a specified year
def getHighestGross(yearList, revenueList):
    validYear = False

    # Asks for year to find until user enters valid year from data
    while validYear == False:
        try:
            year = int(input("Enter year: "))
            if year < 2006 or year > 2016:
                raise ValueError("Year out of range")
            else:
                validYear = True
        # catches the raised exception for handling
        except ValueError as error:
            if str(error) == "Year out of range":
                print("Year out of range, must be between 2006 and 2016")
            else:
                print("Invalid entry - Try again")

    # After year is valid, return the highest grossing film in the year
    indexList = []
    greatestRevenue = 0
    for i in range(len(yearList)):
        if yearList[i] == year:
            if float(revenueList[i]) > float(greatestRevenue):
                greatestRevenue = revenueList[i]
                greatestIndex = i
    indexList.append(greatestIndex)
    return indexList

# Function to get all films in a given year range by a specified genre
def getGenreYear(genreList, yearList):
    year1Valid = False
    year2Valid = False
    print("Enter year range to search (oldest year first)")
    # Ask user for year and determines if it's a valid year range
    while year1Valid == False or year2Valid == False:
        try:
            if year1Valid == False:
                year1 = int(input("Year1: "))
                if year1 < 2006 or year1 > 2016:
                    raise ValueError("Value out of range")
                else:
                    year1Valid = True
            # Checks if 2nd value is valid and is greater than the first
            if year2Valid == False:
                year2 = int(input("Year2: "))
                if year2 < 2006 or year2 > 2016:
                    raise ValueError("Value out of range")
                elif year2 <= year1:
                    raise ValueError("Value not greater than first")
                else:
                    year2Valid = True
        # Catch ValueError and determines which error to output to console
        except ValueError as error:
            if str(error) == "Value out of range":
                print("Year out of range, must be between 2006 and 2016")
            elif str(error) == "Value not greater than first":
                print("Second year should be after first year - try again")
                year1Valid = False
                year2Valid = False
            else:
                print("Invalid entry - Try again")

    # Asks user for genre and determines if it's a valid genre
    validGenre = False
    while validGenre == False:
        try:
            genre = input("Enter genre: ")
            if genre in genreList:
                validGenre = True
            else:
                raise ValueError
        except:
            print("Invalid entry - Try again")

    # Gets all films within year range and append corresponding indices to list
    indexList = []
    for i in range(len(yearList)):
        if yearList[i] >= year1 and yearList[i] <= year2:
            if genre in str(genreList[i]):
                indexList.append(i)

    return indexList

# Function to find a movie based on the title
def getTitle(titleList):
    indexList = []
    title = input("Enter title: ")
    print()
    # Checks each title in the data to see if the movie is found
    for i in range(len(titleList)):
        if titleList[i] == title:
            indexList.append(i)
    # If movie not found, print no films exist
    if len(indexList) == 0:
        print("No such film exists.\n")
    return indexList

# Function to find average runtime of movies greater than specified revenue
def getRevenueLength(lengthList, revenueList):
    localIndexList = []
    try:
        validLimit = False
        revenueLimit = float(input("Enter revenue limit (millions): $"))
        # Find all movies with more revenue than the limit
        for i in range(len(revenueList)):
            if float(revenueList[i]) > revenueLimit:
                validLimit = True
                localIndexList.append(i)
        # Throws error if the value is invalid
        if validLimit == False:
            raise ValueError("Revenue Limit High")
        # Finds average runtime for all movies found above the limit
        else:
            totalLength = 0.0
            for i in localIndexList:
                totalLength += int(lengthList[i])
            averageLength = totalLength / len(localIndexList)
            print("The average runtime for films with revenue higher than ${:.2f} million is {:.2f} minutes."
                  .format(revenueLimit, averageLength))
    # Catches valueError exception and prints error to console
    except ValueError as error:
        if str(error) == "Revenue Limit High":
            print("No films have revenue higher than ${:.2f} million.".format(revenueLimit))
    return


# Function to sort lists by revenue and returns a list of the ordered indexes
def sortLists(revenueList):
    # Copy the revenueList to avoid modifying the original list
    sortedRevenue = revenueList.copy()
    sortedIndexes = []
    # assign the indices for relative sorting via sorting algorithm
    for i in range(len(sortedRevenue)):
        sortedIndexes.append(i)
    # Perform sorting of revenue from new list to avoid modifying original list
    # And re-arrange the list of indexes that correspond to each revenue index
    for i in range(len(sortedRevenue)):
        for j in range(0, len(sortedRevenue)-1):
            if sortedRevenue[j] > sortedRevenue[j + 1]:
                tempIndex = sortedIndexes[j]
                sortedIndexes[j] = sortedIndexes[j + 1]
                sortedIndexes[j + 1] = tempIndex
                temp = sortedRevenue[j]
                sortedRevenue[j] = sortedRevenue[j + 1]
                sortedRevenue[j + 1] = temp
    return sortedIndexes

# Function to print the data in a formatted output to console
def printData(titleList, genreList, directorList, yearList, lengthList, revenueList, indexList):
    # Only prints if the indexList is not empty
    # Prints different output based on if there is a single value
    if len(indexList) == 1:
        print("The film that meets your criteria is:\n")
        print("TITLE".ljust(45), "GENRE".ljust(35), "DIRECTOR".ljust(24), "YEAR".ljust(8), "RUNTIME".ljust(8), "REVENUE(mil)".ljust(12))
        for i in indexList:
            print(titleList[i].ljust(45), genreList[i].ljust(35), directorList[i].ljust(24), str(yearList[i]).ljust(8),
                str(lengthList[i]).ljust(8) + ("$" + str(revenueList[i]).rjust(12)))
    # Prints different output if there are more than one value
    if len(indexList) > 1:
        print("The films that meet your criteria are:\n")
        print("TITLE".ljust(45), "GENRE".ljust(35), "DIRECTOR".ljust(24), "YEAR".ljust(8), "RUNTIME".ljust(8), "REVENUE(mil)".ljust(12))
        for i in indexList:
            print(titleList[i].ljust(45), genreList[i].ljust(35), directorList[i].ljust(24), str(yearList[i]).ljust(8),
                str(lengthList[i]).ljust(8) + ("$" + str(revenueList[i]).rjust(12)))
    return

def outputData(titleList, genreList, directorList, yearList, lengthList, revenueList, sortedIndexList):
    # Open file for writing data to
    currFile = open("movies-sorted-rev.csv", "w")
    # Append data for each sorted index to a file
    for i in sortedIndexList:
        currFile.write(str(titleList[i]) + "," + str(genreList[i]) + "," + str(directorList[i]) + "," +
                       str(yearList[i]) + "," + str(lengthList[i]) + "," + str(revenueList[i]) + "\n")
    currFile.close()
    print("Sorted data has been written to the file: movies-sorted-rev.csv.\n")

# Main function to perform calls to other functions
def main():
    # Assign data to lists from data retrieved in the getData function
    titleList, genreList, directorList, yearList, lengthList, revenueList = getData()

    # Ask the user which function they wish to perform with the retrieved data
    choice = 0
    while choice != 7:
        indexList = []
        sortedIndexList = []
        choice = pickFunction()
        if choice == 1:
            indexList = getDirector(directorList)
        elif choice == 2:
            indexList = getHighestGross(yearList, revenueList)
        elif choice == 3:
            indexList = getGenreYear(genreList, yearList)
        elif choice == 4:
            indexList = getTitle(titleList)
        elif choice == 5:
            getRevenueLength(lengthList, revenueList)
        elif choice == 6:
            sortedIndexList = sortLists(revenueList)
        elif choice == 7:
            print("Good-bye")
        # Either prints output to console or file based on user selection
        if choice == 6:
            outputData(titleList, genreList, directorList, yearList, lengthList, revenueList, sortedIndexList)
        else:
            printData(titleList, genreList, directorList, yearList, lengthList, revenueList, indexList)
            print()
    return