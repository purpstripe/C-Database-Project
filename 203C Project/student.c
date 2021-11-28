/*
 *
 *	C source file for the Student ADT implementation
 *
 *	The Student ADT contains all the information 
 *	for a given Student including:
 *		the Student's name
 *		the Student's Degree program
 *		a list of the Student's completed
 *		Courses
 *
 *	Each Student has a Course pointer Vector
 *	full of Elements containing Course
 *	references to the CourseBinaryTree
 *
 *	All the information about a Student's 
 *	completed Courses can be accessed using
 *	said Course pointers
 *
 * 	Every Student is stored in a 
 * 	StudentBinaryTree organized
 * 	lexicographically by Student name
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/*
 * initStudent() takes a C string as
 * an argument
 *
 * initStudent() allocates heap space
 * for Student and initializes the
 * Student's name with the C string 
 * argument
 * 
 * initStudent() initializes the 
 * Student's Degree program with NULL
 * and initializes its completedCourses
 * data member with a pointer to the 
 * Student's (currently) empty Vector
 *
 * initStudent() returns a pointer to
 * the new Student adn returns NULL if
 * there is an error
 */
Student* initStudent(char* stuName) {

	// checking for NULL pointer argument
	if (stuName == NULL) {
		printf("\nCannot initialize Student with "
				"no Student name argument\n");
		return NULL;
	}

	// allocating memory and initializing Student
	Student *studentPtr = (Student*) malloc(sizeof(Student));
	studentPtr->name = stuName;
	studentPtr->degree = NULL;
	studentPtr->completedCourses = initVector();
	return studentPtr;
}

/*
 * setStudentDegree() takes a Student pointer
 * and a C string as arguments
 *
 * setStudentDegree() simply accesses the
 * given Student's Degree data member and 
 * changes its value with the C string argument
 */
void setStudentDegree(Student* studentPtr, char* degreeName) {

	// checking for NULL pointer arguments
	if (degreeName == NULL) {
		printf("\nCannot change Student's Degree "
				"with no Degree name "
				"argument\n");
		return;
	}
	if (studentPtr == NULL) {
		printf("\nCannot change Student's Degree to %s "
				"with NULL Student pointer "
				"argument\n", degreeName);
		return;
	}
	studentPtr->degree = degreeName;
	return;
}

/*
 * addCompletedCourse() takes a Student pointer and
 * a Course pointer as arguments
 *
 * addCompletedCourse() initializes an Element
 * with the given Course pointer
 *
 * addCompletedCourse() adds a completed Course to 
 * the Student's Course pointer Vector of Elements
 *
 * increases Vector list capacity as necessary
 */
void addCompletedCourse(Student *studentPtr, Course *coursePtr) {

	// checking for null pointers
	if (studentPtr == NULL) {
		printf("\nCannot add Course to Student's "
				"completed Courses with "
				"NULL Student pointer "
				"argument\n");
		return;
	}
	if (coursePtr == NULL) {
		printf("\nCannot add Course to Student's "
				"completed Courses with "
				"NULL Course pointer "
				"argument\n");
		return;
	}

	Element* newCompletedCourse = initElement(coursePtr);
	addElement(studentPtr->completedCourses, newCompletedCourse);
	return;
}	

/*
 * loadStudent() takes lines, an array of strings, 
 * and numLinesInFile from a formatted input file
 *
 * loadStudent() also takes a pointer to the 
 * CourseBinaryTree as arguments
 *
 * loadStudent() initializes a Student
 * with the Student name from the Student file
 *
 * loadStudent() adds the Degree read from his
 * or her file to the Student 
 *
 * loadStudent() puts each Course read from lines 
 * onto the CourseBinaryTree and then adds each 
 * Course read to that Student's Vector of Elements
 *
 * loadStudent() then returns a pointer to the 
 * new Student
 *
 * and returns NULL for any error
 */
Student* loadStudent(char **lines, int numLinesInFile, CourseBinaryTree *courseTreePtr) {

	// checking for NULL pointer arguments
	if (lines == NULL) {
		printf("\nCannot load Student with a NULL "
				"string array argument, "
				"lines\n");
		return NULL;
	}
	if (numLinesInFile == 0) {
		printf("\nCannot load Student if there are "
				"no lines in the file!\n");
		return NULL;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot load Student with Course "
				"pointers with NULL "
				"CourseBinaryTree pointer!\n");
		return NULL;
	}
	// creating a pointer to Student
	Student *stuPtr = initStudent(lines[1]);
	setStudentDegree(stuPtr, lines[2]);
	// looping through student's completed courses
	for (int j = 3; j < numLinesInFile; j++) {
		if ( strcmp(lines[j], "") != 0) {
			// put course on the course tree
			Course* coursePtr = insertInCourseBinaryTree(courseTreePtr, lines[j]);
			// link student struct to that course
			addCompletedCourse(stuPtr, coursePtr);
		}
	}
	return stuPtr;
}


/*
 * printStudent() takes a Student pointer
 * as an argument
 *
 * printStudent() prints out all of the 
 * Student's information to the terminal
 */
void printStudent(Student* stuPtr) {

	// checking for NULL pointer argument
	if (stuPtr == NULL) {
		printf("\nCannot print Student information "
				"with NULL Student pointer "
				"argument\n");
		return;
	}

	printf("\nSTUDENT\n");
	printf("%s\n", stuPtr->name);
	printf("%s\n", stuPtr->degree);
	printVector(stuPtr->completedCourses);
}
