# Reflection - Assignment 5
### What changed between your design document and final implementation
One of the key differences between my initial design document and the final implementation was the strategy I used to manage the data for the snake. Originally, I intended to maintain a length variable and decrement the length of each node with every move. Nodes reaching a value of 0 would be removed, effectively moving the tail without needing to update pointers or every node's coordinates. This approach aimed to simplify memory operations. However, the structure of the template code made this approach impractical. Instead, I ended up iterating through the linked list of the snake, updating each node's location in sequence, and modifying the board to reflect the new state. If the snake grew, an additional node was appended at the end.

### What worked? What did not work?
During development, I encountered challenges with maintaining the snake's behavior when its length exceeded 1. Initially, the code created a new snake node, but it would remain static, acting like a "ghost" node rather than moving properly. Experimental adjustments to variables led to a different situation where the snake grew infinitely from the start of the game which was not the intended functionality. After extensive debugging, I discovered that functions returning 1 or 0 could not be directly interpreted as booleans. Instead of using if(function()) {}, I had to explicitly check conditions with if(function() == 0) {}. While this issue took considerable time to resolve, the core functionalities—such as movement, scoring, and food placement—worked correctly on the first attempt, with only minor adjustments needed to ensure the right order of operations.

### What issues did you face during research, and what topics did you have to explore?
While researching, I faced some difficulty fully grasping how UTF-8 encoding worked and how to properly parse it. Although I understood the concept of it in binary representation, my familiarity with hexadecimal binary representation was somewhat rusty. As a result, I needed to spend extra time reviewing and understanding how data is encoded in UTF-8 and how to effectively handle it programmatically.

### How many hours did this assignment take to complete?
This assignment required approximately 18 to 26 hours to complete.

### Unit Test: A detailed description including purpose, input data, expected output, and explanation of how the test confirms correctness.
- <b>Unit Test 1:</b>

- <b>Purpose of the test:</b> To verify that the snake cannot reverse direction on itself when its length is greater than 1 and will continue moving in its current direction.

- <b>Input data:</b> Seed for randomness and specific user inputs.

- <b>Expected output:</b> The snake achieves a score of 1, the game ends with game_over set to true, and the board state aligns with the expected configuration.

- <b>Explanation of correctness:</b> This test ensures that if the user provides inputs attempting to reverse the snake's direction, it will not double back on itself when its length exceeds 1. The game ends appropriately when the snake collides with a wall, confirming that movement logic and collision detection are functioning as intended.