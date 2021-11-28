/*
 *
 *	C source file containing the implementation of the 
 *	Vector ADT and Element ADT
 *
 *	The Vector ADT provides a layer of abstraction, 
 *	through the use of the Element ADT, that allows the 
 *	user organize Course pointers with ease.
 *
 *	The Degree, Department, and Student ADTs all contain 
 *	a reference to their own a Vector - each of which 
 *	refers to an unique combination of Course pointers 
 *	that belong to the given Degree, Department, or Student.
 *
 *	Go to header file for more information
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "course.h"
#include "coursePtrVector.h"


/*
 * initElement() takes a Course pointer (parameter coursePtr)
 * as its argument 
 *
 * initElement() allocates heap space for an Element
 * and initializes an Element with a reference
 * to a Course with a Course pointer 
 *
 * initElement() returns a pointer to the new Element
 * an Element consists of:
 * 	a pointer to a Course
 * 	a pointer to disjunct, an optional field for another 
 * 	Element pointer 
 * 	used to refer to a disjunct Course - namely for 
 * 	disjunct requirements in Degree programs
 */
Element* initElement(Course* coursePtr) {

	// checking for null Course pointer
	if (coursePtr == NULL) {
		printf("\nCannot initialize type Element with a "
				"NULL Course pointer argument\n");
		return NULL;
	}
	// allocating heap space for one Element
	Element *elementPtr = (Element*) malloc(sizeof(Element));
	// initializing data members
	elementPtr->disjunct = NULL;
	elementPtr->course = coursePtr;
	return elementPtr; 
}

/*
 * linkDisjunct() takes two Element pointers as arguments
 * linkDisjunct() links Element pointer, disjunctPtr, as 
 * the disjunct to Element pointer, elementPtr
 */
void linkDisjunct(Element *elementPtr, Element *disjunctPtr) {

	// checking for null pointers
	if (elementPtr == NULL || disjunctPtr == NULL) {
		printf("\nCannot link disjunct Element with "
				"NULL Element pointer "
				"argument\n");
		return;
	}

	elementPtr->disjunct = disjunctPtr;
	return;
}



/*
 * initVector() allocates heap space for a Vector
 * and allocates heap space for ten Elements
 * and then initializes the Vector data members:
 * 	the number of Elements in the Vector at a given time, numElements
 *	the maximum number of Elements given the allocated space, capacity
 *	the pointer the Vector's Elements, elements
 * Each Vector starts with a capacity of 10, and a numElements of zero
 */
Vector* initVector() {

	// allocating heap space
	Vector *vectorPtr = (Vector*) malloc(sizeof(Vector));
	// filling in data members
	vectorPtr->numElements = 0;
	vectorPtr->capacity = 10;
	vectorPtr->elements = (Element*) calloc( (vectorPtr->capacity), sizeof(Element) );
	return vectorPtr;
}

/*
 * addElement() takes a Vector pointer, vectorPtr, and an Element pointer,
 * elementPtr, as arguments
 * addElement() adds the Element, elementPtr, to the Vector pointed to by vectorPtr
 * addElement() doubles the Vector capacity as necessary
 */
void addElement(Vector *vectorPtr, Element *elementPtr) {

	// checking for null pointers
	if (vectorPtr == NULL) {
		printf("\nCannot add Element to Vector with "
				"NULL Vector pointer "
				"argument\n");
		return;
	}
	if (elementPtr == NULL) {
		printf("\nCannot add Element to Vector with "
				"NULL Element pointer "
				"argument\n");
		return;
	}
	// double capacity if needed
	if (vectorPtr->numElements == vectorPtr->capacity) {
		int originalCapacity = vectorPtr->capacity;
		int newCapacity = originalCapacity * 2;
		vectorPtr->elements = (Element*) realloc(vectorPtr->elements, newCapacity * sizeof(Element));
		vectorPtr->capacity = newCapacity;
	}

	// adding Element to the Vector and updating Vector's number of elements
	int originalSize = vectorPtr->numElements;
	vectorPtr->elements[originalSize] = *elementPtr;
	vectorPtr->numElements = originalSize + 1;
	return;
}	


/*
 * removeNextElementInDisjunctList() removes the disjunct of the
 * Element pointer argument and links the elementPtr to
 * the next disjunct node in the linked list
 */
void removeNextElementInDisjunctList(Element *elementPtr) {

	// checking for NULL pointer arguments
	if (elementPtr == NULL) {
		printf("\nCannot remove next Element in "
				"disjunct Element list with "
				"NULL Element pointer "
				"argument\n");
		return;
	}

	// unlinking and relinking
	Element *disjunctPtr = elementPtr->disjunct;
	elementPtr->disjunct = disjunctPtr->disjunct;
	return;
}

/*
 * overwriteHeadElementOfDisjunctList() takes an Element
 * pointer as an argument, headPtr
 *
 * headPtr points to an Element in a Vector's allotted
 * contiguous space - instead of in a linked list of 
 * disjuncts
 *
 * overwriteHeadElementOfDisjunctList() takes the 
 * Course pointer from headPtr's first disjunct Element
 * and copies the Course's memory address into the head
 * Element
 *
 * overwriteHeadElementOfDisjunctList() removes the 
 * extraneous disjunct node
 */
void overwriteHeadElementOfDisjunctList(Element *headPtr) {

	// checking for valid input
	if (headPtr == NULL) {

		printf("\nCannot overwrite first Element in "
				"disjunct Element linked list "
				"if the list is empty\n");
		return;
	}

	// the head of list has disjunct Element
	if (headPtr->disjunct != NULL) {
		// copying Course pointer from first disjunct element
		// into the head element
		headPtr->course = headPtr->disjunct->course;
		// removing the first disjunct Course
		removeNextElementInDisjunctList(headPtr);
	}
	return;
}

/*
 * removeElementFromDisjunctList() takes an Element pointer, 
 * disjunctList, and a Course name string, courseName, as
 * arguments
 *
 * removeElementFromDisjunctList() traverses an Element's
 * linked list of disjunct Elements and removes the Element
 * with the Course of name courseName from the linked list
 *
 * relinks disjunct Elements if necessary
 */
void removeElementFromDisjunctList(Element *disjunctList, char *courseName) {

	// checking for NULL pointer arguments	
	if (courseName == NULL) {
		printf("\nCannot remove disjunct Element from "
				"disjunct linked list with no "
				"Course name argument\n");
		return;
	}
	if (disjunctList == NULL) {
		printf("\nCannot remove disjunct Element with "
				"%s with an empty disjunct "
				"linked list\n", courseName);
		return;
	}

	// pointing tempPtr to list head	
	Element *tempPtr = disjunctList;
	// looping through disjunct elements and removing
	// Element if present
	Element *disjunctPtr = tempPtr->disjunct;
	while (disjunctPtr != NULL) {
		if ( strcmp(disjunctPtr->course->name, courseName) == 0 ) {
			removeNextElementInDisjunctList(tempPtr);
		}
		tempPtr = disjunctPtr;
		disjunctPtr = disjunctPtr->disjunct;
	}
	return;
}

/*
 * removeElementFromVector() takes a Vector pointer and the index
 * of the Element in contiguous memory to be removed
 *
 * removeElementFromVector() overwrites the data in the Element
 * at elementIndex with the Element at elementIndex+1
 *
 * removeElementFromVector() continues overwriting each Element
 * with the Element one space higher until all Elements have been
 * shifted 
 *
 * removeElementFromVector() adjusts the capacity of the Vector 
 * if necessary by half
 *
 * removeElementFromVector() does not remove Elements from
 * disjunct linked lists
 */
void removeElementFromVector(Vector *vectorPtr, int elementIndex) {

	// checking for null pointers
	if (vectorPtr == NULL) {
		printf("\nCannot remove Element from Vector "
				"with null Vector pointer "
				"argument\n");
		return;
	}
	if ( (elementIndex >= vectorPtr->numElements) || (elementIndex < 0) ) {
		printf("\nCannot remove Element from Vector "
				"with out of bounds element "
				"index\n");
		return;
	}

	// overwriting Element to remove and shifting Vector Elements
	for (int i = (elementIndex + 1); i < vectorPtr->numElements; i++) {
		Element *tempPtr = vectorPtr->elements + (i-1);
		Element *nextPtr = tempPtr + 1;
		tempPtr->course = nextPtr->course;
		tempPtr->disjunct = nextPtr->disjunct;
		tempPtr = nextPtr;
		nextPtr++;
	}

	vectorPtr->numElements--;

	// half double capacity if needed
	if (vectorPtr->numElements == (vectorPtr->capacity) / 2) {
		int originalCapacity = vectorPtr->capacity;
		int newCapacity = originalCapacity / 2;
		vectorPtr->elements = (Element*) realloc(vectorPtr->elements, newCapacity * sizeof(Element));
		vectorPtr->capacity = newCapacity;
	}

	return;
}


/*
 * removeCoursePtrFromVector() combines the functionality
 * of removeElementFromVector(), overwriteHeadElementOfDisjunctList(),
 * and removeElementFromDisjunctList() to remove a Course pointer
 * with name courseName from the combined Vector and Element ADT
 */
void removeCoursePtrFromVector(Vector *vectPtr, char *courseName) {

	// checking for NULL pointer arguments
	if (courseName == NULL) {
		printf("\nCannot remove Course pointer from "
				"Vector with no Course name "
				"argument\n");
		return;
	}
	if (vectPtr == NULL) {
		printf("\nCannot remove Course pointer for %s "
				"from Vector with NULL Vector "
				"pointer argument\n", courseName);
		return;
	}

	// looping through Elements in contiguous memory of Vector
	for (int i = 0; i < vectPtr->numElements; i++) {
		// checking if the Vector Element's Course is a
		// match to the Course to remove, courseName
		if ( strcmp(vectPtr->elements[i].course->name, courseName) == 0 ) {
			// checking if the Vector Element has disjuncts
			if (vectPtr->elements[i].disjunct == NULL) {
				// if not, remove Element by shifting
				// all Vector Elements by one Element
				removeElementFromVector(vectPtr, i);
			} else {
				// if so, simply overwrite the Vector
				// Element with the data of the first
				// disjunct Element
				overwriteHeadElementOfDisjunctList(vectPtr->elements+i);
			}
		}
		// Vector Element's Course name is not courseName
		// checking all of the Vector Element's disjunct Elements
		if (vectPtr->elements+i != NULL) {
			removeElementFromDisjunctList(vectPtr->elements+i, courseName);
		}
	}
	return;
}


/*
 * printVector() takes a Vector pointer as an argument, vectorPtr
 * printVector() prints the names of all Courses referenced by the Elements
 * of the given Vector
 * printVector() prints disjunct elements appropriately, if any exist
 */
void printVector(Vector *vectorPtr) {

	// checking for null Vector pointer
	if (vectorPtr == NULL) {
		printf("\nCannot print Vector Elements' Courses "
				"with a NULL Vector pointer "
				"argument\n");
		return;
	}

	Element *vectElem = vectorPtr->elements;
	// looping through all Elements and their Course pointers
	for (int i = 0; i < vectorPtr->numElements; i++) {
		Element *disjunctPtr = vectElem[i].disjunct;
		// checking that the Element has a disjunct
		if (disjunctPtr != NULL) {
			printf("OR ");
		}
		// printing the first/only Course name
		printf("%s", vectElem[i].course->name);	
		// printing all disjunct Courses, if any
		while (disjunctPtr != NULL) {
			printf(", %s", disjunctPtr->course->name);
			disjunctPtr = disjunctPtr->disjunct;
		}
		printf("\n");
	}
	return;
}


/*
 * findCoursePtrInVector() takes a Vector pointer, vectorPtr,
 * and a Course's name, courseName, as arguments
 *
 * findCoursePtrInVector() searches all the Elements of a Vector
 * and the linked lists of Element disjuncts for an Element 
 * referring to a Course with courseName
 *
 * if the Course with courseName is found, findCoursePtrInVector()
 * returns a Course pointer
 *
 * otherwise, NULL is returned
 */
Course* findCoursePtrInVector(Vector *vectorPtr, char *courseName) {

	// checking for NULL pointer arguments
	if (courseName == NULL) {
		printf("\nCannot find Course pointer in "
				"Vector with no Course "
				"name argument\n");
		return NULL;

	}
	if (vectorPtr == NULL) {
		printf("\nCannot find Course pointer for "
				"%s in Vector with NULL "
				"Vector pointer "
				"argument\n", courseName);
		return NULL;
	}

	// looping through all Vector Elements
	for (int i = 0; i < vectorPtr->numElements; i++) {

		Course *currentCoursePtr = vectorPtr->elements[i].course;	
		// checking if the Course is found
		if ( strcmp(currentCoursePtr->name, courseName) == 0) {
			return currentCoursePtr;
		}
		// checking all present disjunct Elements for courseName
		Element *disjunctPtr = vectorPtr->elements[i].disjunct;
		while (disjunctPtr != NULL) {
			currentCoursePtr = disjunctPtr->course;	
			if ( strcmp(currentCoursePtr->name, courseName) == 0) {
				return currentCoursePtr;
			}
			disjunctPtr = disjunctPtr->disjunct;
		}

	}
	// no Course, courseName, found
	return NULL;
}



/*
 * printDifferingCourses() takes two Vector pointers as 
 * arguments, sourcePtr and vectToCheckPtr
 *
 * prints all Courses in sourcePtr that are not in 
 * vectToCheckPtr
 *
 * returns the total number of differing Courses
 * and returns -1 for error
 */
int printDifferingCourses(Vector *sourcePtr, Vector *vectToCheckPtr) {

	// checking for NULL pointer arguments
	if ( (sourcePtr == NULL) || (vectToCheckPtr == NULL) ) {

		printf("\nCannot print differing Courses "
				"between two Vectors with "
				"NULL Vector pointer "
				"argument\n");
		return -1;
	}

	// looping through all Courses in source Vector
	int numDifferingCourses = 0;
	for (int i = 0; i < sourcePtr->numElements; i++) {
		// checking to see if Vector Element does not 
		// have disjunct (Courses)
		Element* currElementPtr = sourcePtr->elements+i;
		if (currElementPtr->disjunct == NULL) {
			// print if Course not found in vectToCheck
			if ( findCoursePtrInVector(vectToCheckPtr, currElementPtr->course->name) == NULL ) {
				printf("%s\n", currElementPtr->course->name);
				numDifferingCourses++;
			}
		// Vector Element has disjunct (Courses)
		} else {
			// looping through first Course and then  all 
			// disjuncts of current Element from sourcePtr 
			// to compare to elements in vectToCheck
			bool courseFound = false;
			while (currElementPtr != NULL) {
				if ( findCoursePtrInVector(vectToCheckPtr, currElementPtr->course->name) != NULL) {
					courseFound = true;
					break;	
				}
				currElementPtr = currElementPtr->disjunct;
			}
			if (courseFound == false) {
				currElementPtr = sourcePtr->elements+i;
				printf("OR %s", currElementPtr->course->name);
				currElementPtr = currElementPtr->disjunct;
				numDifferingCourses++;
				while (currElementPtr != NULL) {
					printf(", %s", currElementPtr->course->name);
					currElementPtr = currElementPtr->disjunct;
					numDifferingCourses++;
				}
				printf("\n");
			}
		}
	}
	return numDifferingCourses;
}

/*
 * printAvailableCourses() takes two Vector pointers
 * as arguments, sourcePtr and vectToCheckPtr
 *
 * prints all Courses from vectToCheckPtr whos' 
 * prerequisite requirements have been fulfilled 
 * by Courses from sourcePtr
 */
void printAvailableCourses(Vector *sourcePtr, Vector *vectToCheckPtr) {

	// checking for NULL pointer arguments
	if ( (sourcePtr == NULL) || (vectToCheckPtr == NULL) ) {

		printf("\nCannot print available Courses "
				"between two Vectors with "
				"NULL Vector pointer "
				"argument\n");
		return;
	}

	// loop through all sourcePtr Courses
	for (int i = 0; i < sourcePtr->numElements; i++) {
		Element *elementPtr = sourcePtr->elements+i;
		Course *sourceCoursePtr = elementPtr->course;
		// Course *sourceCoursePtr = sourcePtr->elements[i].course;
		do {
			// check current sourcePtr Course to see if its already in vectToCheck
			if ( findCoursePtrInVector(vectToCheckPtr, sourceCoursePtr->name) == NULL ) {
				LinkedListNode *prereqPtr = sourceCoursePtr->firstPrereq;

				// if NOT, check prerequisite structure from source Course
				// checking if the sourse Course has a prerequisite
				if (prereqPtr == NULL) {
					// if Course has no prereqs and is not in vectToCheck
					// print the name of the Course
					printf("%s\n", sourceCoursePtr->name);

				} 
				// checking if the source Course has only one prereq
				else if (sourceCoursePtr->firstPrereq == sourceCoursePtr->lastPrereq) {
					// single prerequisite - checking if prereq is in vector
					if ( findCoursePtrInVector(vectToCheckPtr, prereqPtr->name) != NULL ) {
						printf("%s\n", sourceCoursePtr->name);
					}

				}
				// checking if the source Course has disjunct prerequisites
				else if ( strcmp(prereqPtr->name, "OR") == 0 ) {
				
					// moving past OR flag
					prereqPtr = prereqPtr->next;

					// looping through all of the source Course prereqs and
					// checking them against vectToCheckPtr
					while (prereqPtr != NULL) {
						if ( findCoursePtrInVector(vectToCheckPtr, prereqPtr->name) != NULL ) {
							// printing source Course
							printf("%s\n", sourceCoursePtr->name);
							// exiting while loop
							break;
						}
						prereqPtr = prereqPtr->next;
					}
				} 
				// source Course has conjunct prerequisites
				// if one prereq is not in vectToCheck then skip the source Course
				// if all prereqs are in the the vectToCheck, print the Course
				else {
					bool prereqsFulfilled = true;
					while (prereqPtr != NULL) {
						if ( findCoursePtrInVector(vectToCheckPtr, prereqPtr->name) == NULL) {
							prereqsFulfilled = false;

						}
						prereqPtr = prereqPtr->next;
					}
					if (prereqsFulfilled) {
						printf("%s\n", sourceCoursePtr->name);
					}
				}
			}
			elementPtr = elementPtr->disjunct;
			if (elementPtr != NULL) {
				sourceCoursePtr = elementPtr->course;
			}
		} while (elementPtr != NULL);
	}	
	return;
}
