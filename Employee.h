#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

using namespace std;

// declaration of class FileIO
class Employee
{
private:
   // attributes are made private
   string employeeID;
   string lastName;
   string firstName;
   string birthDate;
   char gender;
   string startDate;
   double yearlySalary;
public:
   // constructor declarations
   Employee();
   Employee(string, string, string, string, char, string, double);

   // set function declarations
   void setEmployeeID(string employeeIDUI) { employeeID = employeeIDUI; }
   void setLastName(string lastNameUI) { lastName = lastNameUI; }
   void setFirstName(string firstNameUI) { firstName = firstNameUI; }
   void setBirthDate(string birthDateUI) { birthDate = birthDateUI; }
   void setGender(char genderUI) { gender = genderUI; }
   void setStartDate(string startDateUI) { startDate = startDateUI; }
   void setYearlySalary(double yearlySalaryUI) { yearlySalary = yearlySalaryUI; }

   // set function declarations (all have the const specifier)
   string getEmployeeID() const { return employeeID; }
   string getLastName() const { return lastName; }
   string getFirstName() const { return firstName; }
   string getBirthDate() const { return birthDate; }
   char getGender() const { return gender; }
   string getStartDate() const { return startDate; }
   double getYearlySalary() const { return yearlySalary; }
   double getMonthlySalary() const { return yearlySalary / 12; }
};

#endif
