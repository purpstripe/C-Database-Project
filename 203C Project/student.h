/*
 *
 *	A header file for the Student ADT interface
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

#ifndef STUDENT_H
#define STUDENT_H

#include "coursePtrVector.h"
#include "courseBT.h"

// student struct definition
typedef struct student {
	char *name;
	char *degree;
	Vector *completedCourses;
} Student;


// interface

/*
 * initializes a Student with
 * the given Student name string
 *
 * returns a pointer to a Student
 * when complete
 *
 * returns NULL for error
 *
 * stuName - string for the Student's
 * name
 */
Student* initStudent(char* stuName);

/*
 * adds a Course to a Student's list
 * of completed Courses - using the
 * Student's Vector of Elements
 *
 * studentPtr - pointer to the 
 * Student we are adding a Course to
 *
 * coursePtr - pointer to the Course
 * we are adding
 */
void addCompletedCourse(Student* studentPtr, Course* coursePtr);

/*
 * initializes a Student with all
 * of the information read from a
 * formatted Student file, including
 * 	Student's name
 * 	Student's Degree
 * 	Student's completed Courses
 *
 * puts all new Courses read onto
 * the CourseBinaryTree
 *
 * returns a pointer to the new
 * Student for data member editing
 *
 * returns NULL for any error
 *
 * lines - a string array of lines
 * read from the Student file
 *
 * numLinesInFile - the number
 * of lines read from the Student
 * file
 *
 * courseTreePtr - pointer to the
 * CourseBinaryTree
 */
Student* loadStudent(char** lines, int numLinesInFile, CourseBinaryTree* courseTreePtr);

/*
 * prints all of a Student's 
 * information, including:
 * Student's name
 * Student's Degree
 * and Student's completed Courses
 *
 * stuPtr - pointer to the 
 * Student to print
 */
void printStudent(Student* stuPtr);

#endif
