//**********************************************************************
//*                                                                    *
//* Program Name: PROG06 - Manage a company's employee bonus program   *
//* Author:       Austin Sink                                          *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: March 29, 2018                                       *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* I pledge the lines in this C++ program are my own original work,   *
//* and none of the lines in this C++ program have been copied from    *
//* anyone else, unless I was specifically authorized to do so by my   *
//* CS246 instructor.                                                  *
//*                                                                    *
//*                                                                    *
//*          Signed: ____________________________________              * 
//*                              (signature)                           *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* This program manages a company's bonus program. The company enters *
//* their name, number of employees, bonus year, bonus amount per      *
//* employee, and each employee's years of service. The year hired and *
//* bonus amount are then calculated for each employee then each       *
//* employee is printed in table form sorted by employee ID then       *
//* ascending by year hired.                                           *
//*                                                                    *
//**********************************************************************

#include "stdafx.h"
#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>
using namespace std;

//**********************************************************************
//*                        Symbolic Constants                          *
//**********************************************************************
#define MAX_NAME_LENGTH 80   // Max company name length
#define COMPANY_ALLOC_ERR 1  // Cannot allocate company info memory
#define NAME_ALLOC_ERR 2     // Cannot allocate company name memory
#define EMPLOYEE_ALLOC_ERR 3 // Cannot allocate employee DB memory

//**********************************************************************
//*                        Program Structure                           *
//**********************************************************************
// The company information
struct company_information
{
    char  *p_company_name; // Point to the name of the company
    int   bonus_year,      // Year that bonuses are given
          employee_number; // Number of employees
    float bonus_amount;    // Bonus amount per year
};

//**********************************************************************
//*                        Class Definitions                           *
//**********************************************************************
// The company employee bonus record
class company_bonus_record
{
    int   employee_id,           // Identification of the employee
          service_years,         // Years that the employee has served
          year_hired;            // Year the employee was hired
    float employee_bonus_amount; // Employee bonus amount per year
public:
    // Set the variables
    void  set_id            (int id)   {employee_id           = id;}
    void  set_service_years (int sy)   {service_years         = sy;}
    void  set_year_hired    (int yh)   {year_hired            = yh;}
    void  set_bonus_amount  (float ba) {employee_bonus_amount = ba;}

    // Get the variables
    int   get_id            () {return employee_id;}
    int   get_service_years () {return service_years;}
    int   get_year_hired    () {return year_hired;}
    float get_bonus_amount  () {return employee_bonus_amount;}

    // Destructor, delete employee bonus record
          ~company_bonus_record() {cout <<
                                   "\n\nDestructor executing . . .";}
};

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void                 print_heading();
    // Print the program heading and instructions
company_information  *get_company_information();
    // Get information on the company
company_bonus_record *get_employees(company_information company_information);
    // Get DB of employee bonus records
void print_employees (company_bonus_record *p_database_start, 
                      int employee_number, const char *p_order);
    // Print the DB of employee bonus records in a table form
void sort_employees  (company_bonus_record *p_database_start, 
                      int employee_number);
    // Sort the DB of employee bonus records in ascending order
void fatal_error     (int error_code, const char *p_function_name, 
                      const char *p_memory_type);
    // Print a fatal error message and abort

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
    company_information  *p_company_information; // Point to the company info
    company_bonus_record *p_database;            // Point to the bonus records

    // Print the heading and instructions
    cout << "\n\n\n\n\n\n";
    print_heading();

    // Get and print the company information
    p_company_information = get_company_information();
    cout << "\n\nCompany name:        " << p_company_information->p_company_name;
    cout <<   "\nYear of the bonuses: " << p_company_information->bonus_year;
    cout <<   "\nNumber of employees: " << p_company_information->employee_number;
    cout <<   "\nBonus per year:     $" << p_company_information->bonus_amount;

    // Get and print the company bonus DB
    p_database = get_employees(*p_company_information);
    print_employees(p_database, p_company_information->employee_number,
                                                            "IN UNSORTED ORDER");

    // Sort ascending the company bonus DB
    sort_employees(p_database, p_company_information->employee_number);
    print_employees(p_database, p_company_information->employee_number,
                                                            "SORTED BY YEAR HIRED");

    // Free the dynamically allocated memory
    delete[] p_database;
    delete   p_company_information;

    // Print goodbye and terminate
    cout << "\n\n\nThanks for processing employee bonuses today.";
    cout << "\n\n\n\n\n\n";
    return 0;
}

//**********************************************************************
//*                   Print the program instructions                   *
//**********************************************************************
void print_heading()
{
    cout << "\n========================================================";
    cout << "\nThis program asks for information about your company and";
    cout << "\nabout each employee. It then calculates the bonus amount";
    cout << "\nowned each employee based on the number of service years.";
    cout << "\n========================================================";
}

//**********************************************************************
//*                     Get the company information                    *
//**********************************************************************
company_information *get_company_information()
{
    company_information *p_company_information; 
                                    // Point to the company information
    char                p_company_name[MAX_NAME_LENGTH + 1]; 
                                    // Point to the company name

    // Allocate memory for the company info and abort if memory is not available
    try
    {
        p_company_information = new company_information;
    }
    catch(bad_alloc xa)
    {
        fatal_error(COMPANY_ALLOC_ERR, "get_company_information()",
                                                        "company_information");
    }

    // Allocate memory for the company name and about if memory is not available
    try
    {
        p_company_information->p_company_name = new char[strlen(company_name) + 1];
    }
    catch(bad_alloc xa)
    {
        fatal_error(NAME_ALLOC_ERR, "get_company_information()",
                                                        "company_name");
    }
    strcpy_s(p_company_information->p_company_name, strlen(company_name) + 1,
                                                                    company_name);

    // Get the number of employees
    do
    {
        cout << "\nEnter your number of employees (1 or more): ";
        cin  >> p_company_information->employee_number;
        if(p_company_information->employee_number < 1)
        {
            cout << "The number of employees must be 1 or more.";
        }
    } while (p_company_information->employee_number < 1);
    
    // Get the year in which bonuses were given
    cout << "Enter the year in which the bonuses are given (YYYY): ";
    cin  >> p_company_information->bonus_year;

    // Get the bonus amount
    cout << "Give the yearly bonus amount per employee (on dollars): ";
    cin  >> p_company_information->bonus_amount;

    // Return the company information
    return p_company_information;
}

//**********************************************************************
//*                     Get the employee bonus DB                      *
//**********************************************************************
company_bonus_record *get_employees(company_information company_information)
{
    int employee_number = 1, // ID number of each employee
        service_year;        // Number of service years
    company_bonus_record 
}