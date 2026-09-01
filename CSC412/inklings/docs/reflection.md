# Reflection Document - Assignment 4

### What changed between your design document and the final implementation
There were quite a few changes I made between my design document and my final implementation. At first, when writing my design document, I wasn't sure how the code base was set up. I also had very little experience with multi-threaded programs. In my design document, I expected to need to fix a lot of the code already given. However, there was actually not a whole lot that had to be changed. Rather, it was more of a template code that I had to implement my own solution to meet the requirements of the handout.

### What worked? What did not work?
At first, I attempted to run 4 threads simultaneously and print out each grid as each ran. This approach proved poor initially, as I wasn't sure exactly what was going wrong with my code. I shifted my approach towards utilizing print statements for debugging and using the GDB debugger to determine where my code was having problems, such as crashes. After creating debugging statements, I was able to trace somewhat what my threads were doing.

I decided instead of attempting multiple threads to only work in red and only with a single thread. At first, I was able to get the program mostly working and spent a good number of hours trying to debug why my program would continue to run even after the inkling hit a corner. After taking a break and coming back, I took a look into `main` and realized I had changed the thread count but not the maximum concurrent threads. So, I changed that to match the thread count, and the program began to behave as expected.

After that, I removed all my debug statements and re-enabled the grid printing. Here I ran into another problem: the grid was not printing out each move that each inkling made. Upon investigation, I quickly realized I did not sleep the inkling after it made a move. Once I made that fix, the code worked flawlessly.

### During your research did you run into any issues, what (if any) topics did you have to research?
I had to take some time to research how to check if a directory exists in C++. I wasn't sure how to check other than using a try/catch, which isn't the ideal approach, so I took some time to research how to determine if a directory already exists. 

I also spent a bit of time looking at example code provided by the professor and examples online of multi-threaded synchronized applications. After reviewing these examples, I was able to gain a better understanding of how multi-threaded programs work and how to implement this knowledge into my own code.

### How many hours did this assignment take to complete? (i.e., 10 hours, 20 hours, etc.)
This assignment took roughly 30-40 hours to complete, including reading the handout, reviewing the code base, testing, debugging, development, and fixes.
