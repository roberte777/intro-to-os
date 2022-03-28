Justin Sprouse
Ethan Wilkes

This is the readme file for homework 1.

The two code files are: "Threads.cpp" and "Processes.cpp".
If you want to run these files, simply compile them in whatever compiler is on your system and execute the executables.

The test text file that we provided is called "testfile.txt".

When you run each file, it will ask you to input a test file name. This will let you put your own file, or 
you can just type in "testfile.txt" to use the one we provided.

The output file for Processes.cpp is called "Process Results.txt"
The output file for Threads.cpp is called "Thread Results.txt"

The writeup for the assignment is in "OS_hw1.docx"

Noting that we had issues displaying the thread ID due to the process.h library, which contains the gettid() function, does not work on Mac. we commented the code out and if you uncomment it it will print a thread id. 