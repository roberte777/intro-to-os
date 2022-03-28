Authors: Ethan Wilkes and Justin Sprouse

The write up for this homework assignment is in the docs folder under the name
"hw_3_writeup.docx"
In that location is the answer to the questions asked in the homework assignment.

The input files, output files, and code files are in the folders corresponding to their part on the homework assignment.
For example, all the files for Part 1 will be under the folder "Part-1".

In order to run the code for each part of this homework assignment, cd into the directory for the part you would like to run and run:

```
g++ -pthread -std=c++11 main.cpp -o build
./build
```

This will begin execution of your program. It will ask the name of the file you would like to import, give the full
file name including the extension. For example, "input.txt"

It will then ask you what you would like the output file to be named. Give the full filename including the
extension. Example: "output.txt"

The program will then execute, and place a file with the name you specified in the current directory.
This output should be in the format specified by the homework assignment.
