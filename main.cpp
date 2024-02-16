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
    LinearHashIndex emp_index("EmployeeIndex.txt");
    //emp_index.createFromFile("Employee.csv");

    /*
    // Loop to lookup IDs until user is ready to quit
    int bruh = 11432159;

    int hashResult = bruh%216;
    int binResult = 0;
    int modResult = 0;
    int divResult = hashResult;
    //grab i least significant bits
    for(int k = 0; k < 3; k++){
        //build an int that looks like binary
        modResult = divResult%2;
        divResult = divResult/2;

        binResult += pow(10,k) * modResult;
        cout << binResult << endl;

    }

    cout << binResult << endl;
    */

    
    

    return 0;
}
