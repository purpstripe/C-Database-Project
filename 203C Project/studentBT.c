/*
 *
 *	C source file containing the StudentBinaryTree 
 *	ADT implementation
 *
 *	As Student files are processed, the 
 *	StudentBinaryTree stores all Student pointers 
 *	in StudentBTNodes
 *	
 *	Each Student contains their name, their 
 *	Degree program's name, and a list of
 *	their completed Courses
 *
 *	Each of their completed Courses are
 *	stored in a Vector Element as a Course
 *	pointer referring to the CourseBinaryTree
 *
 *	The StudentBinaryTree is organized
 *	by Student name lexicographically
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "studentBT.h"

/*
 * createStudentBTNode() takes a Student pointer
 * as an argument
 *
 * createStudentBTNode() allocates heap space
 * for the new StudentBTNode and initializes
 * its data members
 *
 * createStudentBTNode() initializes the node's
 * data with a Student pointer and initializes
 * the node's left and right node pointers with
 * NULL
 *
 * createStudentBTNode() returns a pointer to
 * the new StudentBTNode
 */
StudentBTNode* createStudentBTNode(Student* newStudentPtr) {

	// checking for NULL pointer argument
	if (newStudentPtr == NULL) {
		printf("\nCannot initialize a StudentBTNode "
				"with a NULL Student pointer "
				"argument\n");
		return NULL;
	}

	// initializing data members
	StudentBTNode *newNode = (StudentBTNode*) malloc(sizeof(StudentBTNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->studentPtr = newStudentPtr;
	return newNode;
}

/*
 * createBinaryTree() allocates memory for a
 * StudentBinaryTree on the heap
 * 
 * createBinaryTree() initilizes the root of 
 * the tree with NULL
 *
 * the root StudentBTNode and other 
 * StudentBTNode are inserted into the 
 * tree in a separate function,
 * insertInStudentBinaryTree()
 * 
 * createStudentBinaryTree() returns a pointer 
 * to the new tree
 */
StudentBinaryTree* createStudentBinaryTree() {

	StudentBinaryTree *newTree = (StudentBinaryTree*) malloc(sizeof(StudentBinaryTree));
	newTree->root = NULL;
	return newTree;
}

/*
 * findInStudentBinaryTree() takes a 
 * StudentBTNode pointer and a C string
 * as arguments
 *
 * findInStudentBinaryTree() traverses
 * the StudentBinaryTree recursively
 * looking for a StudentBTNode with
 * the given Student name
 *
 * uses strcmp from string.h to 
 * choose left and right subtrees
 *
 * if found, findInStudentBinaryTree()
 * returns a StudentBTNode pointer
 *
 * if not found, the function returns
 * NULL
 */
StudentBTNode* findInStudentBinaryTree(StudentBTNode *rootPtr, char* studentName) {

	if (studentName == NULL) {
		printf("\nCannot find Student in the "
				"StudentBinaryTree with "
				"no Student name string "
				"argument\n");
		return NULL;
	}

	// node does not exist in StudentBinaryTree	
	if (rootPtr == NULL) {
		return NULL;
	// checking to the left of rootPtr
	} else if (strcmp(studentName, rootPtr->studentPtr->name) < 0) {
		return findInStudentBinaryTree(rootPtr->left, studentName);
	// checking to the right of rootPtr
	} else if (strcmp(studentName, rootPtr->studentPtr->name) > 0) {
		return findInStudentBinaryTree(rootPtr->right, studentName);
	} else {
	// node found on the tree
		return rootPtr;	
	}
}
/*
 * insertInStudentBinaryTree() takes a pointer to
 * the StudentBinaryTree and a Student pointer
 * as arguments
 *
 * insertInStudentBinaryTree() initializes a 
 * StudentBTNode with the given Student pointer
 *
 * insertInStudentBinaryTree() finds a location
 * for the new StudentBTNode lexicographically
 * by Student name
 * 
 * if the root node has not been fillled, then
 * insertInStudentBinaryTree() will put the
 * new node as the StudentBinaryTree root
 *
 * if a StudentBTNode already exists with
 * the given Student pointer, then the 
 * heap space used to the new node is freed
 */
void insertInStudentBinaryTree( StudentBinaryTree* bt, Student* newStudentPtr ) {

	// making sure the pointer to the binary tree is valid
	if (bt == NULL) {
		printf("\nCannot insert Student pointer in "
			       	"StudentBinaryTree "
				"with NULL binary tree "
				"pointer argument\n");
		return;
	}
	if (newStudentPtr == NULL) {
		printf("\nCannot insert Student pointer in "
				"StudentBinaryTree with NULL "
				"Student pointer argument\n");
		return;
	}

	// creating a new binary tree node
	StudentBTNode *newNode = createStudentBTNode(newStudentPtr);
	// binary tree is empty - add root
	if (bt->root == NULL) {
		bt->root = newNode;
		return;
	}
	// searching for appropriate place in the BT for the new node
	StudentBTNode *nodePtr = bt->root;
	char *studentName = newStudentPtr->name;
	bool locationFound = false;
	while (!locationFound) {
		if ( (strcmp(studentName, nodePtr->studentPtr->name) < 0) && (nodePtr->left != NULL) ) {
			nodePtr = nodePtr->left;
		} else if ( (strcmp(studentName, nodePtr->studentPtr->name) > 0) && (nodePtr->right != NULL) ) {
			nodePtr = nodePtr->right;
		} else {
			locationFound = true;
		}
	}
	// newNode is linked to the left of nodePtr
	if (strcmp(studentName, nodePtr->studentPtr->name) < 0) {
		nodePtr->left = newNode;
	// newNode is linked to the right of nodePtr
	} else if (strcmp(studentName, nodePtr->studentPtr->name) > 0) {
		nodePtr->right = newNode;
	// found node with the same name as studentName
	} else if (strcmp(studentName, nodePtr->studentPtr->name) == 0) {
		free(newNode);
		newNode = NULL;
		printf("\nStudent is already on the tree\n");
	// error
	} else {
		printf("\nError adding student to the tree\n");
	}
	return;
}

/*
 * printStudentBinaryTreeInOrder() takes a StudentBTNode
 * pointer as an argument
 *
 * printStudentBinaryTreeInOrder() traverses the 
 * tree starting at the StudentBTNode given and
 * prints all Student information found within the 
 * tree/subtree in order
 *
 *
 */
void printStudentBinaryTreeInOrder(StudentBTNode *stuNodePtr) {

	if (stuNodePtr == NULL) {
		return;
	}
	
	printStudentBinaryTreeInOrder(stuNodePtr->left);
	printStudent(stuNodePtr->studentPtr);
	printStudentBinaryTreeInOrder(stuNodePtr->right);
	return;
}

/*
 * traverseAndRemoveCompletedCourse() takes a 
 * StudentBTNode pointer and C string as 
 * arguments
 *
 * traverseAndRemoveCompletedCourse() is a 
 * recursive helper function for the function
 * removeCompletedCoursesFromAllStudents()
 *
 * traverseAndRemoveCompletedCourse() starts
 * traversing the tree/subtree at the
 * StudentBTNode pointer given
 *
 * traverseAndRemoveCompletedCourse() checks
 * each Course's list of completed Courses 
 * for a Course with the given string name
 *
 * if found, the function removes the Course
 * from the Student's list and prints the
 * Student's information to the terminal
 *
 * if not found, then the next node is
 * checked
 */
void traverseAndRemoveCompletedCourse( StudentBTNode *nodePtr, char *courseName) {

	// checking for NULL pointer argument
	if (nodePtr == NULL) {
		return;
	}

	traverseAndRemoveCompletedCourse(nodePtr->left, courseName);

	// checking for completed Course with courseName and
	// removing it, if found
	if ( findCoursePtrInVector(nodePtr->studentPtr->completedCourses, courseName) != NULL ) {
		removeCoursePtrFromVector(nodePtr->studentPtr->completedCourses, courseName);
		printStudent(nodePtr->studentPtr);
	}

	traverseAndRemoveCompletedCourse(nodePtr->right, courseName);

	return;

}

/*
 * removeCompletedCourseFromAllStudents() 
 * takes a StudentBinaryTree pointer and
 * C string as arguments
 *
 * removeCompletedCourseFromAllStudents()
 * removes every instance of a completed
 * Course with name courseName from every
 * Student in the StudentBinaryTree
 */
void removeCompletedCourseFromAllStudents( StudentBinaryTree *bt, char *courseName) {

	// checking for NULL pointer arguments
	if (courseName == NULL) {
		printf("\nCannot remove given Course from "
				"all Student's completed "
				"Courses with no Course "
				"name argument\n");
		return;
	}
	if (bt == NULL) {
		printf("\nCannot remove %s Course from "
				"all Student's completed "
				"Courses with NULL "
				"StudentBinaryTree pointer "
				"argument\n", courseName);

		return;
	}

	// checking for empty tree and removing
	// specified completed Course
	if (bt->root != NULL) {
		traverseAndRemoveCompletedCourse(bt->root, courseName);
		return;
	} else {
		printf("\nCannot remove %s Course from "
				"all Student's completed "
				"Courses with empty "
				"StudentBinaryTree\n", courseName);
		return;
	}
}
