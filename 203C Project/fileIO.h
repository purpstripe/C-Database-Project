/*
 *
 *	Header file for fileIO fuctions interface
 *	Functions for reading and processing 
 *	formatted Department, Degree, and Student
 *	files
 *	
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "courseBT.h"
#include "departmentVector.h"
#include "degreeVector.h"
#include "studentBT.h"

#include "student.h"

// interface

/* parses through formatted file
 * and loads all files of the file
 * into a string array of lines
 *
 * lines - an pointer to an empty 
 * string array to be filled 
 * by lines from the input file
 * 
 * fileName - name of the file we
 * want to open and read from in
 * current directory
 */
int fileParser(char*** lines, char* fileName);

/*
 * takes command line arguments
 * from the user, parses the formatted
 * files and processes each file line by
 * line by loading every Course mentioned
 * from Departments' available Courses,
 * Degrees' required Courses, Students'
 * completed Courses and prerequisite 
 * Courses into the CourseBinaryTree
 *
 * loads each Department's available
 * Courses as Course pointers into
 * the Department's Vector of Elements
 *
 * loads each Degree's required Courses
 * as Course pointers into the Degree's
 * Vector of Elements
 *
 * loads each Student's completed Courses
 * as Course pointers into the Student's
 * Vector of Elements
 *
 * argc - number of command line arguments
 *
 * argv - string array of command line
 * arguments
 *
 * courseTreePtr - pointer to the program's
 * central CourseBinaryTree
 *
 * depListPtr - pointer to the program's
 * DepartmentVector
 *
 * degListPtr pointer to the program's 
 * DegreeVector
 *
 * studentTreePtr - pointer to the 
 * StudentBinaryTree
 */
void handleCommandLineFileInput(int argc, char** argv, CourseBinaryTree* courseTreePtr, DepartmentVector* depListPtr, DegreeVector* degListPtr, StudentBinaryTree* studentTreePtr);

#endif
