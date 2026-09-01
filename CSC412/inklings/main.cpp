//
//  main.cpp
//  inklings
//
//  Authors: Jean-Yves Hervé, Shaun Wallace, and Luis Hernandez
//

 /*-------------------------------------------------------------------------+
 |	A graphic front end for a grid+state simulation.						|
 |																			|
 |	This application simply creates a a colored grid and displays           |
 |  some state information in the terminal using ASCII art.			        |
 |	Only mess with this after everything else works and making a backup		|
 |	copy of your project.                                                   |
 |																			|
 |	Current Keyboard Events                                     			|
 |		- 'ESC' --> exit the application									|
 |		- 'r' --> add red ink												|
 |		- 'g' --> add green ink												|
 |		- 'b' --> add blue ink												|
 +-------------------------------------------------------------------------*/

#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <filesystem>
#include <sys/stat.h>

#include "ascii_art.h"

//==================================================================================
//	Function prototypes
//==================================================================================
void displayGridPane(void);
void displayStatePane(void);
void initializeApplication(void);
void threadFunction(InklingInfo* inkling);
void getNewDirection(InklingInfo* inkling);
bool checkIfInCorner(InklingInfo* inkling);
void redColorThreadFunc();
void greenColorThreadFunc();
void blueColorThreadFunc();
bool checkEnoughInk(InklingInfo* inkling, int moveAmount);

//==================================================================================
//	Application-level global variables
//==================================================================================

//	The state grid and its dimensions
int** grid;
int NUM_ROWS, NUM_COLS;

//	the number of live threads (that haven't terminated yet)
int MAX_NUM_TRAVELER_THREADS;
int numLiveThreads = 0;

//vector to store each struct
std::vector<InklingInfo> info;
bool DRAW_COLORED_TRAVELER_HEADS = true;

//	the ink levels
int MAX_LEVEL = 50;
int MAX_ADD_INK = 10;
int REFILL_INK = 10;
int redLevel = 20, greenLevel = 10, blueLevel = 40;

// create locks for color levels
std::mutex redLock;
std::mutex blueLock;
std::mutex greenLock;
std::mutex blueCellLock;
std::mutex redCellLock;
std::mutex greenCellLock;

// ink producer sleep time (in microseconds)
// [min sleep time is arbitrary]
const int MIN_SLEEP_TIME = 30000; // 30000
int producerSleepTime = 100000; // 100000

// inkling sleep time (in microseconds)
int inklingSleepTime = 1000000; // 1000000

// Random engine
std::random_device myRandDev;
std::default_random_engine myEngine(myRandDev());

//==================================================================================
//	These are the functions that tie the simulation with the rendering.
//	Some parts are "don't touch."  Other parts need your help to ensure
//	that access to critical data and the ASCII art are properly synchronized
//==================================================================================
std::mutex gridLock;
void displayGridPane(void) {
	//---------------------------------------------------------
	//	This is the call that writes ASCII art to render the grid.
	//
	//	Should we synchronize this call?
	//---------------------------------------------------------
	// std::lock_guard<std::mutex> lock(gridLock);
    drawGridAndInklingsASCII(grid, NUM_ROWS, NUM_COLS, info);
}

void displayStatePane(void) {
	//---------------------------------------------------------
	//	This is the call that updates state information
	//
	//	Should we synchronize this call?
	//---------------------------------------------------------
	// std::lock_guard<std::mutex> lock(gridLock);
	drawState(numLiveThreads, redLevel, greenLevel, blueLevel);
}

//------------------------------------------------------------------------
//	These are the functions that would be called by a inkling thread in
//	order to acquire red/green/blue ink to trace its trail.
//	You *must* synchronize access to the ink levels (C++ lock and unlock)
//------------------------------------------------------------------------
// You probably want to edit these...
bool acquireRedInk(int theRed) {
	std::lock_guard<std::mutex> lock(redLock);
    if (redLevel >= theRed) {
        redLevel -= theRed;
        return true;
    }
    return false;
}

bool acquireGreenInk(int theGreen) {
	std::lock_guard<std::mutex> lock(greenLock);
	if (greenLevel >= theGreen)
	{
		greenLevel -= theGreen;
		return true;
	}
	return false;
}

bool acquireBlueInk(int theBlue) {
	std::lock_guard<std::mutex> lock(blueLock);
	if (blueLevel >= theBlue)
	{
		blueLevel -= theBlue;
		return true;
	}
	return false;
}


//------------------------------------------------------------------------
//	These are the functions that would be called by a producer thread in
//	order to refill the red/green/blue ink tanks.
//	You *must* synchronize access to the ink levels (C++ lock and unlock)
//------------------------------------------------------------------------
// You probably want to edit these...
bool refillRedInk(int theRed) {
	std::lock_guard<std::mutex> lock(redLock);
	if (redLevel + theRed <= MAX_LEVEL)
	{
		redLevel += theRed;
		return true;
	}
	return false;
}

bool refillGreenInk(int theGreen) {
	std::lock_guard<std::mutex> lock(greenLock);
	if (greenLevel + theGreen <= MAX_LEVEL)
	{
		greenLevel += theGreen;
		return true;
	}
	return false;
}

bool refillBlueInk(int theBlue) {
	std::lock_guard<std::mutex> lock(blueLock);
	if (blueLevel + theBlue <= MAX_LEVEL)
	{
		blueLevel += theBlue;
		return true;
	}
	return false;
}

//------------------------------------------------------------------------
//	You shouldn't have to touch this one.  Definitely if you do not
//	add the "producer" threads, and probably not even if you do.
//------------------------------------------------------------------------
void speedupProducers(void) {
	// decrease sleep time by 20%, but don't get too small
	int newSleepTime = (8 * producerSleepTime) / 10;
	
	if (newSleepTime > MIN_SLEEP_TIME) {
		producerSleepTime = newSleepTime;
	}
}

void slowdownProducers(void) {
	// increase sleep time by 20%
	producerSleepTime = (12 * producerSleepTime) / 10;
}

// Function to create the logFolder
void createLogsDir(){
	std::string logDir = "logFolder";
	(std::filesystem::create_directory(logDir));
}

// Function for logging to get the current time
std::string getTime(){
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	// combine everything for return
	char buffer[20];
	std::sprintf(buffer, "%02d:%02d:%02d.%03d",
                 std::localtime(&in_time_t)->tm_hour,
                 std::localtime(&in_time_t)->tm_min,
                 std::localtime(&in_time_t)->tm_sec,
                 static_cast<int>(milliseconds.count()));
	return std::string(buffer);
}

// MARK: Main
//-------------------------------------------------------------------------------------
//	You need to change the TODOS in the main function to pass the the autograder tests
//-------------------------------------------------------------------------------------
int main(int argc, char** argv) {
    // a try/catch block for debugging to catch weird errors in your code
    try {
        // check that arguments are valid, must be a 20x20 or greater and at least 8 threads/inklings
        if (argc == 4) {
            if (std::stoi(argv[1]) >= 20 && std::stoi(argv[2]) >= 20 && std::stoi(argv[3]) >= 8) {
                NUM_ROWS = std::stoi(argv[1]);
                NUM_COLS = std::stoi(argv[2]);
                MAX_NUM_TRAVELER_THREADS = std::stoi(argv[3]);
                numLiveThreads = std::stoi(argv[3]);
            }
        } else {
          std::cout << "No arguments provided, running with 8x8 grid and 4 threads.\n\tThis message will dissapear in 2 seconds... \n";
            sleep(2); // so the user can read the message in std::cout one line up
            clearTerminal();
            // some small defaults, will these run?
            NUM_ROWS = 8;
            NUM_COLS = 8;
            MAX_NUM_TRAVELER_THREADS = 4;
            numLiveThreads = 4;
        }

		// Set up our logs directory and wait 50ms for it to complete
		createLogsDir();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		// Initialize our applications's front and backend
        initializeFrontEnd(argc, argv, displayGridPane, displayStatePane);
        initializeApplication();


        // producer threads that check the levels of each ink
		std::thread redProducerThread(redColorThreadFunc);
		redProducerThread.detach();
		std::thread greenProducerThread(greenColorThreadFunc);
		greenProducerThread.detach();
		std::thread blueProducerThread(blueColorThreadFunc);
		blueProducerThread.detach();
        
        // create threads for the inklings
		for (int i = 0; i < MAX_NUM_TRAVELER_THREADS; i++){
			std::thread(threadFunction, &info[i]).detach();
		}
        
        // now we enter the main event loop of the program
		myEventLoop(0);

		// ensure main does not return immediately, killing detached threads
		while(numLiveThreads > 0){
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		cleanupAndQuit("Main thread exiting, joining all threads...\n");
        
    } catch (const std::exception& e) {
        std::cerr << "ERROR :: Oh snap! unhandled exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR :: Red handed! unknown exception caught" << std::endl;
    }

	return 0;
}


//==================================================================================
//
//	TODO this is a part that you have to edit and add to.
//
//==================================================================================

void cleanupAndQuit(const std::string& msg) {
  std::cout << "Somebody called quits, goodbye sweet digital world, this was their message: \n" << msg;
	// should we join all the threads before you free the grid and other allocated data structures.  
    // you may run into seg-fault and other ugly termination issues otherwise.
	
	// also, if you crash there, you know something is wrong in your code.
	for (int i=0; i< NUM_ROWS; i++)
		delete []grid[i];
	delete []grid;

	// clear the inkling list
	for(int i = 0; i < info.size(); i++){
		info.pop_back();
	}
    exit(0);
}

// Function to check if there already exists and inkling at a location
bool checkIfUnique(InklingInfo* inkling) {
	for(auto i = 0; i < info.size(); i++) {
		if (info[i].row == inkling->row && info[i].col == inkling->col) {
			return false;
		}
	}
	return true;
}

// Function to ensure coordinates are not corners
bool isValidInitializationPoint(InklingInfo* inkling) {
	// Check if we're in a corner
	if(!checkIfInCorner(inkling)) {
		// Check if there is an inkling at the same location
		if(checkIfUnique(inkling)){
			return true;
		}
	}
	return false;
}


// MARK: logfile
// Function to create a log file for each inkling
void createInklingLogFile(InklingInfo* inkling){
	std::string logDir = "logFolder";
	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
	std::ofstream outFile(fileName);
	outFile << getTime() << ",inkling" << inkling->inklingNum << "," << 
	(inkling->type == RED_TRAV ? "red" : inkling->type == BLUE_TRAV ? "blue" : "green") <<  ",row" << inkling->row << ",col" << inkling->col << std::endl;
	// std::cout << "wrote to file " << inkling->inklingNum << std::endl;
	outFile.close();
	chmod(fileName.c_str(), 0755);
}

// void createInklingLogFile(InklingInfo* inkling){
// 	std::string logDir = "logFolder";
// 	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
// 	std::ofstream outFile(fileName);
// 	outFile << std::left
//                 << std::setw(15) << getTime()            // 15 spaces for timestamp
//                 << std::setw(10) << "inkling" + std::to_string(inkling->inklingNum) // 10 spaces for inkling ID
//                 << std::setw(10) << (inkling->type == RED_TRAV ? "red" : inkling->type == BLUE_TRAV ? "blue" : "green") // 10 spaces for type
//                 << std::setw(6)  << "row" + std::to_string(inkling->row) // 6 spaces for row
//                 << std::setw(6)  << "col" + std::to_string(inkling->col) // 6 spaces for column
//                 << std::endl;
// 	outFile.close();

// 	chmod(fileName.c_str(), 0755);
// }

// Function to initialize the backend of our application
void initializeApplication(void) {
	// log Directory
	std::string logDir = "logFolder";

	//	Allocate the grid
	grid = new int*[NUM_ROWS];
	for (int i=0; i<NUM_ROWS; i++)
		grid[i] = new int[NUM_COLS];	
	
    // TODO random number generation initialization for color, position and direction of inklings
	std::uniform_int_distribution<int> inklingColor(0, 2);
	std::uniform_int_distribution<int> inklingPosition(0, NUM_ROWS * NUM_COLS - 1);
	std::uniform_int_distribution<int> inklingDirection(0, 3);
	int numberOfInklings = 1;
	
	// Generate an empty grid
	for (int i=0; i<NUM_ROWS; i++) {
		for (int j=0; j<NUM_COLS; j++) {
			// the intialization you should use
            grid[i][j] = 0;
		}
	}

	int position;
	// Generate the inklings
	while (numberOfInklings <= numLiveThreads){
		position = inklingPosition(myEngine);
		InklingInfo inked = 
		{
			(InklingType)inklingColor(myEngine), // type
			// (InklingType)0,
			position / NUM_COLS, position % NUM_COLS, // starting col
			(TravelDirection)inklingDirection(myEngine), //starting row
			true, // is live
			0, // number of moves
			numberOfInklings // inkling number
		};
		// Ensure the inkling is not in a corner and that there is no inkling at the same location before appending
		if (isValidInitializationPoint(&inked)){
			// Open the file
			info.push_back(inked);
			numberOfInklings++;
			createInklingLogFile(&inked);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
}

// Helper function to check if the inkling is facing a wall
bool facingEdge(InklingInfo* inkling){
	if(inkling->dir == NORTH && inkling->row <= 0){
		return true;
	}
	if(inkling->dir == WEST && inkling->col <= 0){
		return true;
	}
	if(inkling->dir == SOUTH && inkling->row >= NUM_ROWS - 1){
		return true;
	}
	if(inkling->dir == EAST && inkling->col >= NUM_COLS - 1){
		return true;
	}
	return false;
}

// Function to get a new amount of moves for the inkling
int getMoveAmount(InklingInfo* inkling){
	int moveAmount = 0;
 moveAmount;
	if(inkling->dir == NORTH){
		if(inkling->row <= 0){
			return 0;
		}
		std::uniform_int_distribution<int> inklingMovements(1, inkling->row);
		moveAmount = inklingMovements(myEngine);
	}
	else if(inkling->dir == WEST){
		if(inkling->col <= 0){
			return 0;
		}
		std::uniform_int_distribution<int> inklingMovements(1, inkling->col);
		moveAmount = inklingMovements(myEngine);
	}
	else if(inkling->dir == SOUTH){
		if(inkling->row >= NUM_ROWS - 1){
			return 0;
		}
		std::uniform_int_distribution<int> inklingMovements(1, NUM_ROWS - inkling->row - 1);
		moveAmount = inklingMovements(myEngine);
	}
	else{
		if(inkling->col >= NUM_COLS - 1){
			return 0;
		}
		std::uniform_int_distribution<int> inklingMovements(1, NUM_COLS - inkling->col - 1);
		moveAmount = inklingMovements(myEngine);
	}
	return moveAmount;
}

// Function to append to the inkling log
void appendInklingLog(InklingInfo* inkling){
	std::string logDir = "logFolder";
	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
	std::ofstream outFile(fileName, std::ios::app);
	outFile << getTime() << ",inkling" << inkling->inklingNum << "," << 
	(inkling->dir == 0 ? "north" : inkling->dir == 1 ? "west" : inkling->dir == 2 ? "south" : "east") << ",row" << inkling->row << ",col" << inkling->col << std::endl;
	outFile.close();
}

// void appendInklingLog(InklingInfo* inkling){
// 	std::string logDir = "logFolder";
// 	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
// 	std::ofstream outFile(fileName, std::ios::app);
// 	outFile << std::left
//                 << std::setw(15) << getTime()  // 15 spaces for timestamp
//                 << std::setw(10) << ("inkling" + std::to_string(inkling->inklingNum))  // 10 spaces for inkling ID
//                 << std::setw(10) << (inkling->dir == 0 ? "north" 
//                                     : inkling->dir == 1 ? "west" 
//                                     : inkling->dir == 2 ? "south" 
//                                     : "east")  // 10 spaces for direction
//                 << std::setw(6)  << ("row" + std::to_string(inkling->row))  // 6 spaces for row
//                 << std::setw(6)  << ("col" + std::to_string(inkling->col))  // 6 spaces for column
//                 << std::endl;
// 	outFile.close();
// }

// Function to append to the inkling log when an inkling is killed
void appendThreadKillLog(InklingInfo* inkling){
	std::string logDir = "logFolder";
	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
	std::ofstream outFile(fileName, std::ios::app);
	outFile << getTime() << ",inkling" << inkling->inklingNum << ",terminated";
	outFile.close();
}

// void appendThreadKillLog(InklingInfo* inkling){
// 	std::string logDir = "logFolder";
// 	std::string fileName = logDir + "/inkling" + std::to_string(inkling->inklingNum) + ".txt";
// 	std::ofstream outFile(fileName, std::ios::app);
// 	outFile << std::left
//                 << std::setw(15) << getTime()  // 15 spaces for timestamp
//                 << std::setw(10) << ("inkling" + std::to_string(inkling->inklingNum))  // 10 spaces for inkling ID
//                 << std::setw(12) << "terminated"  // 12 spaces for status
//                 << std::endl;
// 	outFile.close();
// }

// MARK: ThreadFunction
// TODO help me please, I am a vagabond
void threadFunction(InklingInfo* inkling) {
	// Get a move amount based on the direction
	while(inkling->isLive){
		int moveAmount = getMoveAmount(inkling);
		while (inkling->type == RED_TRAV && !acquireRedInk(moveAmount)) {
			std::this_thread::sleep_for(std::chrono::microseconds(inklingSleepTime));
		}
		while(inkling->type == GREEN_TRAV && !acquireGreenInk(moveAmount)){
			std::this_thread::sleep_for(std::chrono::microseconds(inklingSleepTime));
		}
		while(inkling->type == BLUE_TRAV && !acquireBlueInk(moveAmount)){
			std::this_thread::sleep_for(std::chrono::microseconds(inklingSleepTime));
		}
		
		// Move the inkling
		if (inkling->dir == 0) {
			inkling->row -= moveAmount;
		} 
		else if (inkling->dir == 1) {
			inkling->col -= moveAmount;
		} 
		else if (inkling->dir == 2) {
			inkling->row += moveAmount;
	 	} 
		else {
			inkling->col += moveAmount;
		}

		// Check if the inkling is in the corner and kill the inkling if it is
		if(checkIfInCorner(inkling)){
			inkling->isLive = false;
			appendThreadKillLog(inkling);
			break;
		}
		appendInklingLog(inkling);
		// Get a new direction for the inkling
		getNewDirection(inkling);
		std::this_thread::sleep_for(std::chrono::microseconds(inklingSleepTime));
	}
	numLiveThreads--;
}


// TODO help me please, I have no direction
void getNewDirection(InklingInfo* inkling) {
	std::uniform_int_distribution<int> inklingDirection(0, 1);

	// Generate a new direction for the inkling that is adjacent to our current direction
	if (inklingDirection(myEngine) == 0){
		inkling->dir = (TravelDirection)((inkling->dir + NUM_TRAVEL_DIRECTIONS - 1) % NUM_TRAVEL_DIRECTIONS);
	}
	else{
		inkling->dir = (TravelDirection)((inkling->dir + 1) % NUM_TRAVEL_DIRECTIONS);
	}
}

// TODO help me please, I am blank and need some code
bool checkIfInCorner(InklingInfo* inkling) {
	if (inkling->row == 0 && inkling->col == 0 || 
		inkling->row == 0 &&inkling->col == NUM_COLS - 1 ||
		inkling->row == NUM_ROWS - 1 && inkling->col == 0 ||
		inkling->row == NUM_ROWS - 1 && inkling->col == NUM_COLS - 1){
			return true;
		}
	return false;
}

// TODO check if you have enough ink depending on what kind of inkling you are, maybe some locks/unlocks
bool checkEnoughInk(InklingInfo* inkling, int moveAmount) {
	if(inkling->type == 0){
		std::lock_guard<std::mutex> lockRed(redLock);
		if(redLevel >= moveAmount){
			return true;
		}
	}
	else if (inkling->type == 1){
		std::lock_guard<std::mutex> lockGreen(greenLock);
		if(greenLevel >= moveAmount){
			return true;
		}
	}
	else{
		std::lock_guard<std::mutex> lockBlue(blueLock);
		if(blueLevel >= moveAmount){
			return true;
		}
	}
	return false;
}

// TODO thread function for a red ink producer
void redColorThreadFunc() {
	while(numLiveThreads > 0){
		// std::cout << "[DEBUG] Trying to acquire redLock in redColorThreadFunc" << std::endl;
		if(refillRedInk(REFILL_INK)){
			// std::cout << "Red ink refilled" << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(producerSleepTime));
		}
	}
}

// TODO thread function for a green ink producer
void greenColorThreadFunc() {
	while(numLiveThreads > 0){
		if(refillGreenInk(REFILL_INK)){
			// std::cout << "Green ink refilled" << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(producerSleepTime));
		}
	}
}

// TODO thread function for a blue ink producer
void blueColorThreadFunc() {
	while(numLiveThreads > 0){
		if(refillBlueInk(REFILL_INK)){
			// std::cout << "Blue ink refilled" << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(producerSleepTime));
		}
	}
}
