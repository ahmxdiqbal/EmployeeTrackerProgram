#ifndef FILEIO_H
#define FILEIO_H

// including the Employee class header file and preprecessor directives
#include <string>
#include <fstream>
#include "Employee.h"

using namespace std;

// declaration of class FileIO
class FileIO
{
public:
   // functions to read data from the the file into an array of pointers to Employee objects
   // and to save the employee data in that array to "Employee.txt"
   int read(Employee* employeeArr[], string fileName);
   void print(Employee* employeeArr[], int count, string fileName) const;
};

#endif
