#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

//this youtube video told us how to do pipes https://www.youtube.com/watch?v=8Q9CPWuRC6o

string getInputFileName();
int getCharacterCount(string infile);
int countCharacters(string line);
void resultsToFile(int count);
void sortV();

// Class that contains the results to be written to file
struct result{
    int pid;
    int lineNum;
    int charCount;
};
//glboal variable to store the results
vector<result> v;

int main () {
    string file = getInputFileName();
    int count = getCharacterCount(file);
    
    return 1;
}
//gets input file name from user
string getInputFileName() {
    string filename;
    cout << "Enter the name of the file" << endl; 
    cout << "File Name: ";
    cin >> filename;
    return filename;
}
//Gets the required results, 
//creates multiple processes and gets the character count of lines in the file
int getCharacterCount(string infile) {
    fstream file;
    int count = 0;
    file.open(infile, ios::in);
    if (!file) {
        cout << "File Does Not Exist" << endl; 
        return -1;
    }
    int p1[2]; //C => P
    int p2[2]; // P => C
    if (pipe(p1) == -1) { 
        cout <<"error1";
        return -1; 
    }
    if (pipe(p2) == -1) { 
        cout <<"error2";
        return -1; 
    }

    if (file.is_open()){
        string line;
        int lineNum = 0;
        //while there is still a line of the file to get
        while(getline(file, line)) {
            //make a new child process
            int pid = fork();
            if (pid == -1){
                return -1;
            } else if (pid == 0) {
                //the line passed from the parent object
                string line;
                //the character count of the line
                int lineCharCount;
                //read in the line from the parent process
                if (read(p2[0], &line, sizeof(line)) == -1) { return -1; }
                //function that just counts the characters in the line
                lineCharCount = countCharacters(line);
                //write back to the parent process
                if (write(p1[1], &lineCharCount, sizeof(lineCharCount)) == -1) { return -1; }
                //exit the child process, should contain child ID in future
                exit(0);
               
            } else {
                //this is the parent process
                int lineCharCount = 0;
                //write the line to the child process
                if (write(p2[1], &line, sizeof(line)) == -1) { return -1; }
                //read character count from child process
                if (read(p1[0], &lineCharCount, sizeof(lineCharCount)) == -1) { return -1; }
                //print it for my reference
                cout << "Individual Line Count: " << lineCharCount << endl;
                //looks like this pid is the same pid from line 69
                int childpid = wait(NULL);
                cout << "child pid from wait = " << childpid << "\n" << "child pid from fork = " << pid << "\n" <<endl;
                //add the character count to the total count
                count += lineCharCount;
                //make an object to store the results
                result result = {pid, lineNum, lineCharCount};
                //add the object to the vector that stores all the results
                v.push_back(result);

            } 
            lineNum++;
        }
        file.close();
        close(p1[0]);
        close(p2[0]);
        close(p1[1]);
        close(p2[1]);
        cout << "Total Character Count: " << count << endl; 
        resultsToFile(count);
        
    }
    return 1;
}

//Counts the alphabetical characters in a given string
int countCharacters(string line){
    int length = line.length();
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (isalpha(line[i])){
            count++;
        }
    }
    return count;
}

//Puts the results into a file
void resultsToFile(int count){
    sortV();
    fstream newfile;
    newfile.open("Process Results.txt",ios::out); 
    if(newfile.is_open()){
        for (int i = 0; i < v.size(); i++ ) {
            newfile<<"Child Process ID: " << v[i].pid << " " << "Line Number: " 
            << v[i].lineNum << " " << "Line Character Count: " 
            << v[i].charCount << "\n" <<endl; 
        }
        newfile << "Total Character Count: " << count << endl;
    }
    newfile.close(); 
    
}

//Sorts the vector array containing the results
void sortV(){
    for (int i = 0; i < v.size() - 1;i++){
        for (int j = i+1; j < v.size(); j++){
            if (v[i].lineNum > v[j].lineNum){
                result temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

    

