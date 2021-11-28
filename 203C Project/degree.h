/*
 *
 *	Header file for Degree ADT's interface
 *
 *	The Degree ADT contains the name of the Degree program 
 *	and a reference to the Degree's Vector of conjunct and disjunct
 *	Course requirements.
 *
 *	All members of the Degree Vector, reqCourses, are Elements. Each
 *	Element contains a Course pointer to a Course on the 
 *	CourseBinaryTree and an optional Element pointer, disjunct,
 *	to be filled if the given Course has one or more disjunct
 *	requirements.
 *
 *	Disjunct requirements are stored as a linked list of Element
 *	pointers. If there are more than one disjunct, then each
 *	disjunct must be accessed by traversing the linked list of
 *	Element pointers.
 * 
 *	The Degree ADT provides a means of organizing references to a
 *	degree program's courses in a data structure.
 *	The Vector in a Degree can have conjunct and disjunct Course pointers,
 *	representing the structure of required courses for the degree program.
 *
 *	A Degree's Course information can be accessed by traversing a Degree's
 *	Elements for a particular Course or by finding a Course on the 
 *	CourseBinaryTree and accessing its linked list of Degree program names
 *
 */

#ifndef DEGREE_H
#define DEGREE_H

#include "coursePtrVector.h"
#include "courseBT.h"

// struct for data related to a degree program
typedef struct degree {
	char *name;
	Vector *reqCourses;
} Degree;


// degree structure inteface


/*
 * allocates heap space for a Degree
 * and initializes a Degree's
 * data members including the name
 * of the Degree program and a 
 * reference to the Degree's Vector
 *
 * degName - string for the name of the
 * Degree we want to initialize
 */
Degree* initDegree(char* degName);


/*
 * adds an Element to a Degree's 
 * Vector of Elements; thus, adding 
 * a reference to a Degree's Course
 * to the Degree's data structure
 *
 * disjunct Course requirements
 * are linked through the Element
 * ADT before being added to a Degree
 * in addDegreeCourse()
 *
 * degreePtr - pointer to the Degree we
 * want to add a Course Element to
 * 
 * elementPtr - pointer to the Element
 * we want to add to the Degree, 
 * degreePtr
 */
void addDegreeCourse(Degree* degreePtr, Element* elementPtr);


/*
 * takes an array of lines from a Degree
 * file and adds each Course name
 * to the CourseBinaryTree and
 * reads every Course in the array into 
 * the Degree's Vector of Elements
 * including both conjunct and disjunct
 * Course requirements
 *
 * lines - an array of strings read
 * line by line from an input Degree
 * file
 *
 * numLinesInFile - the number of lines
 * read from the input Degree file
 *
 * courseTreePtr - pointer to the 
 * CourseBinaryTree we add Courses to
 */
Degree* loadDegree(char** lines, int numLinesInFile, CourseBinaryTree* courseTreePtr);

/*
 * prints out a Degree program's
 * information including the Degree
 * program name and all of the 
 * Degree's Course requirements,
 * both conjunct (by new line)
 * and disjunct (separated by commas
 * and with an "OR")
 *
 * degPtr - pointer to the Degree
 * whose information we are printing
 */
void printDegree(Degree* degPtr);

#endif


