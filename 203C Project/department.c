/*
 *
 *	C source file containing the function definitions associated with
 *	the Department abstract data type implementation
 *
 *	The Department ADT is a means of storing organized references to
 *	course pointers that point to courses on the main Course tree
 *	structure. For more information, check the associated headerfile
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringFunctions.h"
#include "department.h"
#include "coursePtrVector.h"
#include "courseBT.h"

/*
 * initDepartment() takes a Department name as a string argument
 * initDepartment() initializes type Department by allocating 
 * heap space, initializing its data members including the 
 * Department name with depName and the (intially empty)
 * Vector of Elements of Course pointer references 
 * initDepartment() returns a pointer to the new Department
 */
Department* initDepartment(char* depName) {

	// checking for NULL pointer argument
	if (depName == NULL) {
		printf("\nCannot initialize type Department "
				"with no Department name "
				"argument\n");
		return NULL;
	}	

	// allocating heap space
	Department *depPtr = (Department*) malloc(sizeof(Department));
	// filling in data members
	depPtr->name = depName;
	depPtr->depCourses = initVector(); 
	return depPtr;
}

/*
 * addDepartmentCourse() takes a pointer to a Department 
 * and a Course as arguments
 * 
 * addDepartmentCourse() adds a Department Course to the 
 * Department's Course pointer Vector
 *
 * the Department is pointed to by departmentPtr and Course 
 * pointed to by coursePtr
 *
 * increases vector list capacity as necessary
 */
void addDepartmentCourse(Department *departmentPtr, Course *coursePtr) {

	// checking for null pointers
	if (departmentPtr == NULL) {
		printf("\nCannot add Course to Department "
				"with NULL Department "
				"pointer argument\n");
		return;
	}
	if (coursePtr == NULL) {
		printf("\nCannot add Course to Department "
				"with NULL Course pointer "
				"argument\n");
		return;
	}
	// initializing Element with the Course pointer 
	// and adding Element to the Department's Vector
	Element* newDepCourse = initElement(coursePtr);
	addElement(departmentPtr->depCourses, newDepCourse);
	return;
}	


/*
 * loadDepartment() takes lines, an array of strings, 
 * and numLinesInFile from a formatted input file as arguments
 *
 * loadDepartment() takes a pointer to the main Course tree, 
 * courseTreePtr as an argument 
 *
 * loadDepartment() puts each Course read from lines and puts 
 * the Course on the Course tree if it does not already exist 
 * on the tree
 *
 * loadDepartment() puts all given Course information into each 
 * Course struct read from the array of strings, lines
 * this includes the prerequisites for each Course, the Department 
 * it belongs to and the title of each Course
 *
 * loadDepartment() adds Elements with Course pointers to all
 * of the Department's Courses on the CourseBinaryTree into
 * the Department's Vector of Elements
 *
 * loadDepartment() then returns a pointer to a Department 
 * structure that contains pointers to all of the Department's
 * Courses 
 */
Department* loadDepartment(char **lines, int numLinesInFile, CourseBinaryTree *courseTreePtr) {

	// checking for error
	if (lines == NULL) {
		printf("\nCannot load Department with no "
				"file lines string array "
				"argument\n");
		return NULL;
	}
	if (numLinesInFile == 0) {
		printf("\nCannot load Department when "
				"there are no lines in "
				"the file!\n");
		return NULL;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot load Department with "
				"Course pointers with "
				"NULL CourseBinaryTree "
				"pointer argument\n");
		return NULL;
	}
	// creating a pointer to Department
	Department *depPtr = initDepartment(lines[1]);

	// looping through department courses
	for (int j = 2; j < numLinesInFile; j += 3) {
		// checking if course name line is empty
		if ( strcmp(lines[j], "") != 0) {

			// put/find first course on the tree
			Course *coursePtr = insertInCourseBinaryTree(courseTreePtr, lines[j]);
			// make sure course title line is not empty
			if ( strcmp(lines[j+1], "") != 0 ) {
				// add title to the course
				coursePtr->title = lines[j+1];
			}
			// add department name to the course
			coursePtr->depName = lines[1];
			// add course pointer to department
			addDepartmentCourse(depPtr, coursePtr);
			// checking to see if prerequisite line is empty	
			if ( strcmp(lines[j+2], "") != 0 ) {
				// put prereq strings into the course struct
				// and put each prerequisite onto the course tree
				char **courseStringsArr = NULL;
				int numStrings = splitStringAtComma(lines[j+2], &courseStringsArr);
				for (int i = 0; i < numStrings; i++) {
					// does not ignore OR to keep track of disjuncts
					appendPrereqToCourse(coursePtr, courseStringsArr[i]);
					// we don't want OR on the course tree
					if ( strcmp(courseStringsArr[i], "OR") != 0) {
						insertInCourseBinaryTree(courseTreePtr, courseStringsArr[i]);
					}
				}
			}
		}
	}
	return depPtr;
}

/*
 * printDepartmentCourses() takes a Department pointer
 * as an argument and prints all of the Department's 
 * Courses' names, Courses' titles, and prerequisites
 */
void printDepartmentCourses(Department *depPtr) {

	// checking for NULL pointer argument
	if (depPtr == NULL) {
		printf("\nCannot print a Department's "
			       "Courses	with a NULL "
			       "Department pointer\n");
		return;
	}

	// looping through all the departments courses
	int numCourses = depPtr->depCourses->numElements;	
	for (int i = 0; i < numCourses; ++i) {
		char *courseName = depPtr->depCourses->elements[i].course->name;
		printf("%s\n", courseName);
		char *courseTitle = depPtr->depCourses->elements[i].course->title;
		printf("%s\n", courseTitle);

		// printing the prerequisites for each course
		printPrerequisites(depPtr->depCourses->elements[i].course);		
	}
	printf("\n");
	return;
}

/*
 * printDepartment takes a pointer to Department
 * and prints out the data structure's information
 */
void printDepartment(Department *depPtr) {

	// checking for NULL pointer argument
	if (depPtr == NULL) {
		printf("\nCannot print a Department's "
			       "information with a NULL "
			       "Department pointer\n");
		return;
	}
	
	printf("\nDEPARTMENT\n");
	printf("%s\n", depPtr->name);
	printDepartmentCourses(depPtr);
	return;
}
