/*******************************************************************************************************
* Employee Tracking System
*
* This program gets opens "Employee.txt", and sends it to a function in the FileIO class to read
* its contents into an array of dynamically allocated pointers to objects.
*
* It then prints a menu and gives the user the choice of whether to add to, remove from, look up 
* from, sort alphabetically and display, or save the information of the employees to "Employee.txt"
*
* The program will then print the menu and allow the user to access the data another
* way. It will keep repeating until the user responds with a 5 to the menu options, at which point
* it will save the information of the employees to "Employee.txt".
*
* Written by Ahmed Iqbal for CS1337.009, assignment 5, starting April 5, 2021.
* NetID: axi180011
*******************************************************************************************************/

// including preprocessor directives and header files
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Employee.h"
#include "FileIO.h"

using namespace std;

// declaring function prototypes
void showMenu();
void enterData(Employee* employeeArr[], int count);
void sort(Employee* employeeArr[], int count);
double roundNumber(double number);
void displayData(Employee* employeeArr[], int count);
void employeeLookUp(Employee* employeeArr[], int count, string ID);
int deleteEmployee(Employee* employeeArr[], int count, string ID);
void deleteArray(Employee* employeeArr[], int count);

int main()
{
   // declaring variables
   int count;
   int field;
   string fileName = "Employee.txt";
   // declaring array of pointers to Employee objects and a FileIO object
   Employee* employeeArr[100];
   FileIO employeeData;

   // initialzing count with the number of Employees in the file
   count = employeeData.read(employeeArr, fileName);

   // looping until option 5 in selected in the menu
   while (true)
   {
      // displaying the menu options
      showMenu();

      // input validation loop to ascertain a valid menu choice was selected
      do
      {
         cout << "Please enter one of the above menu options: ";
         cin >> field;
         cout << endl;

      } while (field != 1 && field != 2 && field != 3 && field != 4 && field != 5);

      // using menu input to decide what to do with the data
      switch (field)
      {
         // allows user to enter new employee data
      case 1: 
      {
         enterData(employeeArr, count);
         count++;
         break;
      }
         // sorts and displays all data alphabetically by last name
      case 2: 
      {
         sort(employeeArr, count);
         displayData(employeeArr, count);
         break;
      }
         // finds and displays the employee's data whose ID number was entered by the user
      case 3: 
      {
         string ID;
         cout << "Please enter the ID of the employee you are searching for: ";
         cin >> ID;
         employeeLookUp(employeeArr, count, ID);
         break;
      }
         // deletes an employee's data if the ID given by the user is found
      case 4:
      {
         string ID;
         cout << "Please enter the ID of the employee you are searching for: ";
         cin >> ID;
         count = deleteEmployee(employeeArr, count, ID);
         break;
      }
         // saves the changes made by the user to the data and writes data to Employee.txt
      case 5:
      {
         employeeData.print(employeeArr, count, fileName);
         exit(0);
         break;
      }
      default:
         break;
      }
   }

   // calling function to free the array
   deleteArray(employeeArr, count);

   return 0;
}// end function main

// In this function, we display a menu containing options on what to do with the data to the user
//
// Inputs:   none
// Outputs:  none
void showMenu()
{
   cout << "1. Enter new employee information" << endl
      << "2. Display all employee information in alphabetical order by last name" << endl
      << "3. Lookup an employee by ID" << endl 
      << "4. Remove an employee" << endl
      << "5. Save all data to Employee.txt and exit" << endl
      << endl;
}

// In this function, we allow the user to input the information of a new employee
//
// Inputs:   an array of pointers to Employees, the integer count
// Outputs:  none
void enterData(Employee* employeeArr[], int count)
{
   // bool flag used to indicate whether entered ID is already in the system
   bool match = false;

   // declaring temp variables that will hold value read in from inFile as attributes are private
   string tempStr;
   char tempChr;
   double tempDbl;

   // prompting user for ID
   cout << "Please enter ID of new employee" << endl;
   cin >> tempStr;

   // input validation loop to ensure entered ID is not in the system
   do
   {
      match = false;

      // looping through the data to see if entered ID matches an ID already in the system and setting match to true if so
      for (int ix = 0; ix < count; ix++)
      {
         if ((employeeArr[ix]->getEmployeeID()) == tempStr)
         {
            match = true;
         }
      }

      // printing error message and getting new input if ID is already in the system
      if (match == true)
      {
         cout << "Error. This ID number is registered to another employee. Please enter new ID" << endl;
         cin >> tempStr;
      }

   } while (match == true);

   // allocating new Employee object once a unique ID has been entered
   employeeArr[count] = new Employee;

   // reading in and storing data in attributes using the set functions
   employeeArr[count]->setEmployeeID(tempStr);

   cout << "Enter last name" << endl;
   cin >> tempStr;
   employeeArr[count]->setLastName(tempStr);

   cout << "Enter first name" << endl;
   cin >> tempStr;
   employeeArr[count]->setFirstName(tempStr);

   cout << "Enter birth date" << endl;
   cin >> tempStr;
   employeeArr[count]->setBirthDate(tempStr);

   cout << "Enter gender (M or F)" << endl;
   cin >> tempChr;
   employeeArr[count]->setGender(tempChr);

   cout << "Enter start date" << endl;
   cin >> tempStr;
   employeeArr[count]->setStartDate(tempStr);

   // input validation loop to make sure salary is a positive number
   do
   {
      cout << "Enter yearly salary greater than zero" << endl;
      cin >> tempDbl;
      employeeArr[count]->setYearlySalary(tempDbl);
   } while (!(tempDbl > 0));

   cout << endl;
}

// In this function, we sort the employee's data alphabetically, by last name, using the bubble sort
//
// Inputs:   an array of pointers to Employees, the integer count
// Outputs:  none
void sort(Employee* employeeArr[], int count)
{
   // bool flag to let us know if any swaps have occured(if not, sort is finished)
   bool swapFlag;
   Employee* temp;

   do
   {
      swapFlag = false;

      // for loop to traverse the until the penultimate element of the array
      for (int ix = 0; ix < count - 1; ix++)
      {
         // determining if a element is alphabetically greater than the next element, and if so, swapping them
         if (employeeArr[ix]->getLastName() > employeeArr[ix + 1]->getLastName())
         {
            temp = employeeArr[ix];
            employeeArr[ix] = employeeArr[ix + 1];
            employeeArr[ix + 1] = temp;

            // setting loop control variabile to do another iteration
            swapFlag = true;
         }
      }
      // loop will iterate until no swaps are done(until array is fully sorted)
   } while (swapFlag);
}

// In this function, we round the double passed as an arguement to the nearest whole number
//
// Inputs:  the double number
// Outputs:  none
double roundNumber(double number)
{
   // determining what the value after the decimal is and deciding whether to round up or down
   // based on whether it is greater than or equal to 0.5 or not, respectively
   double difference = number - static_cast<int>(number);
   if (difference > 0.5)
   {
      number = static_cast<int>(number) + 1.0;
   }
   else
   {
      number = static_cast<int>(number);
   }

   return number;
}

// In this function, we display the employee data with neat formatting and headers
//
// Inputs:   an array of pointers to Employees, the integer count
// Outputs:  none
void displayData(Employee* employeeArr[], int count)
{
   // printing the headers in the desired formatting
   cout << setw(12) << "Employee ID" << setw(15) << "Last Name" << setw(15) << "First Name"
      << setw(15) << "Birth Date" << setw(10) << "Gender" << setw(15) << "Start Date"
      << setw(17) << "Yearly Salary" << setw(17) << "Monthly Salary" << endl;

   // printing the information of each employee(sorted as desired) line by line
   for (int ix = 0; ix < count; ix++)
   {
      cout << setw(12) << employeeArr[ix]->getEmployeeID() << setw(15) << employeeArr[ix]->getLastName() << setw(15) << employeeArr[ix]->getFirstName()
         << setw(15) << employeeArr[ix]->getBirthDate() << setw(10) << employeeArr[ix]->getGender() << setw(15) << employeeArr[ix]->getStartDate()
         << setw(17) << fixed << setprecision(0) << roundNumber(employeeArr[ix]->getYearlySalary()) << setw(17) << fixed << setprecision(2) 
         << employeeArr[ix]->getMonthlySalary() << endl;
   }

   cout << endl;
}

// In this function, we look up and print an employee's information given his/her employee ID.
// If the employee is not found, we display a message saying that.
//
// Inputs:   an array of pointers to Employees, the integer count, the string ID
// Outputs:  none
void employeeLookUp(Employee* employeeArr[], int count, string ID)
{
   bool found = false;
   int ix = 0;

   // walking through the array until we find the employee that was requested or until we reach the end of the array
   while (!found && ix < count)
   {
      // printing the employee's information if the ID numbers match
      if (employeeArr[ix]->getEmployeeID() == ID)
      {
         cout << endl << setw(12) << "Employee ID" << setw(15) << "Last Name" << setw(15) << "First Name"
            << setw(15) << "Birth Date" << setw(10) << "Gender" << setw(15) << "Start Date"
            << setw(17) << "Yearly Salary" << setw(17) << "Monthly Salary" << endl;

         cout << setw(12) << employeeArr[ix]->getEmployeeID() << setw(15) << employeeArr[ix]->getLastName() << setw(15) << employeeArr[ix]->getFirstName()
            << setw(15) << employeeArr[ix]->getBirthDate() << setw(10) << employeeArr[ix]->getGender() << setw(15) << employeeArr[ix]->getStartDate()
            << setw(17) << fixed << setprecision(0) << roundNumber(employeeArr[ix]->getYearlySalary()) << setw(17) << fixed << setprecision(2) 
            << employeeArr[ix]->getMonthlySalary() << endl;

         // letting the loop know a match was found
         found = true;
      }
      ix++;
   }

   // printing message if the employee was not found
   if (!found)
   {
      cout << endl << "The employee you are looking is not in the file." << endl;
   }

   cout << endl;
}

// In this function, we delete an employee's information given their ID by the user, if it exists
//
// Inputs:   an array of pointers to Employees, the integer count, the string ID
// Outputs:  none
int deleteEmployee(Employee* employeeArr[], int count, string ID)
{
   bool found = false;
   int ix = 0;

   // walking through the array until we find the employee that was requested or until we reach the end of the array
   while (!found && ix < count)
   {
      // printing the employee's information if the ID numbers match
      if (employeeArr[ix]->getEmployeeID() == ID)
      {
         // freeing the memory pointed to by the pointer to Employee
         // and setting each succesive pointer to point to the previous object
         delete employeeArr[ix];
         for (int iy = ix; iy < count - 1; iy++)
         {
            employeeArr[iy] = employeeArr[iy + 1];
         }

         // decrementing count so we don't access an element that doesn't point to anything
         count--;

         // letting the loop know a match was found
         found = true;
      }
      ix++;
   }

   // printing message if the employee was not found
   if (!found)
   {
      cout << "The employee you are looking is not in the file." << endl;
   }

   cout << endl;

   return count;
}

// In this function, we delete every dynamically allocated element of the of the array using a for loop
//
// Inputs:   an array of pointers to Employees, the integer count
// Outputs:  none
void deleteArray(Employee* employeeArr[], int count)
{
   // for loop to traverse the array and delete the elements one by one
   for (int ix = 0; ix < count; ix++)
   {
      delete employeeArr[ix];
   }
}