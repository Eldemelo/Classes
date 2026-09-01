#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "linked_list.h"
#include "mbstrings.h"

/*
This section of code is dedicated to handling the snake_t struct for our snake
Here we will be updating our snake's location by moving each node's coordinate and adding a node if we've eaten
*/
void moveSnake(int* cells, size_t width, size_t height, snake_t* snake_p, int grows, int growing){
    // Save our last node
    snake_t* lastNode = snake_p;
    while(lastNode->next){
        lastNode = lastNode->next;
    }
    // variable to save each node's location
    int prevCoord = snake_p->snakeHeadIndex;

    // handle the head
    snake_t* head = snake_p;
    switch(head->snakeDir){
        case(INPUT_UP):
            head->snakeHeadIndex -= width;
            break;
        case(INPUT_DOWN):
            head->snakeHeadIndex += width;
            break;
        case(INPUT_LEFT):
            head->snakeHeadIndex -= 1;
            break;
        default:
            head->snakeHeadIndex += 1;
            break;
    }
    
    int currCoord = 0;
    // Node to traverse snake and update coordinates
    snake_t* temp = snake_p->next;
    while(temp){
        // we move our node to the next position
        currCoord = temp->snakeHeadIndex;
        temp->snakeHeadIndex = prevCoord;
        prevCoord = currCoord;
        temp = temp->next;
    }
    
    // update our board to remove the old tail if we have not ate
    // We grow so we will not remove the tail from the board and create a new node
    // Only grow if growing is enabled
    if(growing == 1 && grows == 1){
        snake_t* newTail = malloc(sizeof(snake_t));
        lastNode->next = newTail;
        newTail->snakeHeadIndex = prevCoord;
        newTail->prev = lastNode;
        newTail->next = NULL;
        cells[newTail->snakeHeadIndex] = FLAG_SNAKE;
    }
    else{
        cells[prevCoord] = FLAG_PLAIN_CELL;
    }
    cells[head->snakeHeadIndex] = FLAG_SNAKE;
}

// Return 1 if we hit a wall
int hitWall(int* cells, size_t width, size_t height, snake_t* snake_p){
    // determine move direction
    switch(snake_p->snakeDir){
        case(INPUT_UP):
            if(cells[snake_p->snakeHeadIndex - width] & FLAG_WALL){
                return 1;
            }
            break;
        case(INPUT_DOWN):
            if(cells[snake_p->snakeHeadIndex + width] & FLAG_WALL){
                return 1;
            }
                break;
        case(INPUT_LEFT):
            if(cells[snake_p->snakeHeadIndex - 1] & FLAG_WALL){
                return 1;
            }
            break;
        default:
            if(cells[snake_p->snakeHeadIndex + 1] & FLAG_WALL){
                return 1;
            }
            break;
    }
    return 0;
}

// return 1 if we hit ourselves
int hitSelf(int* cells, size_t width, size_t height, snake_t* snake_p){
    snake_t* curr = snake_p;
    while(curr->next){
        curr = curr->next;
    }

    int newIndex;
    
    // determine move direction
    switch(snake_p->snakeDir){
        case(INPUT_UP):
            newIndex = snake_p->snakeHeadIndex - width;
            break;
        case(INPUT_DOWN):
            newIndex = snake_p->snakeHeadIndex + width;
            break;
        case(INPUT_LEFT):
            newIndex = snake_p->snakeHeadIndex - 1;
            break;
        default:
        newIndex = snake_p->snakeHeadIndex + 1;
            break;
    }
    // Check each node aside from the tail and see if the coordinates match
    if(curr->prev){
        curr = curr->prev;
    }
    while(curr->prev){
        if(curr->snakeHeadIndex == newIndex){
            return 1;
        }
        curr = curr->prev;
    }
    return 0;
}

// check if we eat the food, and if so place a new one
int eatFood(int* cells, size_t width, size_t height, snake_t* snake_p){
    // determine move direction
    switch(snake_p->snakeDir){
        case(INPUT_UP):
            if(cells[snake_p->snakeHeadIndex - width] & FLAG_FOOD){
                place_food(cells, width, height);
                cells[snake_p->snakeHeadIndex - width] = FLAG_PLAIN_CELL;
                g_score++;
                return 1;
            }
            break;
        case(INPUT_DOWN):
            if(cells[snake_p->snakeHeadIndex + width] & FLAG_FOOD){
                place_food(cells, width, height);
                cells[snake_p->snakeHeadIndex + width] = FLAG_PLAIN_CELL;
                g_score++;
                return 1;
            }
                break;
        case(INPUT_LEFT):
            if(cells[snake_p->snakeHeadIndex - 1] & FLAG_FOOD){
                place_food(cells, width, height);
                cells[snake_p->snakeHeadIndex - 1] = FLAG_PLAIN_CELL;
                g_score++;
                return 1;
            }
            break;
        default:
            if(cells[snake_p->snakeHeadIndex + 1] & FLAG_FOOD){
                place_food(cells, width, height);
                cells[snake_p->snakeHeadIndex + 1] = FLAG_PLAIN_CELL;
                g_score++;
                return 1;
            }
            break;
    }
    return 0;
}

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board

    // If game is over we do nothing
    if(g_game_over){
        return;
    }

    // If the input has changed we update our direction for the snake
    if(input != INPUT_NONE){
        int doubling = 0;
        // Make sure we aren't doubling back if the length isn't 1
        if(snake_p->next){
            if (((input == INPUT_UP && snake_p->snakeDir == INPUT_DOWN) ||
                (input == INPUT_DOWN && snake_p->snakeDir == INPUT_UP) ||
                (input == INPUT_LEFT && snake_p->snakeDir == INPUT_RIGHT) ||
                (input == INPUT_RIGHT && snake_p->snakeDir == INPUT_LEFT))){
                    doubling = 1;
            }
        }
        if(doubling == 0){
            snake_p->snakeDir = input;
        }
    }

    // Check if we're going to eat
    int ate = eatFood(cells, width, height, snake_p);

    // First check if we're going to hit a wall, or ourselves
    if(hitWall(cells, width, height, snake_p) == 1 || hitSelf(cells, width, height, snake_p) == 1){
        g_game_over = 1;
        return;
    }

    // Move our snake
    moveSnake(cells, width, height, snake_p, ate, growing);
}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    char name_buffer[1000];
    ssize_t bytes_read;
    int validName = 0;
    while (validName == 0) {
        // Prompt the user for their name
        write(1, "Name > ", 7);

        // Read input from the user
        bytes_read = read(0, name_buffer, sizeof(name_buffer) - 1);

        if (bytes_read <= 1) {
            // Input is too short (only newline or empty)
            write(1, "Name Invalid: must be longer than 0 characters.\n", 48);
        } else {
            // Null-terminate the input
            if (name_buffer[bytes_read - 1] == '\n') {
                name_buffer[bytes_read - 1] = '\0'; // Remove trailing newline
            } else {
                name_buffer[bytes_read] = '\0'; // Ensure null-termination
            }

            // Validate the UTF-8 string using mbslen
            if (mbslen(name_buffer) == (size_t)-1) {
                write(1, "Name Invalid: must be a valid UTF-8 string.\n", 44);
            } else {
                validName = 1; // Name is valid
            }
        }
    }

    // Copy the valid name into the provided buffer
    strcpy(write_into, name_buffer);
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
    // Free cells if we've allocated
    if(cells){
        free(cells);
    }
    // If the snake doesn't exist return
    if(!snake_p){
        return;
    }
    // Free the memory for the snake
    snake_t* current = snake_p;
    while (current) {
        snake_t* next = current->next;
        // If we're at the head, memory is allocated on the stack so we skip
        if(current == snake_p){
            current = next;
            continue;
        }
        free(current);
        current = next;
    }
}