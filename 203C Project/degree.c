/*
 *
 *	C source file for the implementation of the Degree ADT
 *
 *	A Degree contains the name of the degree program
 *	and a Vector of the Degree's required conjunct and
 *	disjunct Courses. 
 *
 *	All Courses of a Degree are referenced through 
 *	Course pointers to Courses on the CourseBinaryTree.
 *
 *	Elements of a Degree's Vector contain Course pointers
 *	and an optional Element pointer to refer to a 
 *	disjunct Element	
 *
 *	Elements allow each Degree to contain its own set
 *	of conjunct and disjunct Course relationships
 *
 *	Go to header file for more information
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "degree.h"
#include "stringFunctions.h"

/*
 * initDegree() takes the Degree's name as a string argument
 * initDegree() allocates heap space, initializes type Degree, 
 * initializes the Degree's data members, and returns a new 
 * Degree pointer 
 */
Degree* initDegree(char *degName) {

	// checking for NULL pointer argument
	if (degName == NULL) {
		printf("\nCannot initialize type Degree "
				"with no Degree name "
				"argument\n");
		return NULL;
	}

	// allocating space on the heap
	Degree *degPtr = (Degree*) malloc(sizeof(Degree));
	// filling in data members
	degPtr->name = degName;
	degPtr->reqCourses = initVector();
	return degPtr;
}

/*
 * addDegreeCourse() takes a Degree pointer, degreePtr, and an
 * Element pointer, elementPtr, as arguments
 * addDegreeCourse() adds an Element to a Degree's Vector of 
 * Elements
 * the Element added contains a Course pointer to be added to 
 * the Degree's required Courses
 * Elements are linked to their disjunct, if any, before 
 * addDegreeCourse() is called
 * addDegreeCourse() calls addElement() which increases 
 * the Vector's list capacity as necessary
*/ 
void addDegreeCourse(Degree *degreePtr, Element *elementPtr) {

	// checking for null pointers
	if (degreePtr == NULL) {
		printf("\nCannot add an Element to a Degree "
				"with a NULL Degree pointer "
				"argument\n");
		return;
	}
	if (elementPtr == NULL) {
		printf("\nCannot add an Element to a Degree "
				"with a NULL Element pointer "
				"argument\n");
		return;
	}

	// addElement...
	addElement(degreePtr->reqCourses, elementPtr);
	return;
}


/*
 * loadDegree() takes an array of strings, lines, as its first 
 * argument
 * each string in lines is a single line from a given Degree
 * file - the newline character has been removed from each 
 * string in lines
 *
 * loadDegree() takes an integer, numLinesInFile, and a 
 * CourseBinaryTree pointer, courseTreePtr, as arguments
 *
 * loadDegree() reads every Course from the array, lines, 
 * (including all conjunct and disjunct Courses) and adds 
 * each to CourseBinaryTree
 *
 * loadDegree() adds each Course pointer to the Degree's
 * Vector of Elements and Courses - referring to the
 * CourseBinaryTree
 *
 * loadDegree() handles all Element disjuncts
 * 
 * then loadDegree() returns a new Degree pointer 
 */
Degree* loadDegree(char **lines, int numLinesInFile, CourseBinaryTree *courseTreePtr) {

	// checking for null pointer
	if (lines == NULL) {
		printf("\nCannot load a Degree with Course "
				"pointers with a NULL "
				"Course lines array "
				"argument\n");
		return NULL;
	}
	// making sure there are lines in the file
	if (numLinesInFile == 0) {
		printf("\nCannot load a Degree when there "
				"are no lines in the Degree "
				"file!\n");
		return NULL;
	}
	// checking for null tree pointer
	if (courseTreePtr == NULL) {
		printf("\nCannot load a Degree with Course "
				"pointers with a NULL "
				"CourseBinaryTree argument\n");
		return NULL;
	}

	Degree *degPtr = initDegree(lines[1]);
	// going through the array of strings from the file  
	for (int j = 2; j < numLinesInFile; ++j) {
		// ignore empty line
		if ( strcmp(lines[j], "") != 0) {
			// splitting line from degree file
			char **courseStringsArr = NULL;
			int numStrings = splitStringAtComma(lines[j], &courseStringsArr);
			// loading degree courses into course tree and
			// course pointers into degree struct
			Element* firstCourseAdded = NULL;
			Element* lastCourseAdded = NULL;
			int i = 0;
			if ( strcmp(courseStringsArr[0], "OR") == 0 ) {
				i++;
			}
			while (i < numStrings) {
				// course on the tree
				Course *coursePtr = insertInCourseBinaryTree(courseTreePtr, courseStringsArr[i]);
				// degree name into course struct
				appendDegreeToCourse(coursePtr, lines[1]);
				Element* newDegreeCourse = initElement(coursePtr);
				if (i <= 1) {
					firstCourseAdded = newDegreeCourse;
				}
				if (i > 1) {
					linkDisjunct(lastCourseAdded, newDegreeCourse);
				}
				lastCourseAdded = newDegreeCourse;
				i++;
			}
			// putting element(s) into degree struct
			addDegreeCourse(degPtr, firstCourseAdded);
		}
	}
	return degPtr;
}

/*
 * printDegree takes a pointer to Degree and prints out
 * the data structure's information, including
 * the Degree name and its conjunct and disjunct
 * Course requirements
 */
void printDegree(Degree *degPtr) {

	// checking for NULL pointer argument
	if (degPtr == NULL) {
		printf("\nCannot print a Degree's Courses "
				"with a NULL Degree pointer "
				"argument\n");
		return;
	}
	
	printf("\nDEGREE\n");
	printf("%s\n", degPtr->name);
	printVector(degPtr->reqCourses);
	return;
}
