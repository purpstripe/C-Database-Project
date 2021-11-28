/*
 *
 *	Header file for C string editing functions
 *
 *	These string editing functions are used for:
 *	splitting lines read from formatted files
 *	splitting lines read from user input
 *	allocating heap space for string arrays
 *	and removeing command characters from user input
 */

#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

/*
 * removes the user's command character 
 * from their input string and returns the 
 * character to the user for processing 
 * the user's function request
 *
 * strPtr - pointer to the string getting
 * its command character removed
 */
char removeCommandChar(char** strPtr);

/*
 * allocates exactly enough heap space for
 * a string array of a given number of
 * strings
 *
 * strArrPtr - pointer to an empty string
 * array to be filled with the strings in
 * the given string array buffer
 *
 * strArrBuffer - string array buffer
 * temporarily holding strings
 *
 * numStrings - the number of strings
 * inside of the strArrBuffer
 */
void allocHeapForStrArr(char*** strArrPtr, char* strArrBuffer[], int numStrings);

/*
 * splits the "OR" off of the input
 * string, if present, and loads
 *
 * splits the input string at all
 * commas
 *
 * loads all split strings into a
 * string buffer and passes the buffer into a function
 * to load all of the split strings into strictly 
 * allocated heap space (no more or less than needed)
 *
 * returns the number of strings
 * split and loaded
 *
 * inputStr - input string to be split up at
 * each comma and "OR"
 *
 * strArrPtr - pointer to an empty string array
 * to be filled by the split input string
 */
int splitStringAtComma(char* inputStr, char*** strArrPtr);

#endif
