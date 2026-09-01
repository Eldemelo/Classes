# Design Document - Assignment/Lab5

## **1. Plan**
### **How do you plan on creating this?**

1. **Snake data structure Idea -** My idea to get snake to work is to create a singly-linked-list. This will represent each part of the length of the snake. Every time the snake moves, the current node's lifetime gets reduced by one. If a food is consumed, one iteration of lifetime gets skipped. This will allow the snake to appear as if it is moving when in reality it's just the lifetime of each node.
2. I'll begin by setting up the data structure for the snake. This will set me up for the overall logic of the snake itself
2. Next I'll handle snake location. I'll likely achieve this by saving the location of each node in the snake itself.
3. Next I'll work on the functionality to check if the snake has hit a wall, or if it has hit itself. This will complete the overall game functionality
4. Finally I'll ensure user input works as intended. This will finalize the game
---

## **2. Challenges**
### **Difficult or Time-Consuming Areas**
- **Challenge 1:** Ensuring user input is synced to the game's display properly. Avoiding desync can avoid having the user press a key and the snake not reacting as expected
- **Challenge 2:** Display - It may be difficult to get the display to show properly as expected

---

## **4. Implementation Details**
### **Outline of Functions**
- **moveSnake:** - Move the snake on the grid
  - **Input:** Head node of snake, user input selected
  - **Output:** no output
- **checkCollision** - Check if the snake has hit a wall, or itself
  - **Input:** Head of node of snake
  - **Output:** true/false
- **checkIfSnack:** - Check if the node is a snack
  - **Input:** - Head of node of snake
  - **Output:** - True/False

---

### **Outline of Data Structures**
Describe any data structures you think will be necessary for the implementation, such as:
- **Linked List** - Each node holds the lifetime of the node, and a pointer to the next node

---