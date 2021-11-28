/*
 *
 *	Header file for the DepartmentVector ADT and its interface
 *
 *	DepartmentVector stores Departments in a Vector, similar to
 *	an ArrayList structure - allowing simple iteration and access
 *	DepartmentVector contains a counter for the number of 
 *	Departments added, the current capacity of the (Vector) list, 
 *	and a pointer to Deparments in contiguous memory.
 *	DepartmentVector adds a Deparment and updates its data members 
 *	for every Department file that is read.
 *
 *	The DepartmentVector is also updated with every new Department
 *	added using the 'a' command from user input in the program
 *	terminal
 */

#ifndef DEPARTMENTVECTOR_H
#define DEPARTMENTVECTOR_H

#include "department.h"

// vector struct for elements of type Deparment
typedef struct departmentVector {
	unsigned int numDeps;
	unsigned int capacity;
	Department *departments;
} DepartmentVector;


// DepartmentVector interface

/* allocates heap space for a DepartmentVector and 
 * (initially) ten Departments in contiguous memory
 * initializes the data elements of the
 * DepartmentVector including its numDeps at zero,
 * its capacity at ten, and its pointer to the
 * list's Departments, *departments
 */
DepartmentVector* initDepartmentVector();


/*
 * adds a Department to the DepartmentVector pointer
 * passed as an argument
 * increments the DeparmentVector's numDeps for each
 * Department and increases the DepartmentVector's 
 * list capacity as needed
 *
 * depListPtr - pointer to the DeparmentVector
 * to which we want to add a Department
 *
 * departmentPtr - pointer to the Department we
 * want to add
 */
void addDepartment(DepartmentVector* depListPtr, Department* departmentPtr);

/*
 * searches every Department in the given DepartmentVector
 * for a Department with the given Department name
 * if the Department is found in the DepartmentVector, 
 * then a pointer to that Department is returned
 * the function returns NULL if the Department is not
 * found or when any pointer arguments are NULL
 *
 * depListPtr - pointer to the DepartmentVector we
 * want to search
 *
 * departmentName - string for the name of the 
 * Department we want to search for
 */
Department* findInDepartmentVector(DepartmentVector* depListPtr, char* departmentName);

#endif
