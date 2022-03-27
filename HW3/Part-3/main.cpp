#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <pthread.h>
using namespace::std;

 //https://stackoverflow.com/questions/19232957/pthread-create-and-passing-an-integer-as-the-last-argument

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
int group1= 0;
int group2= 0;
int group3= 0;
int group4= 0;
int group5= 0;
int group6= 0;
int group7= 0;
int group8= 0;
int group9= 0;
int group10= 0;


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
pthread_mutex_t mutex[10];
pthread_t threads[10];


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

    //create mutexes
    for (int i = 0; i < 10; i++){
        if (pthread_mutex_init(&mutex[i], NULL) != 0) {
            cout << "mutex init failed" << endl;
            exit(1);
        }
    }

    //create a thread for each group
    for (int i = 0; i < 10; i++){
        int startIndex = i * 10;
        int *arg = (int *) malloc(sizeof(*arg));
        *arg = startIndex;

        if (pthread_create(&threads[i], NULL, partitionNums, arg ) != 0){
            cout << "thread creation failed" << endl;
            exit(1);
        }
    }

    //join threads
    for (int i = 0; i < 10; i++){
        if (pthread_join(threads[i], NULL) != 0){
            cout << "thread join failed" << endl;
            exit(1);
        }
    }

    //destroy mutexes
    for (int i = 0; i < 10; i++){
        if (pthread_mutex_destroy(&mutex[i]) != 0){
            cout << "mutex destroy failed" << endl;
            exit(1);
        }
    }
}

void *partitionNums(void* startIndex) {
    int start = *((int*)startIndex);
    int end = start + 10;
    //for each number in nums starting at startIndex, determine group and increment group count
    for (int i = start; i < end; i++){
        int group = determineGroup(nums[i]);
        pthread_mutex_lock(&mutex[group - 1]);
        incrementGroup(group, nums[i]);
        pthread_mutex_unlock(&mutex[group - 1]);
    }
    pthread_exit(NULL);
}

void output(string filename) {
    map<int, int> countMap = {
        {1,group1},
        {2,group2},
        {3,group3},
        {4,group4},
        {5,group5},
        {6,group6},
        {7,group7},
        {8,group8},
        {9,group9},
        {10,group10},
   
    };

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
    //create a switch statement to increment group count
    switch (group) {
        case 1:
            group1++;
            break;
        case 2:
            group2++;
            break;
        case 3:
            group3++;
            break;
        case 4:
            group4++;
            break;
        case 5:
            group5++;
            break;
        case 6:
            group6++;
            break;
        case 7:
            group7++;
            break;
        case 8:
            group8++;
            break;
        case 9:
            group9++;
            break;
        case 10:
            group10++;
            break;
        default:
            break;
    }
}
