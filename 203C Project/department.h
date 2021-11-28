/*
 *
 *	Header file for Department ADT interface
 *
 *	The Department ADT consists of a Department 
 *	name as a string. and a reference to a Vector 
 *	structure that contains Elements with Course 
 *	pointers - references to the different available 
 *	Courses for that particular Department. Each 
 *	Department is initialized with the input of a 
 *	Department file with the Department's name. 
 *	All subsequent Courses listed in the file will 
 *	first be added to the main CourseBinaryTree and 
 *	then references to the Department's Courses 
 *	will be loaded into the Department's Vector 
 *	of Course pointers.
 *
 */

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "coursePtrVector.h"
#include "courseBT.h"

// struct for data related to each department
typedef struct department {
	char *name;
	Vector *depCourses;
} Department;


// department structure interface

/*
 * allocates heap space for a 
 * Department and initializes 
 * with given Department name string
 * argument and a pointer to an, 
 * initially empty, Vector for 
 * the Department's available
 * Courses
 *
 * depName - name of the Department that
 * we want to initialize
 */
Department* initDepartment(char* depName);

/*
 * adds a Deparment Course to the 
 * Department's Course pointer
 * Vector of Elements
 *
 * updates the Department's Vector
 * numElements and increases the
 * Vector capacity as needed
 *
 * departmentPtr - pointer to the 
 * Department we are adding a Course
 * to
 *
 * coursePtr - pointer to the Course
 * we want to add
 */
void addDepartmentCourse(Department* departmentPtr, Course* coursePtr);

/*
 * takes an array of lines from the given
 * Department file and loads every Course
 * read from the file into the CourseBinaryTree,
 * updates the Course's name, title, and prerequisites;
 * and finally, adds each Course pointer into Vector
 * Elements of the initialized Department
 * returns a pointer to the loaded and initialized
 * Department
 *
 * lines - an array of strings read
 * line by line from an input
 * Department file
 *
 * numLinesInFile - the number of lines
 * read from the input Department file
 *
 * courseTreePtr - pointer to the 
 * CourseBinaryTree we add Courses to
 */
Department* loadDepartment(char** lines, int numLinesInFile, CourseBinaryTree* courseTreePtr);

/*
 * prints the name, title, and prerequisites
 * of all Courses of a given Department,
 * separated by new lines
 *
 * depPtr - pointer to the Department whose
 * Course names we want to print
 */
void printDepartmentCourses(Department* depPtr);

/*
 * prints all information associated
 * with a Department, including the
 * Department name and all of its
 * Courses' information
 *
 * depPtr - pointer to the Department whose
 * information we want to print
 */
void printDepartment(Department* depPtr);

#endif
