/*
Skeleton code for linear hash indexing
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"

using namespace std;


int main(int argc, char* const argv[]) {

    //Create the index
    LinearHashIndex emp_index("EmployeeIndex.dat");
    emp_index.createFromFile("Employee.csv");

    // ofstream testFile;
    // testFile.open("TEST.dat", ios::in | ios::ate);
    // testFile.write("BRUH", 4);
    // testFile.seekp(50);
    // testFile.write("BRO!", 4);
    // testFile.close();
    
    // testFile.open("TEST.dat", ios::in | ios::ate);
    // testFile.seekp(7);
    // testFile.write("TEMP", 4);
    // testFile.close();


    /*
    char userChoice = ' ';
    int userId = 0;

    while(userChoice != 'n')
    {
      cout << "Please enter a Employee ID to search: ";
      cin >> userId;
      manager.findRecordById(userId);

      cout << "Do you want to search again[y,n]: ";
      cin >> userChoice;
      userChoice = tolower(userChoice);
    }
    */

    return 0;
}
