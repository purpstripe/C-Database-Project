/*
 *
 *	C source file containing definitions of all of 
 *	the programs various command functions
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
 *	p - handleCmdP() (found in userInterface)
 *		c - findAndPrintCourse2()
 *		d - findAndPrintDepartment()
 *		g - findAndPrintDegree()
 *		s - findAndPrintStudent()
 *	q - removeCourseFromDegree()
 *	x - exit
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "courseBT.h"
#include "departmentVector.h"
#include "degreeVector.h"
#include "studentBT.h"
#include "programCommand.h"

/*
 * findAndPrintCourse() takes a query course name and 
 * CourseBinaryTree pointer as arguments
 * 
 * if found, findAndPrintCourse() prints the given Course's
 * information including the Course's title and its 
 * prerequisite Courses
 */
void findAndPrintCourse(CourseBinaryTree *courseTreePtr, char *queryCourseName) {

	// checking for NULL pointer arguments
	if (queryCourseName == NULL) {
		printf("\nCannot find and print Course "
				"information with no "
				"Course name string "
				"argument\n");
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot find and print %s Course "
				"information with NULL "
				"CourseBinaryTree pointer "
				"argument\n", queryCourseName);
		return;
	}
	
	// finding Course on CourseBinaryTree and printing
	// Course information with Course pointer
	CourseBTNode *courseNode = findInCourseBinaryTree(courseTreePtr->root, queryCourseName);
	if (courseNode == NULL) {
		printf("\nCOURSE NOT FOUND\n");
		return;
	}
	if (courseNode->coursePtr->title == NULL) {
		printf("NO COURSE TITLE ON RECORD\n");
	} else {
		printf("%s\n", courseNode->coursePtr->title);
	}
	printPrerequisites(courseNode->coursePtr);

	return;
}

/*
 * findAndPrintCourse2() takes a query course name and 
 * CourseBinaryTree pointer as arguments
 * 
 * if found, findAndPrintCourse2() prints the given Course's
 * information including the Course's Department, the Degrees
 * it belongs to and its prerequisite Courses
 */
void findAndPrintCourse2(CourseBinaryTree *courseTreePtr, char *queryCourseName) {

	// checking for NULL pointer arguments
	if (queryCourseName == NULL) {
		printf("\nCannot find and print Course "
				"information with no "
				"Course name string "
				"argument\n");
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot find and print %s Course "
				"information with NULL "
				"CourseBinaryTree pointer "
				"argument\n", queryCourseName);
		return;
	}

	// finding the Course on the CourseBinaryTree
	// and printing Course information with the
	// Course pointer
	CourseBTNode *courseNode = findInCourseBinaryTree(courseTreePtr->root, queryCourseName);
	if (courseNode == NULL) {
		printf("\nCOURSE NOT FOUND\n");
		return;
	}
	printf("department: ");
	if (courseNode->coursePtr->depName == NULL) {
		printf("NO DEPARTMENT ON RECORD\n");
	} else {
		printf("%s\n", courseNode->coursePtr->depName);
	}
	printf("degree: ");
	printCourseDegrees2(courseNode->coursePtr);
	printf("pre-requisites: ");
	printPrerequisites(courseNode->coursePtr);

	return;
}

/*
 * findAndPrintDegree() takes a query Degree name and a 
 * DegreeVector pointer as arguments
 *
 * if found, findAndPrintDegree() prints the given 
 * Degree's required Courses including both
 * conjunct and disjunct requirements
 */
void findAndPrintDegree(DegreeVector *degListPtr, char *queryDegreeName) {

	// checking for NULL pointer arguments	
	if (queryDegreeName == NULL) {
		printf("\nCannot find and print Degree "
				"information with no "
				"Degree name string "
				"argument\n");
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot find and print %s Degree "
				"information with NULL "
				"DegreeVector pointer "
				"argument\n", queryDegreeName);
		return;
	}

	// searching for given Degree in DegreeVector
	// and printing out Degree's Courses, if found
	Degree *foundDeg = findInDegreeVector(degListPtr, queryDegreeName);
	if (foundDeg == NULL) {
		printf("\nDEGREE NOT FOUND\n");
		return;
	}
	printf("\n%s Courses: \n", queryDegreeName);
	printVector(foundDeg->reqCourses);

	return;
	
}

/*
 * findAndPrintDepartment() takes a query Department name 
 * and a DepartmentVector pointer as arguments
 *
 * if found, findAndPrintDepartment() prints the given 
 * Department's available Courses
 */
void findAndPrintDepartment(DepartmentVector *depListPtr, char *queryDepartmentName) {
	
	// checking for NULL pointer arguments
	if (queryDepartmentName == NULL) {
		printf("\nCannot find and print Department "
				"information with no "
				"Department name string "
				"argument\n");
		return;
	}
	if (depListPtr == NULL) {
		printf("\nCannot find and print %s Department "
				"information with NULL "
				"DepartmentVector pointer "
				"argument\n", queryDepartmentName);
		return;
	}

	// searching for given Department in DepartmentVector
	// and printing the Department's Courses' names, if 
	// found
	Department *foundDep = findInDepartmentVector(depListPtr, queryDepartmentName);
	if (foundDep == NULL) {
		printf("\nDEPARTMENT NOT FOUND\n");
		return; 
	}
	printf("\n%s Department Courses: \n", queryDepartmentName);
	printDepartmentCourses(foundDep);

	return;
}

/*
 * findAndPrintStudent() takes a query Student name and
 * a StudentBinaryTree pointer arguments
 *
 * findAndPrintStudent() prints a Student's Degree 
 * program and completed Courses, if found
 */
void findAndPrintStudent(StudentBinaryTree *studentTreePtr, char *queryStudentName) {

	// checking for NULL pointer arguments
	if (queryStudentName == NULL) {
		printf("\nCannot find and print Student "
				"information with no "
				"Student name string "
				"argument\n");
		return;
	}
	if (studentTreePtr == NULL) {
		printf("\nCannot find and print %s's "
				"information with NULL "
				"StudentBinaryTree "
				"pointer argument\n",
				queryStudentName);
		return;
	}

	// searching StudentBinaryTree for given Student
	// with queryStudentName and printing
	// the Student's information, if found
	StudentBTNode *studentNode = findInStudentBinaryTree(studentTreePtr->root, queryStudentName);
	if (studentNode == NULL) {
		printf("\nSTUDENT NOT FOUND\n");
		return;
	}

	printf("degree: ");
	if (studentNode->studentPtr->degree == NULL) {
		printf("NO DEGREE ON RECORD\n");
	} else {
		printf("%s\n", studentNode->studentPtr->degree);
	}

	Vector *studentCoursesPtr = studentNode->studentPtr->completedCourses;
	printf("completed: ");
	int numCompletedCourses = studentCoursesPtr->numElements;
	if (numCompletedCourses == 0) {
		printf("NO COMPLETED COURSES\n");
		return;
	}

	printf("%s", studentCoursesPtr->elements[0].course->name); 
	for (int i = 1; i < numCompletedCourses; i++) {
		printf(", %s", studentCoursesPtr->elements[i].course->name); 
	}
	printf("\n");

	return;
}

/*
 * effectOfCompletedCourse() takes a pointer to the CourseBinaryTree and 
 * a Course name string as arguments and prints all Courses with the 
 * given Course listed as a prerequisite Course and prints all the 
 * Degrees that the given Course belongs to - effectively showing the
 * effect of completing the given Course
 */
void effectOfCompletedCourse(CourseBinaryTree *courseTreePtr, char *queryCourseName) {

	// checking for NULL pointer arguments
	if (queryCourseName == NULL) {

		printf("\nCannot show the effect of taking "
				"a Course with a no "
				"Course name argument\n");
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot show the effect of taking "
				"the Course %s with NULL "
				"CourseBinaryTree pointer "
				"argument\n", queryCourseName);
		return;
	}

	// printing all Courses with queryCourseName as a prerequisite
	printAllCoursesWithPrerequisite(courseTreePtr, queryCourseName);

	// finding pointer to the Course with name queryCourseName on the 
	// CourseBinaryTree
	CourseBTNode *givenCourseNodePtr = findInCourseBinaryTree(courseTreePtr->root, queryCourseName);

	if (givenCourseNodePtr == NULL) {

		printf("\nCannot show effect of taking the "
				"Course %s without the "
				"affiliated CourseBTNode "
				"on the CourseBinaryTree\n",
			       	queryCourseName);
		// prompt user to put Course on the tree
		printf("Use the 'a' command to add %s to "
				"the system\n",
				queryCourseName);
		return;
	}

	// printing all Degrees that the Course queryCourseName belongs to
	printCourseDegrees(givenCourseNodePtr->coursePtr);
	return;
}

/*
 * addCourseToDepartment() takes a CourseBinaryTree pointer,
 * DepartmentVector, an array of strings from the user's
 * command, and the number of strings to be processed from
 * the user's command
 *
 * addCourseToDepartment() finds/inserts a Course into the
 * CourseBinaryTree, updates the Course's title, prerequisite
 * Courses, and Department name
 *
 * addCourseToDepartment() searches the DepartmetVector for
 * a Department with the specified Department name
 * 	if not found, the Department is initialized
 * 	
 * the Department is checked for a Course with the given 
 * Course name
 * 	if not found, then the Course is added to the 
 * 	Department
 *
 * lastly, the Department's information is printed to the
 * terminal
 */
void addCourseToDepartment(CourseBinaryTree *courseTreePtr, DepartmentVector *depListPtr, char ***userInputArrayPtr, int numStrings) {

	// checking for NULL pointer arguments and
	// valid user input
	if (userInputArrayPtr == NULL) {
		printf("\nCannot add Course to a Department "
				"without the Department "
				"name, Course name, and "
				"Course title\n");
		return;
	}

	if (numStrings < 3) {
		printf("\nCannot add Course to a Department "
				"with too few arguments\n");
		return;
	}
	// labeling input
	char *departmentName = (*userInputArrayPtr)[0];
	if (departmentName == NULL) {
		printf("\nCannot add a Course to a "
				"Department without a"
				"Department name "
				"argument\n");
		return;
	}
	char *courseName = (*userInputArrayPtr)[1];
	if (courseName == NULL) {
		printf("\nCannot add a Course to the "
				"%s Department without a "
				"Course name argument\n",
				departmentName);
		return;
	}
	char *courseTitle = (*userInputArrayPtr)[2];
	if (courseTitle == NULL) {
		printf("\nCannot add the %s Course to the "
				"%s Department without a "
				"Course title argument\n",
				courseName, departmentName);
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot add the %s Course to the "
				"%s Department with a "
				"NULL CourseBinaryTree pointer "
				"argument\n",
				courseName, departmentName);
		return;
	}
	if (depListPtr == NULL) {

		printf("\nCannot add the %s Course to the "
				"%s Department with a "
				"NULL DepartmentVector pointer "
				"argument\n",
				courseName, departmentName);
		return;
	}


	// finding/creating Course pointer and CourseBTNode with name courseName
	Course* coursePtr = insertInCourseBinaryTree(courseTreePtr, courseName);
	// filling Course data members
	coursePtr->title = courseTitle;
	
	// course has prereqs
	if (coursePtr->firstPrereq != NULL) {
		// clearing all current prereqs
		clearCoursePrerequisites(coursePtr);	
	}

	if (numStrings > 3) {
		// appending prereqs - checking first prereq for "OR"
		if ( (*userInputArrayPtr)[3][0] == 'O' && (*userInputArrayPtr)[3][1] == 'R' && (*userInputArrayPtr)[3][2] == ' ') {
			// putting "OR" into list of prereqs as a flag
			appendPrereqToCourse(coursePtr, "OR");
			// moving character pointer past "OR"
			(*userInputArrayPtr)[3] += 3;
		}
		
		// appending new prerequisites
		for (int i = 3; i < numStrings; i++) {
			char *prereqName = (*userInputArrayPtr)[i];
			appendPrereqToCourse(coursePtr, prereqName);
		}

	}

	coursePtr->depName = departmentName;
	Department* depPtr = findInDepartmentVector(depListPtr, departmentName);
	// new department if its not listed --> if findDep returns NULL
	if (depPtr == NULL) {
		depPtr = initDepartment(departmentName);
		addDepartment(depListPtr, depPtr);
	}	
	// Course not found in Department's Vector
	if (findCoursePtrInVector(depPtr->depCourses, courseName) == NULL) {
		// adding Course pointer to Department ADT
		addDepartmentCourse(depPtr, coursePtr);
	}

	printDepartment(depPtr);

	return;
}

/*
 * studentCoursesStillNeeded() takes a Student name as string argument,
 * a DegreeVector pointer as an argument, and a StudentBinaryTree pointer
 * as an argument
 *
 * studentCoursesStillNeeded() searches the StudentBinaryTree with 
 * the given Student name, queryStudentName, for a Student pointer
 *
 * if the Student is found, then the Student's Degree name is used
 * to search the DegreeVector for a pointer to his or her Degree
 *
 * with access to the Student's completed Courses and the Degree's
 * required Courses, printDifferingCourses() is used to print all
 * of the Courses the Degree program contains that the Student has
 * not yet completed - the Courses the Student still needs to complete
 * for his or her Degree program
 *
 */
void studentCoursesStillNeeded(DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr, char *queryStudentName) {

	// checking for NULL pointer arguments
	if (queryStudentName == NULL) {
		printf("\nCannot print Courses a Student still "
				"needs to complete for his or "
				"her Degree program with no "
				"Student name argument\n");
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot print Courses %s still "
				"needs to complete for his "
				"or her Degree program with "
				"NULL DegreeVector pointer "
				"argument\n", queryStudentName);
		return;
	}
	if (studentTreePtr == NULL) {
		printf("\nCannot print Courses %s still "
				"needs to complete for his "
				"or her Degree program with "
				"NULL StudentBinaryTree pointer "
				"argument\n", queryStudentName);
		return;
	}

	// searching StudentBinaryTree for Student with 
	// the given Student name, queryStudentName
	StudentBTNode *givenStudentNodePtr = findInStudentBinaryTree(studentTreePtr->root, queryStudentName);

	if (givenStudentNodePtr == NULL) {
		printf("\nCannot print Courses %s still "
				"needs to complete for his or "
				"her Degree program with no "
				"StudentBTNode pointer found "
				"in StudentBinaryTree\n", 
				queryStudentName);
		return;
	}
	// Student found - searching for Student's Degree
	char *studentDegreeName = givenStudentNodePtr->studentPtr->degree;	
	Degree* studentDegreePtr = findInDegreeVector(degListPtr, studentDegreeName);

	if (studentDegreePtr == NULL) {
		printf("\nSTUDENT DEGREE %s NOT FOUND IN DEG LIST\n", studentDegreeName);
		return;
	}

	Vector *degreeCourses = studentDegreePtr->reqCourses;
	Vector *stuCompletedCourses = givenStudentNodePtr->studentPtr->completedCourses;
	// loop through all of the Degree courses and check if they are in the Student's
	// printing all Courses in the Degree program and not in the Student's completed
	// Course list
	int numCoursesNeeded = printDifferingCourses(degreeCourses, stuCompletedCourses);
	if (numCoursesNeeded == 0) {
		printf("\n%s has all Degree requirements fulfilled\n", queryStudentName);
	}

	return;
}

/*
 * showAvailableCoursesForStudent() takes a DegreeVector pointer,
 * StudentBinaryTree pointer, and Student name string as arguments
 *
 * showAvailableCoursesForStudent() searches the StudentBinaryTree
 * for a Student with the given name, queryStudentName
 *
 * if found, then the DegreeVector is searched for the Student's
 * Degree program
 *
 * if found, then each of the prerequisites of the Courses
 * in the Student's Degree program are compared to the Student's
 * completed Courses
 *
 * if completed Courses are found to satisfy Degree Courses'
 * prereq requirements, then the available Course for the Student
 * is printed 
 */
void showAvailableCoursesForStudent(DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr, char *queryStudentName) {

	// checking for NULL pointer arguments
	if (queryStudentName == NULL) {
		printf("\nCannot show available Courses for "
				"a Student in his or her "
				"Degree program without a "
				"Student name argument\n");
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot show available Courses for "
				"%s in his or her Degree "
				"program with a NULL "
				"DegreeVector pointer "
				"argument\n",
				queryStudentName);
		return;
	}
	if (studentTreePtr == NULL) {
		printf("\nCannot show available Courses for "
				"%s in his or her Degree "
				"program with a NULL "
				"StudentBinaryTree pointer "
				"argument\n",
				queryStudentName);
		return;
	}

	// searching for Student with name queryStudentName and
	// searching for Student's Degree program
	StudentBTNode* studentNodePtr = findInStudentBinaryTree(studentTreePtr->root, queryStudentName);
	if (studentNodePtr == NULL) {
		printf("\nStudent %s does not exist in the "
				"StudentBinaryTree\n", 
				queryStudentName);
		return;
	}
	
	char *studentDegreeName = studentNodePtr->studentPtr->degree;
	Degree* studentDegreePtr = findInDegreeVector(degListPtr, studentDegreeName);
	if (studentDegreePtr == NULL) {
		printf("\nStudent's Degree %s is not in the "
				"DegreeVector\n", 
				studentDegreeName);
		return;
	}

	// with each of the Student's completed Courses, loop through all 
	// of the Courses from the Student's Degree and compare their
	// completed Course to the prerequisite Courses of each of the 
	// Degree Courses
	// if a completed Course is found to be a prerequisite for a 
	// Degree Course then print the name of the Degree Course

	Vector *completedCourses = studentNodePtr->studentPtr->completedCourses;
	Vector *degreeCourses = studentDegreePtr->reqCourses;
	printAvailableCourses(degreeCourses, completedCourses);
	
	return;	
}

/*
 * removeCourseFromDegree() takes a DegreeVector pointer and 
 * an array of user command strings as arguments
 *
 * removeCourseFromDegree() searches for a Degree with the
 * user's Degree name input
 *
 * if found, then the Degree is checked for the user's
 * input Course name string
 *
 * if found, the Course is removed from the Degree's
 * Vector of Elements and the updated Degree is printed
 * to the terminal
 */
void removeCourseFromDegree(DegreeVector *degListPtr, char **userInputArray) {

	// checking for NULL pointer arguments
	if (userInputArray == NULL) {
		printf("\nCannot remove Course from "
				"Degree program without "
				"the Degree name and "
				"Course name "
				"arguments\n");
		return;
	}
	char *degreeName = userInputArray[0];
	if (degreeName == NULL) {
		printf("\nCannot remove Course from "
				"Degree program without "
				"the Degree name "
				"argument\n");
		return;
	}
	char *courseName = userInputArray[1];
	if (courseName == NULL) {
		printf("\nCannot remove Course from "
				"%s Degree program "
				"without the Course "
				"name argument\n",
				degreeName);
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot remove %s from "
				"%s Degree program "
				"with NULL "
				"DegreeVector pointer "
				"argument\n",
				courseName, degreeName);
		return;
	}

	// finding the Degree in Vector
	Degree *degPtr = findInDegreeVector(degListPtr, degreeName);
	
	if (degPtr != NULL) {	
		// removing Degree information from Course
		Course *coursePtr = findCoursePtrInVector(degPtr->reqCourses, courseName);
		if (coursePtr != NULL) {
			removeFromLinkedList( &(coursePtr->firstDegree), degreeName );
		} else {
			printf("\nCOURSE NOT FOUND IN DEGREE\n");
		}
		// removing Course pointer from Degrees
		removeCoursePtrFromVector(degPtr->reqCourses, courseName);
		printDegree(degPtr);
	} else {
		printf("\nDEGREE NOT FOUND\n");
	}

	return;
}

/*
 * removeCourseFromAll() takes a CourseBinaryTree pointer,
 * DepartmentVector pointer, DegreeVector pointer, 
 * StudentBinaryTree pointer, and string array of the 
 * user's input as arguments
 *
 * removeCourseFromAll() clears a given Course of all
 * of its information and removes it from all
 * Departments, Degrees, Students, and the main
 * CourseBinaryTree
 *
 * removeCourseFromAll() prints every updated
 * Department, Degree, and Student to the terminal 
 */
void removeCourseFromAll(CourseBinaryTree *courseTreePtr, DepartmentVector *depListPtr, DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr, char **userInputArray) {

	// checking for NULL pointer arguments
	if (userInputArray == NULL) {
		printf("\nCannot remove Course from "
				"the given Department, "
				"all Degrees, all "
				"prerequisites, and all "
				"Students' completed Courses "
				"with no Department name "
				"and no Course name "
				"arguments\n");
		return;
	}
	char *departmentName = userInputArray[0];
	if (departmentName == NULL) {
		printf("\nCannot remove Course from "
				"the given Department, "
				"all Degrees, all "
				"prerequisites, and all "
			      	"Students' completed Courses "
				"with no Department name "
				"argument\n");
		return;
	}
	char *courseName = userInputArray[1];
	if (courseName == NULL) {
		printf("\nCannot remove Course from "
				"the %s Department, "
				"all Degrees, all "
				"prerequisites, and "
			       	"all Students's completed "
				"Courses without the "
				"Course name argument\n",
				departmentName);
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot remove %s from the %s "
				"Department, all Degrees, all "
				"prerequisites, and all "
			       	"Students' completed Courses "
				"with NULL CourseBinaryTree "
				"pointer argument\n", 
				courseName, departmentName);
		return;
	}
	if (depListPtr == NULL) {
		printf("\nCannot remove %s from the %s "
			       "Department, all Degrees, all "
			       "prerequisites, and all "
			       "Students' completed Courses "
			       "with a NULL DepartmentVector "
			       "pointer argument\n", 
			       courseName, departmentName);	       
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot remove %s from the %s "
			       "Department, all Degrees, all "
			       "prerequisites, and all "
			       "Students' completed Courses "
			       "with a NULL DegreeVector "
			       "pointer argument\n", 
			       courseName, departmentName);	       
		return;
	}
	if (studentTreePtr == NULL) {
		printf("\nCannot remove %s from the %s "
				"Department, all Degrees, all "
				"prerequisites, and all "
			       	"Students' completed Courses "
				"with NULL StudentBinaryTree "
				"pointer argument\n",
			       	courseName, departmentName);
		return;
	}
	
	// remove Department and Degree information from the Course
	Department *depPtr = findInDepartmentVector(depListPtr, departmentName);
	if (depPtr == NULL) {
		printf("\nDEPARTMENT NOT FOUND\n");
		return;
	}

	if (courseTreePtr->root == NULL) {
		printf("\nCannot remove %s from the %s "
				"Department, all Degrees, all "
				"prerequisites, and all "
			       	"Students' completed Courses "
				"with an empty CourseBinaryTree\n",
			       	courseName, departmentName);
		return;
	}
	CourseBTNode *courseNode = findInCourseBinaryTree(courseTreePtr->root, courseName);
	if (courseNode == NULL) {
		printf("\nCOURSE NOT FOUND\n");
		return;
	}
	Course *coursePtr = courseNode->coursePtr;
	coursePtr->title = NULL;
	coursePtr->depName = NULL;
	clearLinkedList( &(coursePtr->firstDegree) );
	clearLinkedList( &(coursePtr->firstPrereq) );

	// remove Course pointer from the Department and all Degrees
	removeCoursePtrFromVector(depPtr->depCourses, courseName);
	// remove Course name from all prerequisites
	removeCourseFromAllPrereqs(courseTreePtr, courseName);
	// print department
	printDepartment(depPtr);

	for (int i = 0; i < degListPtr->numDegs; i++) {
		Degree *degPtr = degListPtr->degrees+i;
		if ( findCoursePtrInVector(degPtr->reqCourses, courseName) != NULL) {
			removeCoursePtrFromVector(degPtr->reqCourses, courseName);
			// print degree
			printDegree(degPtr);
		}
	}

	// remove from Student's completed Courses
	removeCompletedCourseFromAllStudents(studentTreePtr, courseName);

	// remove Course from the Binary Tree
	removeFromCourseBinaryTree(courseTreePtr, courseName);
	
	return;

}
