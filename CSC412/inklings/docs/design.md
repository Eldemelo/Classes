# Design Document - Assignment 4
## Planning First Approach - Ethan DeMelo
### In what order will the assignment be completed?
I plan on attempting to complete the assignment in this order:
<ol>
<li><b>Running and understanding the codebase in place</b> - I want to have a good understanding of what is working, what is not working, what needs to be implemented, and what needs to be improved
<li><b>Implement base fixes</b> - After getting a strong understanding of what needs to be fixed, I will take the time to fix anything that doesn't work as intended. This will hopefully get me to a point where I have a strong codebase that changed and additional functionality can be made. The main focus for this step will be gettin the animation to run properly
<li><b>Creating inklings as multiple threads</b> - I will need to implement threads that move randomly on a grid in the terminal. Some of the primary constraints required:
<ul>
<li>Have an initial unique starting point and be either red, blue, or green
<li>Generate a random amount of "valid" spaces to travel
<li>Record their position of travel on the grid
<li>Have access to at least 1 ink resource before being able to move and stop moving if there are none available
<li>If the ink has run out, refill the tank
<li>Terminate the inkling thread if they reach a corner
</ul>

<li><b>Create log files for Inklings</b> - Each inkling will have its own log file that will track its actions.
format:
hour:minute:second.millisecond
21:20:31.673

every line must also include an action:
21:20:30.562,inkling3,green,row3,col2
21:20:30.824,inkling3,west,row1,col1
21:20:33.901,inkling3,terminated

<li><b>Combine log files</b> - Combine all log files and sort them by time with the name actions.txt. NOTE: make clean will remove the logs executable

<li><b>Write program improvements</b> - Propose, and implement 2 changes to the codebase to improve it

### Describe areas you believe will be difficult or time consuming
I believe the most difficult part of this assignment will be implementing multiple threads for each inkling. I also believe it may be difficult to implement the log files

### Describe what needs to be researched in order to solve these problems
In order to solve these problems, I will need to research some implementations of multi-threading in order to get a better fundamental understanding of how it works and how to properly implement it. I will also need to research how to get the current date/time, and format it.

### Provide a rough outline of the functions, data structures, and/or comments describing what you think you will need.

main:
Handle arguments, generate grid, initialize inklings

