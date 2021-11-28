/*
 *
 *	Header file containing all of the function 
 *	prototypes/signatures for each program command
 *
 *	each function below handles one of the user's
 *	possible commands including:
 *	c - findAndPrintCourse()
 *	d - findAndPrintDegree()
 *	s - effectOfCompletedCourse()
 *	a - addCourseToDepartment()
 *	m - studentCoursesStillNeeded()
 *	n - showAvailableCoursesForStudent()
 *	r - removeCourseFromAll()
 *	p - handleCmdP()
 *		c - findAndPrintCourse2()
 *		d - findAndPrintDepartment()
 *		g - findAndPrintDegree()
 *		s - findAndPrintStudent()
 *	q - removeCourseFromDegree()
 *	x - exit
 */

#ifndef PROGRAMCOMMAND_H
#define PROGRAMCOMMAND_H

// interface

/*
 * searches the CourseBinaryTree for a particular
 * Course with the Course name argument and 
 * prints the Course's title and  prerequisites
 * if it is found
 *
 * courseTreePtr - pointer to the CourseBinaryTree
 * we search for the Course of name queryCourseName
 *
 * queryCourseName - string name of the Course we
 * are searching for and printing
 */
void findAndPrintCourse(CourseBinaryTree* courseTreePtr, char* queryCourseName);

/*
 * searches the CourseBinaryTree for a particular
 * Course with the Course name argument and 
 * prints the Course's Department, Degree programs,
 * and prerequisites if it is found
 *
 * courseTreePtr - pointer to the CourseBinaryTree
 * we search for the Course of name queryCourseName
 *
 * queryCourseName - string name of the Course we
 * are searching for and printing
 */
void findAndPrintCourse2(CourseBinaryTree* courseTreePtr, char* queryCourseName);

/*
 * searches the DegreeVector for a particular
 * Degree with the Degree name argument and
 * prints the Degree's conjunct and disjunct
 * Course requirements to the terminal, if it 
 * is found
 *
 * degListPtr - pointer to the DegreeVector we
 * want to search
 *
 * queryDegreeName - string name of the Degree
 * we want to find and print
 */
void findAndPrintDegree(DegreeVector* degListPtr, char* queryDegreeName);

/*
 * searches the DepartmentVector for a 
 * particular Department with the Department
 * name argument and prints the Department's
 * available Courses; including, each Course's
 * name, title, and prerequisite Courses
 *
 * depListPtr - pointer to the DepartmentVector
 * we want to search
 *
 * queryDepartmentName - string name of the 
 * Department we want to find and print
 */
void findAndPrintDepartment(DepartmentVector* depListPtr, char* queryDepartmentName);

/*
 * searches the StudentBinaryTree for a
 * particular Student with the Student
 * name argument and prints the Student's
 * information including the Student's
 * Degree program and a list of their
 * completed Courses
 *
 * studentTreePtr - pointer to the 
 * StudentBinaryTree we search
 * 
 * queryStudentName - string name of the 
 * Student we are searching for and, if 
 * found, printing
 */
void findAndPrintStudent(StudentBinaryTree* studentTreePtr, char* queryStudentName);

/*
 * prints the effect of taking the Course
 * specified by the Course name argument taken
 * from the user's input string; including, the
 * Courses made available from taking a Course,
 * the Courses whose requirements are partially
 * complete by taking said Course, and the Degree
 * programs to which the given Course belongs
 *
 * courseTreePtr - pointer to the tree we search
 *
 * queryCourseName - name of the Course we search
 * for and print the effect of completing
 */
void effectOfCompletedCourse(CourseBinaryTree* courseTreePtr, char* queryCourseName);

/*
 * adds a Course by name to a specified Department
 * from the user input
 *
 * the specified Course is found/added to the 
 * CourseBinaryTree by Course name
 *
 * updates the Course's information including its
 * title, prerequisite Courses, and Department name
 *
 * if the Department specified is not found, 
 * then it is initialized and added to the
 * DeparmentVector
 *
 * it the Course is not found in the Department's
 * list of available Courses, then the Course is
 * added to the Department's list of available
 * Courses
 *
 * lastly, the Department's information is printed 
 * to the terminal
 *
 * courseTreePtr - pointer to the CourseBinaryTree
 * we search for with the given Course name
 * 
 * depListPtr - pointer to the DepartmentVector
 * we search for with the given Department name
 *
 * userInputArrayPtr - pointer to the array of
 * user input strings including information
 * needed like the Course name, Department name, 
 * and more
 *
 * numStrings - the number of strings stored in 
 * the userInputArray
 */
void addCourseToDepartment(CourseBinaryTree* courseTreePtr, DepartmentVector* depListPtr, char*** userInputArrayPtr, int numStrings);

/*
 * prints all Courses in the given Student's 
 * Degree program that are not in the 
 * Student's list of completed Courses,
 * effectively showing the Courses the 
 * Student still neededs to complete in his
 * or her Degree program
 *
 * degListPtr - pointer to the DegreeVector
 * we search for the given Student's 
 * Degree program
 *
 * studentTreePtr - pointer to the 
 * StudentBinaryTree we search for
 * the Student with name 
 * queryStudentName
 *
 * queryStudentName - string name for
 * the Student whose needed Courses we 
 * want to print
 */
void studentCoursesStillNeeded(DegreeVector* degListPtr, StudentBinaryTree* studentTreePtr, char* queryStudentName);

/*
 * prints all of the available Courses for a 
 * given Student based off of his or her Degree
 * program, his or her completed Courses, and
 * the prerequisite requirements that those
 * completed Courses fulfill 
 * 
 * this function prints a Student's available 
 * Courses from their Degree program separated
 * by new lines
 *
 * degListPtr - pointer to the DegreeVector
 * we search for the given Student's 
 * Degree program
 *
 * studentTreePtr - pointer to the 
 * StudentBinaryTree we search for
 * the Student with name 
 * queryStudentName
 *
 * queryStudentName - string name for
 * the Student whose available Coruses
 * we want to print
 */
void showAvailableCoursesForStudent(DegreeVector* degListPtr, StudentBinaryTree* studentTreePtr, char* queryStudentName);

/*
 * removes a Course with the given Course name
 * from the Degree with the given Degree name
 *
 * this includes removing Degree information
 * from the Course and then removing the 
 * Course pointer and its Element from the 
 * Degree's Vector of Elements
 *
 * lastly, prints the Degree from which the
 * Course was removed
 *
 * degListPtr - pointer to the DegreeVector
 * we want to remove the given Course from
 *
 * userInputArray - the string array containing
 * the Degree name and Course name needed
 */
void removeCourseFromDegree(DegreeVector* degListPtr, char** userInputArray);

/*
 * clears a given Course of all of its information 
 * and removes it from all Departments, Degrees, 
 * Students, and the main CourseBinaryTree
 *
 * prints every updated Department, Degree, and 
 * Student to the terminal
 *
 * courseTreePtr - pointer to the CourseBinaryTree
 * we want to search and remove a Course from
 *
 * depListPtr - pointer to the DepartmentVector
 * we want to search and remove a Course from
 *
 * degListPtr - pointer to the DegreeVector 
 * we want to search and remove a Course from
 *
 * studentTreePtr - pointer to the 
 * StudentBinaryTree we want to remove a 
 * Course from
 *
 * userInputArray - array of strings needed
 * to perform this function, including the
 * Department name and Course name
 */
void removeCourseFromAll(CourseBinaryTree* courseTreePtr, DepartmentVector* depListPtr, DegreeVector* degListPtr, StudentBinaryTree* studentTreePtr, char** userInputArray);

#endif
