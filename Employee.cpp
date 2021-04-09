// including the Employee class header file
#include "Employee.h"

using namespace std;

// In this function, we set all attributes to empty, 0, or \0
// Inputs:   none
// Outputs:  none
Employee::Employee()
{
   // setting all attributes to empty, 0, or \0
   employeeID = "";
   lastName = "";
   firstName = "";
   birthDate = "";
   gender = '\0';
   startDate = "";
   yearlySalary = 0;
}

// In this function, we set all attributes to the arguements passed during the function call
// Inputs:   string employeeIDUI, string lastNameUI, string firstNameUI, string birthDateUI, char genderUI, string startDateUI, double yearlySalaryUI
// Outputs:  none
Employee::Employee(string employeeIDUI, string lastNameUI, string firstNameUI, string birthDateUI, char genderUI, string startDateUI, double yearlySalaryUI)
{
   // setting all attributes to the arguements passed during the function call
   employeeID = employeeIDUI;
   lastName = lastNameUI;
   firstName = firstNameUI;
   birthDate = birthDateUI;
   gender = genderUI;
   startDate = startDateUI;
   yearlySalary = yearlySalaryUI;
}
