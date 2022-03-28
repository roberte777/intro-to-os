#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <mutex>
// #include <process.h>
#include <pthread.h>

using namespace std;

//https://www.youtube.com/watch?v=8Q9CPWuRC6o

string getInputFileName();
int getCharacterCount(string infile);
int countCharacters(string line);
void resultsToFile(int totalCount);
void sortV();

// Class that contains the results to be written to file
struct result{
    int tid;
    int lineNum;
    int charCount;
};

vector<result> v;
mutex myMutex;

void * routine(void* arg) {
    string t = *(string*) arg;
    int lineCharCount = countCharacters(t);
    // cout << gettid();
    return (void*)lineCharCount;
}


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

    if (file.is_open()){
        string line;
        int lineNum = 0;
        int totalCount = 0;
        while(getline(file, line)) {
            pthread_t thread1;
            int count = 0;
            if (pthread_create(&thread1, NULL, &routine, &line) != 0) {
                return -1;
            }  
            
            //thread1 join 
            if (pthread_join(thread1, (void**) &count) != 0) {
                return -1;
            }
            cout << "Individual Line Count: " << count << endl;
            totalCount += count;
            result result = {1, lineNum, count};
            v.push_back(result);
            
            lineNum++;
        }
        file.close();
        cout << "Total Character Count: " << totalCount << endl; 
        resultsToFile(totalCount);
        
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
void resultsToFile(int totalCount){
    sortV();
    fstream newfile;
    newfile.open("Thread Results.txt",ios::out); 
    if(newfile.is_open()){
        for (int i = 0; i < v.size(); i++ ) {
            newfile<<"Line Number: " 
            << v[i].lineNum << " " << "Line Character Count: " 
            << v[i].charCount << "\n" <<endl; 
        }
        newfile << "Total Character Count: " << totalCount << endl;
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

    

