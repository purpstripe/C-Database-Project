/*
 *
 *	C source file containing the function definitions for the
 *	DepartmentVector ADT implementation.
 *
 *	The DepartmentVector is used to organize all of the loaded
 *	Departments in an efficient and practical manner. More 
 *	information about the use of the DepartmentVector can 
 *	be found in the associated header file. For information 
 *	about it's implementation, refer to the functions below.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "departmentVector.h"

/*
 * initDepartmentVector() initializes type DepartmentVector by 
 * allocating space on the heap for a DepartmentVector,
 * setting its Department count to zero and allocating space on 
 * the heap for ten structures of type Department - the initial
 * Vector capacity is initialized to ten
 * initDepartmentVector() returns a pointer to the 
 * DeparmentVector
 */
DepartmentVector* initDepartmentVector() {
	
	// allocating heap space
	DepartmentVector *depVectorPtr = (DepartmentVector*) malloc(sizeof(DepartmentVector));
	// initializing data members
	depVectorPtr->numDeps = 0;
	depVectorPtr->capacity = 10;
	depVectorPtr->departments = (Department*) calloc( (depVectorPtr->capacity), sizeof(Department) );
	return depVectorPtr;
}

/*
 * addDepartment() takes a pointer to DepartmentVector, depListPtr, and 
 * a pointer to the Department to be added, departmentPtr, as its arguments
 * addDepartment() adds a Department to the DepartmentVector's Vector
 * (contiguous memory)
 * and increments the DepartmentVector's numDeps data member
 * addDepartment() increases list capacity as necessary
 */
void addDepartment(DepartmentVector *depListPtr, Department *departmentPtr) {

	// checking for NULL pointer arguments
	if (depListPtr == NULL) {
		printf("\nCannot add Department to the "
				"Department list with NULL "
				"DepartmentVector pointer "
				"argument\n");
		return;
	}
	if (departmentPtr == NULL) {
		printf("\nCannot add Department to the "
				"Department list with NULL "
				"Department pointer "
				"argument\n");
		return;
	}
	// check to see if we need to double capacity
	if (depListPtr->numDeps == depListPtr->capacity) {
		int originalCapacity = depListPtr->capacity;
		depListPtr->departments = (Department*) realloc(depListPtr->departments, (originalCapacity * 2) * sizeof(Department));
		depListPtr->capacity = originalCapacity * 2;
	}	
	
	// adding Department to the list (Vector) and updating the Department list size
	int originalSize = depListPtr->numDeps;
	depListPtr->departments[originalSize] = *departmentPtr;
	depListPtr->numDeps = originalSize + 1;
	return;
}

/*
 * findInDepartmentVector() takes a DepartmentVector pointer, depListPtr,
 * and Department name C string as arguments
 *
 * findInDepartmentVector() iterates through the given DepartmentVector
 * searching for a Department with name departmentName (strcmp())
 *
 * if the Department is found, findInDepartmentVector() returns a pointer
 * to the Department with name departmentName
 *
 * otherwise, the function returns NULL - with an error message is needed
 */
Department* findInDepartmentVector(DepartmentVector *depListPtr, char *departmentName) {

	// checking for NULL pointer arguments
	if (departmentName == NULL) {
		printf("\nCannot find a Department in the "
				"Department list if there's "
				"no Department name "
				"argument\n");
		return NULL;
	}
	if (depListPtr == NULL) {
		printf("\nCannot find the %s Department in "
				"the Department list if the "
				"DepartmentVector pointer "
				"argument is "
				"NULL\n", departmentName);
		return NULL;
	}

	// iterating through all Departments and checking
	// Department names	
	Department *depPtr = depListPtr->departments;
	for (int i = 0; i < depListPtr->numDeps; i++) {
		if ( strcmp(departmentName, depPtr->name) == 0 ) {
			return depPtr;
		}
		depPtr++;
	}
	// Department not found
	return NULL;
}
