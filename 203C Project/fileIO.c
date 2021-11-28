/*
 *
 *	C source file containing functions associated with 
 *	reading from the various formatted files
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileIO.h"

#define MAX_NUM_CHARS 100
#define MAX_NUM_LINES 500

/*
 * fileParser() takes the input file name and an empty array 
 * for strings to be read from the formatted file
 * fileParser() reads from the file fileName and puts each line into 
 * the string array, lines
 * fileParser() returns the number of lines read
 */
int fileParser(char ***lines, char *fileName) {

	// checking for NULL pointer arguments
	if (fileName == NULL) {
		printf("\nCannot load lines from given "
				"file with no file name "
				"argument\n");
		return -1;
	}

	// opening file and returning a file pointer
	FILE *filePtr = fopen(fileName, "r");

	// checking if pointer for array of strings, lines, is valid
	if (lines == NULL) {
		printf("\nCannot load lines from %s with "
				"NULL string array "
				"pointer, lines\n", fileName);
		return -1;
	}

	// checking is the file pointer is valid
	if (filePtr == NULL) {
		printf("\nFile pointer is NULL\n");
		printf("Check spelling and see if the "
				"file, %s, is in the "
				"working "
				"directory\n", fileName);
		fflush(stdout);
		return -1;
	}

	// creating a temporary string buffer
	char stringBuffer[MAX_NUM_LINES][MAX_NUM_CHARS + 1];
	int lineLen = 0;
	int i = 0;
	while ( !feof(filePtr) ) {
		// loading file lines into buffer and removing new line char
		fgets(stringBuffer[i], MAX_NUM_LINES, filePtr);
		lineLen = strlen(stringBuffer[i]);
		if (stringBuffer[i][lineLen - 1] == '\n') {
			stringBuffer[i][lineLen - 1] = '\0';
		}
		i++;
	}

	// loops lines + 1 times at EOF
	int numLines = i - 1;

	// place-holder for lines array
	char **linesArr;
	linesArr = (char**) calloc(numLines, sizeof(char*));
	// assigning address for return pointer lines
	*lines = linesArr;

	for (int j = 0; j < numLines; ++j) {
		linesArr[j] = strdup(stringBuffer[j]);
	}	


	// closing file - no more file pointer
	fclose(filePtr);
	// returns number of lines in the flie
	return numLines;
}


/*
 * handleCommandLineFileInput() takes the command line
 * arguments, argv, the number of command line arguments,
 * argc, a pointer to the CourseBinaryTree, a pointer to
 * the DepartmentVector, a pointer to the DegreeVector,
 * and a pointer to the StudentBinaryTree as arguments
 *
 * first, handleCommandLineFileInput() parses through
 * each formatted file and loads each line of
 * each file into an array of strings 
 *
 * handleCommandLineFileInput() first loads all read
 * Courses from the string array into the CourseBinaryTree
 * with as much Course information as possible
 *
 * for all Department files, the function loads the 
 * Deparment's available Courses as Course pointers
 * into the Department's Vector of Elements
 *
 * for all Degree files, the function loads the 
 * Degree's required Courses as Course pointers
 * into the Degree's Vector of Elements
 *
 * lastly, for all Student files, the function
 * loads the Student's completed Courses as
 * Course pointers into the Student's Vector
 * of Elements
 */
void handleCommandLineFileInput(int argc, char **argv, CourseBinaryTree *courseTreePtr, DepartmentVector *depListPtr, DegreeVector *degListPtr, StudentBinaryTree *studentTreePtr) {

	// checking for NULL pointer arguments
	if (argc == 1) {
		printf("\nYou need a command line "
				"argument to handle "
				"command line "
				"input!\n");
		return;
	}
	if (argv == NULL) {
		printf("\nargv cannot be a NULL "
				"pointer when "
				"handling command "
				"line input!\n");	
		return;
	}
	if (courseTreePtr == NULL) {
		printf("\nCannot handle command line "
				"input with a NULL "
				"CourseBinaryTree "
				"pointer argument!\n");
		return;
	}
	if (depListPtr == NULL) {
		printf("\nCannot handle command line "
				"input with a NULL "
				"DepartmentVector "
				"pointer argument!\n");
		return;
	}
	if (degListPtr == NULL) {
		printf("\nCannot handle command line "
				"input with a NULL "
				"DegreeVector "
				"pointer argument!\n");
		return;
	}
	if (studentTreePtr == NULL) {
		printf("\nCannot handle command line "
				"input with a NULL "
				"StudentBinaryTree "
				"pointer argument!\n");
		return;
	}

	// loop for numFiles here
	// for each file load in lines
	// we start at 1 -> argc includes the name of the program main
	for (int i = 1; i < argc; ++i) {
		// lines is used as array of strings for each line of the file
		char **lines = NULL;
		int numLinesInFile = fileParser(&lines, argv[i]);
		
		// check first line for department or degree
		if (strcmp(lines[0], "DEPARTMENT") == 0) {
			
			// build data structure for file type
			// load data into the structure
			Department *newDepPtr = loadDepartment(lines, numLinesInFile, courseTreePtr);
			addDepartment(depListPtr, newDepPtr);

		} else if (strcmp(lines[0], "DEGREE") == 0) {

			// build data structure for file type
			// load data into the structure
			
			Degree *newDegPtr = loadDegree(lines, numLinesInFile, courseTreePtr);
			addDegree(degListPtr, newDegPtr);
			

		} else if (strcmp(lines[0], "STUDENT") == 0) {
			
			// build data structure for file type
			// load data into structure
			Student *newStuPtr = loadStudent(lines, numLinesInFile, courseTreePtr);
			insertInStudentBinaryTree(studentTreePtr, newStuPtr);	
		} else {

			printf("\nInput file missing header\n");

		}
	}
	return;
}
