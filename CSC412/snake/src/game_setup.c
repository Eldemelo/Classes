#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p, snake_t* snake_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake at the location and save its coordinates
    cells[20 * 2 + 2] = FLAG_SNAKE;
    snake_p->snakeHeadIndex = 20*2+2;
    // Initialize the pointers to null
    snake_p->next = NULL;
    snake_p->prev = NULL;

    // Place food
    place_food(cells, *width_p, *height_p);

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // Default snake direction
    snake_p->snakeDir = INPUT_RIGHT;
    // If there was no custom board passed in
    if(board_rep == NULL){
        return initialize_default_board(cells_p, width_p, height_p, snake_p);
    }
    // If there was a custom board passed in, Initialize the board by parsing it
    else{
        return decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
    }
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */

 // Ensure the board flag prefixes exist
int validPrefix(char prefix){
    if(
    prefix == 'W' ||
    prefix == 'E' ||
    prefix == 'S'){
        return 1;
    }
    return 0;
}

// Check if the character is a number
int isNumber(char* curr){
    if(curr != NULL && *curr >= '0' && *curr <= '9'){
        return 1;
    }
    return 0;
}

// Function to parse a custom board and ensure it's valid
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
    size_t* height_p, snake_t* snake_p,
    char* compressed) {
    // Define variables for parsing data
    const char delimiter[] = "|";
    char *token;
    char *saveptr;
    snake_p->next = NULL;
    snake_p->prev = NULL;

    // Tokenize the dimensions
    token = strtok_r(compressed, delimiter, &saveptr);
    if (token == NULL) {
        return INIT_ERR_BAD_CHAR;
    }

    // Parse dimensions
    {
        // Skip the first character (it just defines it as the board)
        char dimensions[strlen(token)];
        for (size_t i = 1; i < strlen(token); i++) { // remove the first character
            dimensions[i - 1] = token[i];
        }
        dimensions[strlen(token) - 1] = '\0'; // Null-terminate the string

        // Get width and height
        size_t width = 0;
        size_t height = 0;
        char *dimensionPtr;
        char *currDimension = strtok_r(dimensions, "x", &dimensionPtr);
        height = atoi(currDimension);
        currDimension = strtok_r(NULL, "x", &dimensionPtr);
        width = atoi(currDimension);

        // Save our width and height to our pointers
        *width_p = width;
        *height_p = height;

        // Allocate memory for the board
        int *cells = malloc(width * height * sizeof(int));
        if (cells == NULL) {
            return INIT_ERR_BAD_CHAR; // Memory allocation failed
        }
        *cells_p = cells;

        // Initialize all cells to plain cells
        for (size_t i = 0; i < width * height; i++) {
            cells[i] = FLAG_PLAIN_CELL;
        }
    }

    size_t row = 0;
    token = strtok_r(NULL, delimiter, &saveptr);

    // Continue parsing each row
    while (token != NULL) {
        size_t i = 0;
        size_t col = 0; // Track the column index
        while (i < strlen(token)) {
            // Make sure the current prefix is valid
            if (!validPrefix(token[i])) {
                return INIT_ERR_BAD_CHAR;
            }

            // Save the flag
            char currPrefix = token[i];
            i++;

            // Get the number
            char currNum[10]; // Buffer to store the number (max 10 digits)
            int currNumIndex = 0;
            while (i < strlen(token) && isNumber(&token[i])) {
                currNum[currNumIndex] = token[i];
                currNumIndex++;
                i++;
            }
            currNum[currNumIndex] = '\0'; // Null-terminate the number string

            int count = atoi(currNum); // Convert the number to an integer

            // Add the flag to the current row
            for (int j = 0; j < count; j++) {
                size_t index = (row * (*width_p)) + col;
                if (index >= (*width_p) * (*height_p)) {
                    return INIT_ERR_INCORRECT_DIMENSIONS; // Out of bounds
                }
                (*cells_p)[index] = (currPrefix == 'W') ? FLAG_WALL
                                : (currPrefix == 'S') ? FLAG_SNAKE
                                : FLAG_PLAIN_CELL;
                col++; // Move across each column
            }
        }
        
        // Make sure our width dimension is correct
        if(col != *width_p){
            return INIT_ERR_INCORRECT_DIMENSIONS;
        }
        row++; // Move to the next row
        token = strtok_r(NULL, delimiter, &saveptr); // Get the next token
    }
    // Make sure we have the correct number of rows
    if(row != *height_p){
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }
    int numSnakes = 0;

    // Get our snake position and get the number of snakes
    for (unsigned int i = 0; i < (*width_p * *height_p); i++) {
        if ((*cells_p)[i] == FLAG_SNAKE) {
            numSnakes++;
            snake_p->snakeHeadIndex = i;
        }
    }
    
    // Ensure we have 1 and only 1 snake
    if(numSnakes != 1){
        return INIT_ERR_WRONG_SNAKE_NUM;
    }

    // Place the first food
    place_food(*cells_p, *width_p, *height_p);

    return INIT_SUCCESS;
}
