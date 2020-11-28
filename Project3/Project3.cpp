//Project 3
//Author: Han
//ID: 
//Compile: g++

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 100; 

//read file and get size
int readFile(int arrayIn[], string fileNameIn) {
    int index = 0;
    ifstream ifs;
    ifs.open(fileNameIn.c_str(), ios::in);
    if (! ifs.is_open()) {
        cout << "Invalid file name" << endl;
    }
    while (ifs >> arrayIn[index]) {
        index++;
    }
    ifs.close();
    return index;
}

//print file data
void printFile(int arrayIn[], int arraySize, string fileNameIn) {
    cout << "The list of " << arraySize << " numbers in file " << fileNameIn << " is: \n";
    for (int i = 0; i < arraySize; i++) {
        cout << arrayIn[i] << endl;
    }
    cout << endl;
}

//merge and sort array
void sort(int array1In[], int arraySize1, int array2In[], int arraySize2, int outputArrayIn[]) {
    int size = arraySize1 + arraySize2;
    //merge array
    for (int i = 0; i < size; i++) {
        outputArrayIn[i] = array1In[i];
        if (i >= arraySize1) {
            outputArrayIn[i] = array2In[i - arraySize1];
        }
    }

    //bubble Sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (outputArrayIn[j] > outputArrayIn[j + 1]) {
                int temp = outputArrayIn[j];
                outputArrayIn[j] = outputArrayIn[j + 1];
                outputArrayIn[j + 1] = temp;
            }
        }
    }
    
    cout << "The sorted list of " << size << " numbers is:";
    for (int i = 0; i < size; i++) {
        cout << outputArrayIn[i] << " ";
    }
    cout << endl;
}

//write output array
void writeOutput(int outputArrayIn[], int outputArraySize, string fileNameIn) {
    ofstream ofs;
    ofs.open(fileNameIn.c_str(), ios::out);
    for (int i = 0; i < outputArraySize; i++) {
        ofs << outputArrayIn[i] << endl;
    }
    ofs.close();
}


int main() {
    int array1[MAX_SIZE] = {0};
    int array1_size = 0;
    int array2[MAX_SIZE] = {0};
    int array2_size = 0;
    int outputArray[MAX_SIZE] = {0};

    string fileName;
    string outputName;

    cout << "*** Welcome to Han's sorting program ***" << endl;
    cout << "Enter the first input file name: ";
    cin >> fileName;
    array1_size = readFile(array1, fileName);
    if (array1_size == 0) {
        return 0;
    }
    printFile(array1, array1_size, fileName);
    
    cout << "Enter the second input file name: ";
    cin >> fileName;
    array2_size = readFile(array2, fileName);
    if (array2_size == 0) {
        return 0;
    }
    printFile(array2, array2_size, fileName);

    sort(array1, array1_size, array2, array2_size, outputArray);
    cout << "Enter the output file name: ";
    cin >> outputName;
    writeOutput(outputArray, array1_size + array2_size, outputName);
    cout << "*** Please check the new file - " << outputName << " ***" << endl;
    cout << "*** Goodbye. ***" << endl;

    return 0;
}



