/*
 *
 *	C source file for functions to handle 
 *	user commands within the program
 *
 */

// include directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "courseBT.h"
#include "departmentVector.h"
#include "degreeVector.h"
#include "studentBT.h"

#include "stringFunctions.h"
#include "userInterface.h"
#include "programCommand.h"

#define MAX_STRING_LEN 100

/*
 * getUserInput() takes a string pointer as
 * its argument
 *
 * getUserInput() allocates heap space
 * for a user's input command string
 *
 * getUserInput() get the user's command
 * string from the command line and removes 
 * the new line character
 * 
 * getUserInput() removes the first
 * character from the user's input
 * for the program's function switch
 * statement
 * 
 * the rest of the command string is 
 * linked to the string pointer
 * argument for use outside of this 
 * function
 *
 * getUserInput() returns the 
 * command character
 */
char getUserInput(char **userInputPtr) {

	// checking for NULL pointer argument
	if (userInputPtr == NULL) {
		printf("\nCannot get user input if the user's command is null\n");
		return -1;
	}

	char *userInput = (char*) calloc(MAX_STRING_LEN, sizeof(char));
	if (userInput == NULL) {
		printf("\nFailed to allocate heap space for user command input\n");
		return -1;
	}

	// getting input from the user
	fgets(userInput, MAX_STRING_LEN, stdin);
	int inputLen = strlen(userInput);
	if (inputLen == (MAX_STRING_LEN - 1)) {
		printf("\nUser input exceeded maximum number of characters\n");
		return -1;
	}
	// replacing the newline character from user input with
	// a null character to end the string
	if (userInput[inputLen - 1] == '\n') {
		userInput[inputLen - 1] = '\0';
	}
	// getting user's command character
	// and linking command string	
	char firstChar = removeCommandChar(&userInput);
	*userInputPtr = userInput;
	return firstChar;
}

/*
 * handleCmpP() takes a pointer to a string,
 * userInputPtr, a CourseBinaryTree pointer,
 * courseTreePtr, a DepartmentVector pointer,
 * depListPtr, a DegreeVector pointer,
 * degListPtr, and a StudentBianryTree
 * pointer, studentTreePtr
 *
 * handleCmdP() handles all user input 
 * starting with the 'p' command
 *
 * handleCmdP() gets the second command 
 * character from the user's string
 */
void handleCmdP(char **userInputPtr, CourseBinaryTree *courseTreePtr, DepartmentVector *depListPtr, DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr) {
	// new command character for p commands
	char commandChar = removeCommandChar(userInputPtr);	
	// handling cases depending on user input
	switch( commandChar ) {

		case 'c' :
			findAndPrintCourse2(courseTreePtr, *userInputPtr);
			break;

		case 'd' :
			findAndPrintDepartment(depListPtr, *userInputPtr);
			break;
			
		case 'g' :
			findAndPrintDegree(degListPtr, *userInputPtr);
			break;

		case 's' :
			findAndPrintStudent(studentTreePtr, *userInputPtr);
			break;

		default :
			printf("\nwrong input command!\n");
	}
	// shifting userInput back to original location (from removeCommandChar)
	*userInputPtr -= 2;
	return;
}

/*
 * processUserInput() takes a command character from the user,
 * the rest of the string input, a reference to the 
 * CourseBinaryTree, a reference to the list of Departments, 
 * a reference to the list of Degrees, and a reference to the 
 * the Student binary tree as arguments
 *
 * processUserInput() parses the user's command while the program is running
 * and executes the appropriate functions
 * this includes updating data structures, printing information, and more 
 */
void processUserInput(char commandChar, char **userInputPtr, CourseBinaryTree *courseTreePtr, DepartmentVector *depListPtr, DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr) {

	char **stringArray = NULL;
	int numStrings = 0;

	switch( commandChar ) {
		case 'c' :
			findAndPrintCourse(courseTreePtr, *userInputPtr);
			break;

		case 'd' :
			findAndPrintDegree(degListPtr, *userInputPtr);
			break;
			
		case 's' :
			// effect of taking a course
			effectOfCompletedCourse(courseTreePtr, *userInputPtr);
			break;
		case 'a' :
			// add course to given department
			stringArray = NULL;
			numStrings = splitStringAtComma(*userInputPtr, &stringArray);
			addCourseToDepartment(courseTreePtr, depListPtr, &stringArray, numStrings);
			break;
		case 'm' :
			// student required courses
			studentCoursesStillNeeded(degListPtr, studentTreePtr, *userInputPtr);
			break;
		case 'n' :
			// student available courses
			showAvailableCoursesForStudent(degListPtr, studentTreePtr, *userInputPtr);
			break;
		case 'r' :
			// remove course
			stringArray = NULL;
			numStrings = splitStringAtComma(*userInputPtr, &stringArray);
			removeCourseFromAll(courseTreePtr, depListPtr, degListPtr, studentTreePtr, stringArray);
			break;
		case 'p' :
			handleCmdP(userInputPtr, courseTreePtr, depListPtr, degListPtr, studentTreePtr);
			break;
		case 'q' :
			// remove course from degree
			stringArray = NULL;
			numStrings = splitStringAtComma(*userInputPtr, &stringArray);
			removeCourseFromDegree(degListPtr, stringArray);
			break;
		case 'x' :
			printf("\nExiting...\n");
			break;
		default :
			printf("\nwrong input command!\n");
	}

	// shifting userInput back to original location (from removeCommandChar)
	*userInputPtr -= 2;
	return;
}
