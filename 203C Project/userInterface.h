/*
 *
 *	Header file for the functions associated with user commands
 *
 */

#ifndef USERCOMMAND_H
#define USERCOMMAND_H

/*
 * takes a user's command string
 * and separates the command char
 * from the string
 *
 * links the rest of the string
 * to the input string pointer
 * argument
 *
 * userInputPtr - linked as pointer 
 * to the user's input string at
 * the end of the function
 */
char getUserInput(char** userInputPtr);

/*
 * processes the user's input passed
 * into the function and calls the
 * functions to be executed
 *
 * commandChar - the first character
 * from the user input that's used
 * for choosing the program's function
 *
 * userInputPtr - pointer to the user's
 * input without the (first) command
 * character needed for executing the
 * program's functions
 *
 * courseTreePtr - pointer to the 
 * CourseBinaryTree needed for many
 * of the program's functions
 *
 * depListPtr - pointer to the 
 * DepartmentVector needed to 
 * access Departments throughout
 * the program
 *
 * degListPtr - pointer to the
 * DegreeVector needed to access
 * Degrees throughout the program
 *
 * studentTreePtr - pointer to the
 * StudentBinaryTree for Student 
 * accesses in the program
 */
void processUserInput(char commandChar, char** userInputPtr, CourseBinaryTree* courseTreePtr, DepartmentVector* depListPtr, DegreeVector* degListPtr, StudentBinaryTree* studentTreePtr);

#endif
