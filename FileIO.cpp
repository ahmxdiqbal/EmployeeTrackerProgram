// including the Employee class and FileIO class header files and preprecessor directives
#include <iostream>
#include <iomanip>
#include <fstream>
#include "FileIO.h"
#include "Employee.h"

using namespace std;

// In this function, we read in the employee data separated by spaces, one employee per line into
// an array of pointers to Employee objects and return the number of Employees
//
// Inputs:   an array of pointers to Employees, the string fileName
// Outputs:  the integer count
int FileIO::read(Employee* employeeArr[], string fileName)
{
   // creating a count variable to return from function
   int count = 0;

   // declaring temp variables that will hold value read in from inFile as attributes are private
   string tempStr;
   char tempChr;
   double tempDbl;

   // opening the fileName passed to the function, namely, "Employee.txt"
   ifstream inFile(fileName);
   // if the file exists, we read in its data. If not, we will create it when we print it to "Employee.txt"
   if (inFile)
   {
      // looping while count is less than 100 and we can read in the first string on the line
      while ((count < 100) && (inFile >> tempStr))
      {
         employeeArr[count] = new Employee;
         // reading in and storing data in attributes using the set functions
         employeeArr[count]->setEmployeeID(tempStr);
         inFile >> tempStr;
         employeeArr[count]->setLastName(tempStr);
         inFile >> tempStr;
         employeeArr[count]->setFirstName(tempStr);
         inFile >> tempStr;
         employeeArr[count]->setBirthDate(tempStr);
         inFile >> tempChr;
         employeeArr[count]->setGender(tempChr);
         inFile >> tempStr;
         employeeArr[count]->setStartDate(tempStr);
         inFile >> tempDbl;
         employeeArr[count]->setYearlySalary(tempDbl);

         // incrementing count per every employee
         count++;
      }
      // printing error message if more than 100 employees' information are entered
      if (count >= 100)
      {
         cout << "Error. You cannot store the information of more than a 100 employees" << endl;
      }

      // closing the file after we are done with it
      inFile.close();
   }

   return count;
}

// In this function, we print the employee data separated by spaces, one employee per line to "Employee.txt"
//
// Inputs:   an array of pointers to Employees, the integer count, the string fileName
// Outputs:  none
void FileIO::print(Employee* employeeArr[], int count, string fileName) const
{
   // opening "Employee.txt". ofstream opens whether the file exists or not and overwrites the contents if they exist
   ofstream outFile(fileName);

   // printing the employees' information separated by spaces, one employee per line
   for (int ix = 0; ix < count; ix++)
   {
      outFile << employeeArr[ix]->getEmployeeID() << " " << employeeArr[ix]->getLastName() << " " << employeeArr[ix]->getFirstName()
         << " " << employeeArr[ix]->getBirthDate() << " " << employeeArr[ix]->getGender() << " " << employeeArr[ix]->getStartDate()
         << " " << employeeArr[ix]->getYearlySalary() << endl;
   }

   // closing the file after we are done with it
   outFile.close();
}
