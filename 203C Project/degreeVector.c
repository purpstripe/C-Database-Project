/*
 *
 *	C source file containing the function definitions 
 *	for the DegreeVector abstract data type 
 *	implementation
 *
 *	DegreeVector is a ADT for storing structures of 
 *	type Degree in an easy an efficient manner
 *
 *	DegreeVector is a variable space of dynamic
 *	memory containing Degree pointers
 *
 *	More in the associated header file
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "degreeVector.h"

/*
 * initDegree() initializes type DegreeVector 
 * and returns a pointer to the variable 
 * containing the structure
 * 
 * numDegs represents the number of Degrees 
 * in the DegreeVector at any given time
 *
 * capacity is the current total of Degrees 
 * for which heap space has been allocated
 * 	variable as needed
 *
 * degrees is a pointer to the start of the 
 * area of memory containing all of the Degree 
 * pointers
 */
DegreeVector* initDegreeVector() {

	// allocating heap space	
	DegreeVector *degVectorPtr = (DegreeVector*) malloc(sizeof(DegreeVector));
	// filling in data members
	degVectorPtr->numDegs = 0;
	degVectorPtr->capacity = 10;
	degVectorPtr->degrees = (Degree*) calloc( (degVectorPtr->capacity), sizeof(Degree) );
	return degVectorPtr;
}


/*
 * addDegree() takes a pointer to a DegreeVector 
 * and Degree as arguments
 * 
 * addDegree() adds a Degree to the DegreeVector 
 * pointed to by degListPtr with the Degree pointed 
 * to by degreePtr
 *
 * increases list capacity as necessary by double
 * - reallocating heap space for the Vector when the
 * numDegs reaches the capacity
 *
 * updates the DegreeVector's numDegs
 * adds the new Degree to the Vector's 
 * degrees
 */
void addDegree(DegreeVector *degListPtr, Degree *degreePtr) {

	// checking for null pointers
	if (degListPtr == NULL) {
		printf("\nCannot add a Degree to the "
				"Degree list with "
				"a NULL DegreeVector "
				"pointer argument\n");
		return;
	}
	if (degreePtr == NULL) {
		printf("\nCannot add a Degree to "
				"the DegreeVector with "
				"NULL Degree pointer "
				"argument\n");
		return;
	}
	// check to see if we need to double capacity
	if (degListPtr->numDegs == degListPtr->capacity) {
		int originalCapacity = degListPtr->capacity;
		int newCapacity = originalCapacity * 2;
		degListPtr->degrees = (Degree*) realloc(degListPtr->degrees, newCapacity * sizeof(Degree));
		degListPtr->capacity = newCapacity;
	}

	// adding department course to the list (vector) and updating department's size
	int originalSize = degListPtr->numDegs;
	degListPtr->degrees[originalSize] = *degreePtr;
	degListPtr->numDegs = originalSize + 1;
	return;
}	

/*
 * findInDegreeVector() takes a DegreeVector pointer, degListPtr,
 * and a Degree name string to find in the DegreeVector, degreeName
 *
 * findInDegreeVector() loops through all of the Degree pointers in
 * the given DegreeVector with a temporary Degree pointer and checks
 * each Degree in the Vector against the given degreeName with the
 * function from string.h, strcmp()
 *
 * findInDegreeVector() returns a Degree pointer if the Degree is
 * found, and returns NULL if no Degree with degreeName is found
 *
 * findInDegreeVector() prints and error message and returns NULL
 * for any errors 
 */
Degree* findInDegreeVector(DegreeVector *degListPtr, char *degreeName) {

	// checking for NULL pointer arguments
	if (degreeName == NULL) {
		printf("\nCannot find a Degree in "
				"the DegreeVector if "
				"there's no Degree name "
				"argument\n");
		return NULL;
	}
	if (degListPtr == NULL) {
		printf("\nCannot find the %s Degree "
				"in the Degree list "
				"with a NULL "
				"DegreeVector pointer "
				"argument\n", degreeName);
		return NULL;
	}

	// looping through all Degrees in the DegreeVector
	// looking for a Degree of degreeName	
	Degree *degPtr = degListPtr->degrees;
	for (int i = 0; i < degListPtr->numDegs; i++) {
		if ( strcmp(degreeName, degPtr->name) == 0 ) {
			return degPtr;
		}
		degPtr++;
	}
	return NULL;
}
