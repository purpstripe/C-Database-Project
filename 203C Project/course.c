/*
 *
 *	C source file containing the implementation of 
 *	Course abstract data type
 *
 *	The Course ADT contains information about each 
 *	course including:
 *		Course name (ex CS 320)
 *		Course title (ex Databases)
 *		The Department it belongs to
 *		All Degree programs it's in
 *		Its list of prerequisite courses
 *
 * 	Refer to the header file, course.h, for more 
 * 	information about the functionality of the 
 * 	Course ADT and its interface
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"


/*
 * initCourse() takes a Course name as a string
 * argument (parameter courseName) and allocates 
 * heap space for the Course 
 * *
 * initCourse() initializes the Course's name
 * with the string argument and initializes all 
 * other data members with NULL
 * 
 * initCourse() returns a Course pointer to the
 * new Course
 */
Course* initCourse(char* courseName) {

	if (courseName == NULL) {
		printf("\nCannot initialize a Course with no "
				"Course name argument\n");
		return NULL;
	}	

	// allocating heap space
	Course *coursePtr = (Course*) malloc(sizeof(Course));
	// filling in data members
	coursePtr->name = courseName;
	coursePtr->title = NULL;
	coursePtr->depName = NULL;
	coursePtr->firstDegree = NULL;
	coursePtr->lastDegree = NULL;
	coursePtr->firstPrereq = NULL;
	coursePtr->lastPrereq = NULL;
	return coursePtr;
}

/*
 * appendDegreeToCourse() takes a pointer to Course 
 * (parameter coursePtr) and the name of a 
 * Degree (parameter degreeName) as arguments
 * 
 * appendDegreeToCourse() adds the Degree string argument
 * to the Course's linked list of its Degree programs
 *
 * if it is the Course's first Degree, then it is made 
 * the firstDegree and lastDegree in the Course's
 * data members
 *
 * if it is not the first, then the Degree is appended 
 * to the end of the Course's Degree list
 */
void appendDegreeToCourse(Course *coursePtr, char *degreeName) {

	// checking for valid input arguments
	if (degreeName == NULL) {
		printf("\nCannot append a Degree name to Course "
				"without a Degree name argument\n");
		return;
	}
	if (coursePtr == NULL) {
		printf("\nCannot append the Degree, %s, to Course "
				"with NULL Course pointer "
				"argument\n", degreeName);
		return;
	}

	// initializing linked list node for Degree 
	LinkedListNode *newDegreePtr = initListNode(degreeName);
	// handling cases for appending the degree 
	// if first degree in linked list
	if (coursePtr->firstDegree == NULL) {
		coursePtr->firstDegree = newDegreePtr;
		coursePtr->lastDegree = newDegreePtr;
		return;
	}
	// otherwise, appending degree to the end 
	// of the list
	insertAfterListNode(coursePtr->lastDegree, newDegreePtr);
	coursePtr->lastDegree = newDegreePtr;
	return;
}

/*
 * printCourseDegrees() takes a Course pointer 
 * (parameter coursePtr) as its argument
 *
 * printCourseDegrees() traverses the Course's
 * linked list of Degrees and prints each one
 *
 * if the list is empty, NO LISTED DEGREES is
 * printed to the terminal
 */
void printCourseDegrees(Course *coursePtr) {

	// checking for valid input
	if (coursePtr == NULL) {
		printf("\nCannot print a Course's Degrees with "
				"NULL Course pointer argument\n");
		return;
	}

	// checking that the course has recorded Degrees
	// and printing all Degrees
	if (coursePtr->firstDegree != NULL) {
		LinkedListNode *tempPtr = coursePtr->firstDegree;
	
		while(tempPtr != NULL) {
	
			printf("%s\n", tempPtr->name);
			tempPtr = tempPtr->next;
		}
		return;
	}
	// there are no recorded Degrees for the Course
	printf("NO LISTED DEGREES\n");
	return;
}

/*
 * printCourseDegrees2() takes a Course pointer
 * (parameter coursePtr) as its argument
 *
 * printCourseDegrees2() traverses a Course's
 * linked list of Degrees and prints each one
 * in a different format than printCourseDegrees()
 *
 * if the list is empty, NO DEGREES ON RECORD
 * is printed to the terminal
 */
void printCourseDegrees2(Course *coursePtr) {

	// checking for valid input
	if (coursePtr == NULL) {
		printf("\nCannot print Course's Degrees with NULL "
			       "Course pointer argument\n");
		return;
	}

	// checking that the Course has Degrees
	// and printing all Degrees
	if (coursePtr->firstDegree != NULL) {
		LinkedListNode *tempPtr = coursePtr->firstDegree;
		printf("%s", tempPtr->name);
		tempPtr = tempPtr->next;
		while (tempPtr != NULL) {
			printf(", %s", tempPtr->name);
			tempPtr = tempPtr->next;
		}
		printf("\n");
		return;
	}
	// there are no Degrees 
	printf("NO DEGREES ON RECORD\n");
	return;
}

/*
 * appendPrereq() takes a Course pointer 
 * (parameter coursePtr) and the name of a prerequisite 
 * course (parameter prereqName) as arguments
 * 
 * appendPrereq() adds the prerequisite to the Course's
 * linked list of prerequisite names
 *
 * if it is the first prereq, then it is made the 
 * firstPrereq and lastPrereq in the Course's data members
 *
 * if it is not, then the prereq is appended to the end of 
 * the prereq list and made to be lastPrereq
 */
void appendPrereqToCourse(Course *coursePtr, char *prereqName) {

	// checking null pointers
	if (prereqName  == NULL) {
		printf("\nCannot append prerequisite to a Course "
				"with no prereq name argument\n");
		return;
	}
	if (coursePtr == NULL) {
		printf("\nCannot append prerequisite %s to a "
				"Course with a NULL Course "
				"pointer argument\n", prereqName);
		return;
	}

	// initializing linked list node for 
	// new prerequisite course and handling
	// cases for appending the prerequisite
	LinkedListNode *newPrereqPtr = initListNode(prereqName);
	if (coursePtr->firstPrereq == NULL) {
		coursePtr->firstPrereq = newPrereqPtr;
		coursePtr->lastPrereq = newPrereqPtr;
		return;
	}
	insertAfterListNode(coursePtr->lastPrereq, newPrereqPtr);
	coursePtr->lastPrereq = newPrereqPtr;

	return;
}

/*
 * clearCoursePrerequisites() takes a Course pointer
 * (parameter coursePtr) as an argument
 *
 * clearCoursePrerequisites() clears the linked list
 * of prerequisite name strings
 */
void clearCoursePrerequisites(Course* coursePtr) {

	// checking for null pointer argument
	if (coursePtr == NULL) {
		printf("\nCannot clear a Course's prerequiste "
				"string list with a NULL "
				"Course pointer argument\n");
		return;
	}

	clearLinkedList( &(coursePtr->firstPrereq) );

	return;
}

/*
 * printPrerequisites() takes a Course pointer as an 
 * argument (parameter coursePtr)
 *
 * printPrerequisites() traverses through the Course's
 * string linked list and prints each prerequisite name 
 *
 * if the list is empty, then NO PREREQUISITES is printed
 * to the terminal
 */
void printPrerequisites(Course *coursePtr) {

	// checking for valid input
	if (coursePtr == NULL) {
		printf("\nCannot print a Course's prerequisites "
				"with NULL Course pointer "
				"argument\n");
		return;
	}

	// checking that the Course has prerequisite
	// and printing formatted output depending
	// on the number of prerequisites
	if (coursePtr->firstPrereq != NULL) {
		LinkedListNode *tempPtr = coursePtr->firstPrereq;
		
		// checking if the Course has only one prereq
		if ( coursePtr->firstPrereq == coursePtr->lastPrereq ) {
			printf("%s\n", coursePtr->firstPrereq->name);
			return;
		}
		// there are more than one prerequisite Course
		else {
			if ( strcmp(tempPtr->name, "OR") == 0){
				printf("%s ", tempPtr->name);
				tempPtr = tempPtr->next;
			}
			printf("%s", tempPtr->name);
			tempPtr = tempPtr->next;
			while (tempPtr != NULL) {
				printf(", %s", tempPtr->name);
				tempPtr = tempPtr->next;
			}
			printf("\n");
			return;
		}
	}
	// there are no prerequisite courses
	printf("NO PREREQUISITES\n");
	return;
}

/*
 * checkCourseForPrerequisite() takes a Course pointer
 * (parameter coursePtr) and a prerequisite name
 * (parameter prerequisiteName) as arguments
 *
 * checkCourseForPrerequisite() checks given Course's 
 * prerequisites to see if there are any matches 
 * to the input  prerequisite string
 *
 * returns 0 if there is no match (false)
 * and returns 1 if the Course has the prerequisite 
 * string in its string LinkedList
 * 
 * checkCourseForPrerequisite() returns -1 for all
 * errors
 */
int checkCourseForPrerequisite(Course *coursePtr, char *prerequisiteName) {

	// checking for valid input
	if (prerequisiteName == NULL) {
		printf("\nCannot check Course for given "
				"prerequisite with no "
				"prerequisite string argument\n");
		return -1;
	}
	if (coursePtr == NULL) {
		printf("\nCannot check Course for prerequisite "
				"%s with NULL Course pointer "
				"argument\n", prerequisiteName);
		return -1;
	}

	// checking that the Course has prerequisite
	if (coursePtr->firstPrereq != NULL) {
		LinkedListNode *tempPtr = coursePtr->firstPrereq;
		
		while (tempPtr != NULL) {

			if ( strcmp(tempPtr->name, prerequisiteName) == 0 ){
				return 1;
			}
			tempPtr = tempPtr->next;
		}
	}
	return 0;
}
