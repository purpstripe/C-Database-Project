/*
 *
 *	Header file for the Course interface
 *
 *	The Course ADT contains information about each course
 *	A Course is built for every Course read from 
 *	every file, including:
 *		A course within a degree program
 *		A course that belongs to a department
 *		A course read from a student's completed 
 *		courses
 *		And as prerequisite of another course!
 *	Each Course is stored on a CourseBinaryTree and referenced by the use
 *	of Course pointers by at least one of three external data structures:
 *		Degree ADT - Department ADT - Student ADT
 *	If the Course is read from a Degree file, then the Degree ADT contains
 *	a pointer to that Course. The same goes for the Department and Student
 *	ADT's - this allows us to reference all Courses of a given Deg, Dep, 
 *	and/or Student and organize different sets of Course pointers for each
 *
 *	Courses can also be accessed directly from the CourseBinaryTree with
 *	Course pointers
 *
 *	For coding convenience and perfomance efficiency, a Course's data members
 *	may also include the title of the course, the department it belongs
 *	to, all degree programs it is apart of, and all of the course's
 *	prerequisites if provided through the use of strings and linked lists
 *	of strings
 */

#ifndef COURSE_H
#define COURSE_H

#include "stringLinkedList.h"

// struct for Course
typedef struct course {
	char *name;
	char *title;
	char *depName;
	LinkedListNode *firstDegree;
	LinkedListNode *lastDegree;
	LinkedListNode *firstPrereq;
	LinkedListNode *lastPrereq;
} Course;


// Course ADT interface


/*
 * initializes type Course with a Course name string argument,
 * allocates heap space for the Course and returns a Course pointer
 * 
 * courseName - string for the name of the Course to
 * be initialized
 */
Course* initCourse(char* courseName);


/*
 * appends a Degree string to a Course's list of Degree programs
 * it belongs to
 *
 * coursePtr - pointer to the Course to append the Degree name to
 *
 * degreeName - name of the Degree to be appended to the given
 * Course pointer
 */
void appendDegreeToCourse(Course* coursePtr, char* degreeName);


/*
 * prints all of the Degree programs for a given Course with
 * new lines between each Degree name
 *
 * coursePtr - pointer to the Course to print Degrees from
 */
void printCourseDegrees(Course* coursePtr);


/*
 * prints all of the Degree programs for a given Course with
 * comma separated Degree names
 *
 * coursePtr - pointer to the Course to print Degrees from
 */
void printCourseDegrees2(Course* coursePtr);


/*
 * appends a prerequisite course name to the Course's list
 * of prerequisite Courses
 *
 * coursePtr - pointer to the Course which to append to
 *
 * prereqName - name of the prerequisite Course to be 
 * appended to the given Course pointer, coursePtr
 */
void appendPrereqToCourse(Course* coursePtr, char* prereqName);


/*
 * clears the Course's list of prerequisite Courses and
 *  frees the used heap space
 *
 *  coursePtr - pointer to the Course to have prerequisites
 *  cleared from
 */
void clearCoursePrerequisites(Course* coursePtr);


/* 
 * prints all of a given Course's prerequisite Course names
 *
 * coursePtr - pointer to the Course from which to print
 * prerequisites
 */
void printPrerequisites(Course* coursePtr);


/*
 * checks a given Course for a prerequisite Course name
 * returning 0 if the prerequisite is not found, 
 * returning 1 if the prerequisite does exist, and
 * returning -1 for errors
 *
 * coursePtr - pointer to the Course to check for a 
 * prerequisite
 *
 * prerequisiteName - name of the prerequisite we want
 * to check for
 */
int checkCourseForPrerequisite(Course* coursePtr, char* prerequisiteName);

#endif 


