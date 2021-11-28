/*
 *
 *	Header file for Vector ADT and Element ADT's interfaces
 *
 *	The Vector ADT provides a layer of abstraction, through the
 *	use of the Element ADT, that allows the user to organize and 
 *	refer to Course pointers with ease.
 *
 *	Initially, all Courses are stored and linked in the 
 *	CourseBinaryTree. Then each Department, Degree, and Student 
 *	is linked to its Courses on the tree with Course pointers.
 *
 *	A Degree has required courses, a Department has offered courses,
 *	and a Student has completed courses. Notice that different 
 *	Departments, Degrees, and Students will have to reference the 
 *	some of the same Courses on the CourseBinaryTree. Through the 
 *	use of the Vector ADT, no copies of a Course are needed; instead, 
 *	we use a single Course pointer in more than one place to link a 
 *	particular Course to more than one Degree, Department, or 
 *	Student.
 *
 *	Notice, however, that each Vector is populated by a unique 
 *	collection of Elements. The first data member of any Element is 
 *	the Course pointer. A single Course pointer can exist in more 
 *	than one Element at a time, allowing for example, a Degree and 
 *	Department to contain unique references to the same Course.
 *
 *	Each Element has an optional pointer to another Element, named 
 *	disjunct, for disjunct Degree requirements. Within different 
 *	Degrees, a course may be a conjunct requirement for one and a 
 *	disjunct for another. With the disjunct Element pointer data 
 *	member, we can handle this discrepency of Course pointer 
 *	organization very easily. There is no need for Course to 
 *	contain disjunct information for every Degree it belongs to;
 *	instead, Degree's Elements contain that information for us.
 *
 */

#ifndef COURSEPTRVECTOR_H
#define COURSEPTRVECTOR_H

#include "course.h"

// struct for data related to each Element
typedef struct element {
	struct element *disjunct;
	Course *course;
} Element;

// struct for data related to each Vector
typedef struct vector {
	unsigned int numElements;
	unsigned int capacity;
	Element *elements;
} Vector;


// element structure interface

/*
 * allocates heap space for an Element and
 * initializes an Element with a Course pointer argument
 * and a NULL disjunct Element pointer
 * returns a pointer to the new Element
 *
 * coursePtr - pointer to the Course used to
 * initialize the new Element
 */
Element* initElement(Course* coursePtr);

/* links one Element to another through the use of
 * the Element's disjunct pointer, starting or 
 * appending to a linked Element list
 *
 * elementPtr - pointer to the Element to attach 
 * the disjunct to
 *
 * disjunctPtr - pointer to the Element attached as 
 * a disjunct Element
 */
void linkDisjunct(Element* elementPtr, Element* disjunctPtr);


// vector structure interface

/* allocates heap space for a Vector and
 * initializes its data members with zero numElements,
 * ten for its capacity, and allocates heap space
 * for ten Elements and stores a pointer to the 
 * first in memory, *elements
 */
Vector* initVector();

/*
 * adds an Element to a Vector, updates the 
 * Vector's numElements data member and 
 * increases capacity as necessary
 * all Elements can be accessed through
 * the Vector's *elements data member
 *
 * vectorPtr - pointer to the Vector to which 
 * the new Element is added
 *
 * elementPtr - pointer to the Element to be
 * added
 */ 
void addElement(Vector* vectorPtr, Element* elementPtr);

/*
 * removes a Course pointer and its associated
 * Element with given Course name from every 
 * Element within a given Vector,
 * including the disjunct Element linked lists
 *
 * vectPtr - pointer to the Vector we remove
 * a Course from
 *
 * courseName - name of the Course we attempt
 * to remove from vectPtr
 */
void removeCoursePtrFromVector(Vector* vectPtr, char* courseName);

/*
 * prints the names of all Courses referenced
 * by the Elements of the given Vector, including
 * all disjunct Elements' Courses, if they exist
 *
 * vectorPtr - pointer to the Vector whose Elements 
 * we print
 */
void printVector(Vector* vectorPtr);

/*
 * finds a given Course name within the Elements
 * of the Vector argument and returns a pointer
 * to the Course with the Course name argument,
 * if there is one
 * otherwise, returns NULL
 * 
 * vectorPtr - pointer to the Vector which is
 * searched
 *
 * courseName - string for the name of the Course
 * we are looking for
 */ 
Course* findCoursePtrInVector(Vector* vectorPtr, char* courseName);

/*
 * prints all Courses in the first Vector that 
 * are not in the other Vector
 *
 * sourcePtr - pointer to the Vector we 
 * loop through to check against the Courses
 * in vectToCheckPtr - the Courses we print
 * if not found in vectToCheckPtr
 *
 * vectToCheckPtr - pointer to the Vector whose
 * Courses we check against
 */
int printDifferingCourses(Vector* sourcePtr, Vector* vectToCheckPtr);

/*
 * prints all Courses from the second Vector
 * whos' prerequisite requirements have been 
 * fulfilled by Courses from the first Vector
 *
 * sourcePtr - pointer to the Vector whose 
 * Courses we loop through to check against the 
 * prerequisites in vectToCheckPtr
 *
 * vectToCheckPtr - pointer to the Vector whose
 * prerequisite requirements we check for
 * completion
 */
void printAvailableCourses(Vector* sourcePtr, Vector* vectToCheckPtr);

#endif
