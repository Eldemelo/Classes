# Improvements Document - Assignment 4

## **Improvement One**: Improved Logging System

### **Proposed Change Summary**
The current logging system is challenging to read and interpret due to misalignment caused by variations in text and character lengths. This inconsistency makes debugging more difficult and slows down the process of identifying and resolving issues. By reformatting the log entries, they will become easier to read and more efficient for debugging.

### **Describe the Problem**
The existing logging implementation appends data directly to the log files without applying any formatting. This results in several issues:
- **Alignment Problems:** Entries with differing lengths for certain fields (e.g., directions like "North" vs. "West") or other values like inkling colors create inconsistent spacing. This misalignment makes it difficult to visually scan and analyze the logs.
- **Reduced Debugging Efficiency:** Developers must spend additional time understanding poorly formatted logs, which can delay the debugging process and lead to oversights.

### **Describe the Solution**
Introducing a structured format for log entries would significantly improve readability and usability. By ensuring consistency across all log lines, developers can quickly analyze the information.

#### Steps to Achieve This Solution:
1. **Format Log Entries:** Construct each log entry as a single string and format it before writing it to the file.
   - In C++, functions like `std::setw()` can be used to control field widths and ensure consistent spacing.
2. **Append Formatted Strings:** Once formatted, append the log string to the file rather than raw unformatted log outputs.

#### Benefits of This Solution:
- Log files become formatted consistently
- Faster and debugging due to improved readability of log entries.

---

## **Improvement Two**: Stabilizing Keyboard Interactions

### **Proposed Change Summary**
The current keyboard interaction system is unreliable and causes the program to crash. This improvement focuses on detaching the key listener from the main event loop to ensure asynchronous functionality for the keystrokes:
- `esc`: Terminates the program.
- `r`: Partially refills the red ink tank.
- `g`: Partially refills the green ink tank.
- `b`: Partially refills the blue ink tank.

### **Describe the Problem**
The instability of the key listener is a major issue. After testing the following was determined:
- After back-end initialization, any keyboard interaction consistently causes the program to crash.
- During early runtime, keys may work temporarily if pressed quickly, but the program eventually crashes, suggesting issues between the event loop and the key listener.

### **Describe the Solution**
The solution involves detaching the key listener from the program's main event loop, allowing it to run independently. This will prevent the eventLoop from crashing awaiting a keystroke input

#### Steps to Achieve This Solution:
1. **Detach the Key Listener:**
   - Detach the listener thread from the main event loop to allow both components to execute concurrently.
2. **Wrap Listener in a Continuous Loop:**
   - Implement a loop within the key listener thread to monitor for inputs continuously.

---

These improvements are designed to address areas of the program that can be improved, enhancing its stability, efficiency, and overall usability.
