#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <pthread.h>
using namespace::std;


// read in file 
void readFile(string filename);
// identify int and increment group count
int determineGroup(int num);
// add one to group count
void incrementGroup(int group, int num);
// creates threads to determine group counts
void generateThreads();
void *partitionNums(void *startIndex);
// get input file name and output file name
string getFile();
string getOutFile();

void output(string filename);

map<int, int> countMap = {
    {1,0},
    {2,0},
    {3,0},
    {4,0},
    {5,0},
    {6,0},
    {7,0},
    {8,0},
    {9,0},
    {10,0},
};
map<int, string> groupList = {
    {1, "(0..9)"},
    {2, "(10..19)"},
    {3, "(20..29)"},
    {4, "(30..39)"},
    {5, "(40..49)"},
    {6, "(50..59)"},
    {7, "(60..69)"},
    {8, "(70..79)"},
    {9, "(80..89)"},
    {10, "(90..99)"},
};

vector<int> nums;


int main() {
    
    //filenames
    string filename;
    string outFile;
    // vector<int> nums;

    filename = getFile();
    outFile = getOutFile();
    readFile(filename);
    generateThreads();
    output(outFile);
    return 0;
}

string getFile() {
    string filename;
    cout << "Type name of input file" << endl;
    cin >> filename;
    return filename;
}
string getOutFile() {
    string outputfilename;
    cout << "\nType name of output file" << endl;
    cin >> outputfilename;
    return outputfilename;
}

void readFile(string filename) {
    int fileNumber;
    ifstream myfile;
    myfile.open(filename);
    if (myfile.fail()){
        cout << "Input file opening failed! \n";
        exit(1);
    }
    if (myfile.is_open()) {
        while (myfile >> fileNumber){
            //add int to nums
            nums.push_back(fileNumber);
        }
    } 
}

void generateThreads(){
    //create an array of 10 threads
    pthread_t threads[10];
    //create a thread for each group
    for (int i = 0; i < 10; i++){
        int startIndex = i * 10;
        int *arg = (int *) malloc(sizeof(*arg));
        *arg = startIndex;
        pthread_create(&threads[i], NULL, partitionNums, arg );
    }
    //join threads
    for (int i = 0; i < 10; i++){
        pthread_join(threads[i], NULL);
    }
}

void *partitionNums(void* startIndex) {
    int start = *(int*)startIndex;
    //for each number in nums starting at startIndex, determine group and increment group count
    for (int i = start; i < start + 10; i++){
        int group = determineGroup(nums[i]);
        incrementGroup(group, nums[i]);
    }
    pthread_exit(NULL);
}

void output(string filename) {
    ofstream outFile;
    outFile.open(filename);
    if (outFile.fail()){
        cout << "Output file opening failed! \n";
        exit(1);
    }
    if (outFile.is_open()) { 
        for (auto it = countMap.begin(); it != countMap.end(); ++it) {
            outFile << "Group " << it->first << " " << groupList[it->first] << ": " << it->second << endl;
        
        }
    }
}

int determineGroup(int num) {
    int group = floor(num/10) + 1;
    return group;
}

void incrementGroup(int group, int num){
    countMap[group] = countMap[group] + 1;
}
