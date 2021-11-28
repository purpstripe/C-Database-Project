/*
 *
 *	C source code for the main file of this project
 *
 */

// include directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileIO.h"

#include "courseBT.h"
#include "departmentVector.h"
#include "degreeVector.h"
#include "studentBT.h"

#include "userInterface.h"

int main(int argc, char *argv[]) {


	// initializing course tree
	CourseBinaryTree *courseTree = createCourseBinaryTree();
	// initializing depListPtr to point to our department list (vector) 
	DepartmentVector *depListPtr = initDepartmentVector();
	// initialize degree vector	
	DegreeVector *degListPtr = initDegreeVector();
	// initialize student tree
	StudentBinaryTree *studentTree = createStudentBinaryTree();

		

	// pass the  memory address of the dep vector and degree vector as arguments!
	// update their values in the function (dereference) 
	handleCommandLineFileInput(argc, argv, courseTree, depListPtr, degListPtr, studentTree);

	// printing the departments, degrees, and students passed into the program	
	for (int i = 0; i < depListPtr->numDeps; ++i) {
		printDepartment(depListPtr->departments + i);
	}

	
	for (int j = 0; j < degListPtr->numDegs; ++j) {
		printDegree(degListPtr->degrees + j);
	}

	printStudentBinaryTreeInOrder(studentTree->root);

	// prompting and handling user commands!
	char *userInput;
	char firstChar;
	do {
		userInput = NULL;
		printf("\nEnter a command (c, d, s, a, m, n, r, p, q, x)\n");
		printf("p takes an additional command: (p) c, d, g, s\n\n");
		firstChar = getUserInput(&userInput);
		processUserInput(firstChar, &userInput, courseTree, depListPtr, degListPtr, studentTree);
		free(userInput);
	} while(firstChar != 'x');

	// freeing heap space

	free(studentTree);
	studentTree = NULL;

	free(depListPtr->departments->depCourses->elements);
	depListPtr->departments->depCourses->elements = NULL;

	free(depListPtr->departments->depCourses);
	depListPtr->departments->depCourses = NULL;
	
	free(depListPtr->departments);
	depListPtr->departments = NULL;

	free(depListPtr);
	depListPtr = NULL;

	free(degListPtr->degrees->reqCourses->elements);
	degListPtr->degrees->reqCourses->elements = NULL;

	free(degListPtr->degrees->reqCourses);	
	degListPtr->degrees->reqCourses = NULL;

	free(degListPtr->degrees);
	degListPtr->degrees = NULL;

	free(degListPtr);
	degListPtr = NULL;
	
	free(courseTree);
	courseTree = NULL;
	return 0;
}
