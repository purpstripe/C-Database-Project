/*
 *
 *	C source file for C string editing functions
 *
 *	These string editing functions are used for:
 *	splitting lines read from formatted files
 *	splitting lines read from user input
 *	allocating heap space for string arrays
 *	and removeing command characters from user input
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringFunctions.h"

#define MAX_ARRAY_SIZE 50

/*
 * removeCommandChar() takes a pointer to a string,
 * or a pointer to an array of char, as its argument
 *
 * removeCommandChar() removes the first two characters
 * of the given string by incrementing the string 
 * pointer - for its intended purpose, the function
 * removes a user's command character and the space
 * between the user's command char and the rest of 
 * the string needed for the programs functions
 *
 * removeCommandChar() returns the removed character
 * (not including the space) so that the program's 
 * various functions are accessable (switch statement)
 */
char removeCommandChar(char **strPtr) {

	// checking for null string pointer
	if (strPtr == NULL) {
		printf("\nCannot remove first character "
				"of a string with NULL "
				"string pointer "
				"argument\n");
		return -1;
	}

	// storing first character from the user input
	char firstChar = (*strPtr)[0];
	// shifting pointer past first character and white space character
	(*strPtr) += 2;
	return firstChar;
}

/*
 * allocHeapForStrArr() takes a pointer to an array of
 * strings, a pointer to a temporary string array buffer,
 * and the number of strings in the buffer as arguments
 *
 * allocHeapForStrArr() allocates heap space for
 * exactly enough string pointers to reference
 * every string in the string array buffer and then
 * copies the memory locations of every string in
 * the buffer into the newly allocated heap string
 * array
 */
void allocHeapForStrArr(char ***strArrPtr, char *strArrBuffer[], int numStrings) {

	// testing for null pointers
	if (strArrBuffer == NULL) {
		printf("\nCannot allocate heap space for "
				"a string array with "
				"NULL string array buffer "
				"pointer argument\n");
		return;
	}
	if (numStrings == 0) {
		printf("\nCannot allocate heap space for "
				"a string array with no "
				"strings\n");
		return;
	}
	// dynamically allocating space for string array
	char **strArr = NULL;
	strArr = (char**) calloc(numStrings, sizeof(char*));
	if (strArr == NULL) {
		printf("\nFailed to allocate heap space "
				"for NULL string array "
				"pointer\n");
		return;
	}
	// pointer to string array to be used outside this function
	*strArrPtr = strArr;
	for (int j = 0; j < numStrings; ++j) {
		strArr[j] = strArrBuffer[j];
	}
	return;
}

/*
 * splitStringAtComma() takes an input string and a pointer
 * to a string array as arguments
 *
 * splitStringAtComma() splits the "OR" off of the input
 * string, if present, and loads
 *
 * splitStringAtComma() splits the input string at all
 * commas
 *
 * splitStringAtComma() loads all split strings into a
 * string buffer and passes the buffer into a function
 * to load all of the split strings into strictly 
 * allocated heap space (no more or less than needed)
 *
 * splitStringAtComma() returns the number of strings
 * split and loaded
 */
int splitStringAtComma(char *inputStr, char ***strArrPtr) {

	// checking for NULL pointer arguments
	if (inputStr == NULL) {
		printf("\nCannot split string at comma "
				"with NULL input string "
				"pointer argument\n");
		return -1;
	}	
	if (strArrPtr == NULL) {
		printf("\nCannot split string at comma "
				"with NULL string array "
				"pointer\n");
		return -1;	
	}

	// splitting the input string by commas and loading them into a buffer
	char *strArrBuffer[MAX_ARRAY_SIZE];
	char *delimiter = NULL;
	// checking for OR
	if (inputStr[0] == 'O' && inputStr[1] == 'R' && inputStr[2] == ' '){
		delimiter = " ";
	} else {
		delimiter = ",";
	}
	strArrBuffer[0] = strtok(inputStr, delimiter);
	if (strArrBuffer[0] != NULL) {
		strArrBuffer[0] = strdup(strArrBuffer[0]);
	}
	// setting delimiter if first string was "OR"
	delimiter = ",";

	int i = 0;
	while(strArrBuffer[i] != NULL) {
		++i;
		strArrBuffer[i] = strtok(NULL, delimiter);
		if (strArrBuffer[i] != NULL) {
			// + 1 for moving char pointer after whitespace
			if (strArrBuffer[i][0] == ' ') {
				strArrBuffer[i] = strdup(strArrBuffer[i]) + 1;
			} else {
				strArrBuffer[i] = strdup(strArrBuffer[i]);
			}
		}
	}
	// number of strings in the buffer
	int numStrings = i;

	allocHeapForStrArr(strArrPtr, strArrBuffer, numStrings);

	// returning the number of strings
	return numStrings;

}

