/*
 *
 *	Header file for DegreeVector ADT interface
 *
 *	DegreeVector is an efficient means of 
 *	storing multiple structures of type Degree. 
 *	Using a Vector allows for fast access, an 
 *	easy implementation and a simple interface. 
 *	We add a new Degree to the DegreeVector 
 *	everytime a new input file of type Degree 
 *	is input into the program.
 *
 */

#ifndef DEGREEVECTOR_H
#define DEGREEVECTOR_H

#include "degree.h"

// struct for managing the list of degree programs
typedef struct degreeVector {
	unsigned int numDegs;
	unsigned int capacity;
	Degree *degrees;	
} DegreeVector;

// interface


/*
 * allocates heap space for a DegreeVector
 * and, initially, ten Degree pointers
 *
 * initializes a DegreeVector's data members
 * including the numDegs, the number of 
 * Degress, as zero, and the initial
 * capacity, at ten
 *
 * the DegreeVectors degrees data member
 * is a pointer to the first Degree pointer
 * of the DegreeVector in memory
 */
DegreeVector* initDegreeVector();


/*
 * adds a Degree to the DegreeVector
 * increases the DegreeVector's numDegs
 * and increases the capacity of the
 * DegreeVector as needed (once the 
 * numDegs reaches the same value as
 * the capacity)
 *
 * degListPtr - pointer to the 
 * DegreeVector we are adding a
 * Degree to
 *
 * degreePtr - pointer to the Degree
 * we are adding to the DegreeVector
 */
void addDegree(DegreeVector* degListPtr, Degree* degreePtr);


/*
 * finds a Degree with given degree name argument
 * in the DegreeVector specified
 *
 * returns a pointer to the Degree, if found
 * and otherwise returns NULL
 * 
 * prints error statements as needed
 *
 * degListPtr - pointer to the DegreeVector
 * we are searching in
 *
 * degreeName - string for the Degree name
 * we are looking for
 *
 */
Degree* findInDegreeVector(DegreeVector* degListPtr, char* degreeName);

#endif
