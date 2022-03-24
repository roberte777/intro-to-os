#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace::std;


// read in file 
void readFile(string filename);
// identify int and increment group count
void identifyInt(int num);
// get input file name
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


int main() {
    string filename;
    string outFile;
    filename = getFile();
    outFile = getOutFile();
    readFile(filename);
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
            int group = floor(fileNumber/10) + 1;
            countMap[group] = countMap[group] + 1;
        }
    } 
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
