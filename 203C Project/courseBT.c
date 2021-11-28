/*
 *
 *	C source file containing the CourseBinaryTree ADT 
 *	implementation
 *
 *	Initially, the CourseBinaryTree stores every Course 
 *	from every file loaded from the command line with as 
 *	much information about each Course as possible
 *	Each Course includes:
 *		Course name
 *		Course title
 *		The Department it belongs to
 *		All Degrees it belongs to
 *		Its prerequisite courses
 *
 *	The CourseBinaryTree is a Binary Search Tree
 *	organized alphabetically by Course name
 *	
 *	The Department, Degree, and Student ADT's contain 
 *	Course pointers that refer to the Courses on the 
 *	CourseBinaryTree
 *
 *	Go to header file for more information
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "courseBT.h"
#include "course.h"

/*
 * createCourseBTNode() takes a Course pointer argument for
 * the newCoursePtr parameter
 * createCourseBTNode() allocates heap space and initializes 
 * a CourseBTNode and its three data members:
 * 	coursePtr with the Course pointer argument
 * 	left, a reference to the left CourseBTNode
 * 	right, a reference the right CourseBTNode 
 * left and right are initialized with NULL and linked as
 * CourseBTNodes are added to the tree 
 * createCourseBTNode() returns the new CourseBTNode pointer
 * and NULL for error
 */
CourseBTNode* createCourseBTNode(Course *newCoursePtr) {

	// null Course pointer detection
	if (newCoursePtr == NULL) {
		printf("\nCannot create a CourseBTNode with "
				"NULL Course pointer "
				"argument\n");
		return NULL;
	}

	// allocating heap space for the node
	// and initializing node's data members
	CourseBTNode *newNode = (CourseBTNode*) malloc(sizeof(CourseBTNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->coursePtr = newCoursePtr;
	return newNode;
}	

/*
 * createCourseBinaryTree() allocates heap space for a
 * new CourseBinaryTree and provides a pointer to that
 * memory location 
 * 
 * createCourseBinaryTree() initilizes the tree's root 
 * with NULL 
 *
 * the root and following CourseBTNodes are filled in
 * as Courses are added to the CourseBinaryTree
 *
 * createCourseBinaryTree() returns a pointer to the 
 * new CourseBinaryTree
 */
CourseBinaryTree* createCourseBinaryTree() {

	// allocating heap space for CourseBinaryTree
	// and initializing root
	CourseBinaryTree *newTree = (CourseBinaryTree*) malloc(sizeof(CourseBinaryTree));
	newTree->root = NULL;
	return newTree;
}

/*
 * findInCourseBinaryTree() takes a reference to the 
 * root of the CourseBinaryTree to be searched and a 
 * name string argument for the Course we are searching 
 * for 
 * 
 * findInCourseBinaryTree() traverses the CourseBinaryTree 
 * recursively, checking each CourseBTNode for its Course's
 * name using strcmp() from string.h
 * 
 * findInCourseBinaryTree() moves to the left subtree when
 * the checked CourseBTNode's Course name is less than 
 * courseName and moves to the right subtree when it is
 * more than courseName
 *
 * if found, findInCourseBinaryTree() returns a pointer to 
 * the CourseBTNode with courseName and it returns NULL 
 * otherwise 
 */
CourseBTNode* findInCourseBinaryTree(CourseBTNode *rootPtr, char* courseName) {

	if (courseName == NULL) {

		printf("\nCannot find a Course in the "
				"CourseBinaryTree with no "
				"Course name argument\n");
		return NULL;
	}

	// node does not exist in CourseBinaryTree	
	if (rootPtr == NULL) {
		return NULL;
	// checking to the left of rootPtr
	} else if (strcmp(courseName, rootPtr->coursePtr->name) < 0) {
		return findInCourseBinaryTree(rootPtr->left, courseName);
	// checking to the right of rootPtr
	} else if (strcmp(courseName, rootPtr->coursePtr->name) > 0) {
		return findInCourseBinaryTree(rootPtr->right, courseName);
	} else {
	// node found on the tree
		return rootPtr;	
	}
}

/*
 * insertInCourseBinaryTree() takes a CourseBinaryTree 
 * pointer (parameter bt) and the name of the Course 
 * to be added to the CourseBinaryTree 
 * (parameter courseName) as arguments 
 *
 * insertInCourseBinaryTree() creates a Course with the 
 * name, courseName, and creates a CourseBTNode with 
 * the newly initialized Course pointer
 *
 * insertInCourseBinaryTree() inserts the new node into 
 * the CourseBinaryTree, bt 
 * 
 * the name of the new Course determines the location of
 * the CourseBTNode in the CourseBinaryTree using stcmp()
 * 
 * insertInCourseBinaryTree() then returns a pointer to 
 * the Course referenced by the new CourseBTNode for 
 * further editing of the Course's data members
 * 
 * however, if a node with courseName is already in the 
 * tree then the new CourseBTNode is not added to the 
 * CourseBinaryTree
 *
 * in that case, the new CourseBTNode and Course pointer 
 * are removed from memory and a pointer to the existing
 * Course with name courseName is returned to the user
 *
 * NULL is returned with an error message for any error
 */

Course* insertInCourseBinaryTree( CourseBinaryTree* bt, char* courseName ) {

	// making sure the function arguments are existing
	// and valid
	if (courseName == NULL) {
		printf("\nCannot insert Course node into "
			       "CourseBinaryTree with no Course "
			       "name argument\n");
		return NULL;
	}
	if (bt == NULL) {
		printf("\nCannot insert %s Course node with "
				"NULL CourseBinaryTree pointer "
				"argument\n", courseName);
		return NULL;
	}
	// creating the new Course and CourseBTNode
	Course *newCourse = initCourse(courseName);
	CourseBTNode *newNode = createCourseBTNode(newCourse);
	// if tree is empty - adding root and return
	if (bt->root == NULL) {
		bt->root = newNode;
		return newNode->coursePtr;
	}
	// tree is not empty
	// finding a location for the newNode in the tree
	CourseBTNode *nodePtr = bt->root;
	bool locationFound = false;
	while (!locationFound) {
		// checking left location by name of newNode
		if ( (strcmp(courseName, nodePtr->coursePtr->name) < 0) && (nodePtr->left != NULL) ) {
			nodePtr = nodePtr->left;
		// checking right location by name of newNode
		} else if ( (strcmp(courseName, nodePtr->coursePtr->name) > 0) && (nodePtr->right != NULL) ) {
			nodePtr = nodePtr->right;
		// location is found or node with courseName is already on the tree
		} else {
			locationFound = true;
		}
	}

	// inserting newNode to the left of leaf node pointer, nodePtr
	if (strcmp(courseName, nodePtr->coursePtr->name) < 0) {
		nodePtr->left = newNode;
		return newNode->coursePtr;	
	// inserting newNode to the right of leaf node pointer, nodePtr
	} else if (strcmp(courseName, nodePtr->coursePtr->name) > 0) {
		nodePtr->right = newNode;
		return newNode->coursePtr;
	// node already exists on the tree
	} else if (strcmp(courseName, nodePtr->coursePtr->name) == 0) {
		free(newNode->coursePtr);
		newNode->coursePtr = NULL;
		free(newNode);
		newNode = NULL;
		return nodePtr->coursePtr;	
	// error
	} else {
		printf("\nCourseBT insertion error!\n");
		return NULL;
	}
}

/*
 * findMinimumNode() takes a CourseBTNode pointer as 
 * its argument (parameter nodePtr)
 *
 * findMinimumNode() traverses the tree or subtree starting
 * at the CourseBTNode, nodePtr
 *
 * findMinimumNode() returns the CourseBTNode with the
 * lowest value (Course name lexicographically)
 *
 * in the case of CourseBinaryTree, the function
 * returns the leftmost CourseBTNode in the tree or subtree
 * beginning with the root nodePtr
 */
CourseBTNode* findMinimumNode(CourseBTNode *nodePtr) {

	if (nodePtr == NULL) {
		printf("\nCannot find minimum node in a "
				"CourseBinaryTree with "
				"a NULL CourseBTNode "
				"pointer argument\n");
		return NULL;
	}

	while (nodePtr->left != NULL) {
		nodePtr = nodePtr->left;	
	}
	return nodePtr;
}

/*
 * traverseAndRemoveCourse() takes a CourseBTNode 
 * pointer (parameter nodePtr) and a C string 
 * (parameter courseName) as arguments
 *
 * traverseAndRemoveCourse() recusively traverses
 * and searches a CourseBinaryTree with root, nodePtr,
 * for the Course with name courseName
 *
 * traverseAndRemoveCourse() uses strcmp() to compare
 * courseName with each CourseBTNodes' Courses'
 * names to choose which subtree to reference 
 * for the next recursive call
 *
 * if the CourseBTNode is not found, then the current
 * CourseBinaryTree root is returned
 *
 * if the CourseBTNode is found in the CourseBinaryTree
 * or any of its subtrees, then the CourseBTNode with
 * Course of name courseName is removed from the 
 * CourseBinaryTree in one of three different ways
 * depending on if it is in a leaf node, a node with one
 * child, or a node with two children
 *
 * the proper root for the CourseBinaryTree and all of
 * its subtrees after CourseBTNode removal (or the lack
 * thereof) is returned from each recursive call in the
 * form of a CourseBTNode pointer
 */
CourseBTNode* traverseAndRemoveCourse(CourseBTNode *nodePtr, char *courseName) {

	// searching for node with courseName by tree 
	// traversal and recursive calls
	if (nodePtr == NULL) {
		return nodePtr;
	} else if ( strcmp(courseName, nodePtr->coursePtr->name) < 0 ) {
		nodePtr->left = traverseAndRemoveCourse(nodePtr->left, courseName);
	} else if ( strcmp(courseName, nodePtr->coursePtr->name) > 0 ) {
		nodePtr->right = traverseAndRemoveCourse(nodePtr->right, courseName);
	// node with courseName found
	} else {

		// handling different node position cases 
		// no children
		if ( (nodePtr->left == NULL) && (nodePtr->right == NULL) ) {
			free(nodePtr);
			nodePtr = NULL;
		// left child
		} else if (nodePtr->left == NULL) {
			CourseBTNode *tempPtr = nodePtr;
			nodePtr = nodePtr->right;
			free(tempPtr);
		// right child
		} else if (nodePtr->right == NULL) {
			CourseBTNode *tempPtr = nodePtr;
			nodePtr = nodePtr->left;
			free(tempPtr);
		// two children
		} else {
			CourseBTNode *tempPtr = findMinimumNode(nodePtr->right);
			nodePtr->coursePtr = tempPtr->coursePtr;
			nodePtr->right = traverseAndRemoveCourse(nodePtr->right, tempPtr->coursePtr->name);
		}	
	}
	return nodePtr;
}

/*
 * removeFromCourseBinaryTree() takes a CourseBinaryTree
 * pointer (parameter bt), and a C string for the name
 * of the Course to be removed (parameter courseName)
 * as arguments
 *
 * removeFromCourseBinaryTree() checks for vaild input
 * and then passes the appropriate arguments into the
 * helper function, traverseAndRemoveCourse(), to 
 * remove the CourseBTNode with the Course of name 
 * courseName from the CourseBinaryTree, *bt
 */
void removeFromCourseBinaryTree( CourseBinaryTree *bt, char *courseName ) {

	// checking for vaild pointer arguments
	if (courseName == NULL) {
		printf("\nCannot remove Course from CourseBinaryTree "
				"with no Course name argument\n");
		return;
	}
	if (bt == NULL) {
		printf("\nCannot remove %s Course from "
				"CourseBinaryTree with "
				"NULL CourseBinaryTree "
				"pointer argument\n", 
				courseName);
		return;
	}

	// checking for empty tree and calling helper
	// function
	if (bt->root != NULL) {
		bt->root = traverseAndRemoveCourse(bt->root, courseName);
		return;
	} else {
		printf("\nCannot remove %s Course from empty "
				"CourseBinaryTree\n",
				courseName);
		return;
	}
}

/*
 * traverseAndPrintCoursesWithPrereq() takes a 
 * CourseBTNode pointer (parameter nodePtr), a 
 * C string prerequisite name (parameter prereqName),
 * and an integer counter variable (parameter counterPtr)
 * as arguments
 *
 * traverseAndPrintCoursesWithPrereq() will recursively
 * traverse across a CourseBinaryTree and all of its 
 * subtrees, in-order, checking for Course prerequisites
 *
 * if the Course being checked has one prerequisite and
 * the prerequisite is fulfilled (Course's prerequisite
 * Course is prereqName) then the Course's name is printed 
 * to the terminal
 *
 * if the Course being checked has disjunct prerequisites
 * and one of the prerequisite Courses has name prereqName,
 * then the name of available Course is printed to the 
 * terminal
 *
 * if the Course being checked has conjunct prerequisite
 * Courses and one of them is prereqName, then the 
 * checked Course's name is printed along with the leftover 
 * prerequisite Courses that need to be completed to make 
 * the Course available
 *
 * counterPtr is used to determine if commas need be printed
 * to the terminal between Course names - more than one 
 * Course name has been printed
 */
void traverseAndPrintCoursesWithPrereq( CourseBTNode *nodePtr, char *prereqName, int *counterPtr ) {

	// passed over a leaf node
	if (nodePtr == NULL) {
		return;
	}
	
	// recursive call - left subtree
	traverseAndPrintCoursesWithPrereq(nodePtr->left, prereqName, counterPtr);

	// checking different prerequisite Course arrangements
	// and printing Course availability information
	LinkedListNode *prereqPtr = nodePtr->coursePtr->firstPrereq;
	if (prereqPtr != NULL) {
		// only one prerequisite to check
		if (prereqPtr->next == NULL) {
			if ( checkCourseForPrerequisite(nodePtr->coursePtr, prereqName) == 1 ) {
				if ( (*counterPtr) > 0) {
					printf(", ");
				}
				printf("%s", nodePtr->coursePtr->name);
				(*counterPtr)++;
			}
		}
		// a Course with disjunct prereqs
		// only one prereq needed to print Course
		else if ( strcmp(prereqPtr->name, "OR") == 0 ) {
			if ( checkCourseForPrerequisite(nodePtr->coursePtr, prereqName) == 1 ) {
				if ( (*counterPtr) > 0) {
					printf(", ");
				}
				printf("%s", nodePtr->coursePtr->name);
				(*counterPtr)++;
			}
		} 
		// conjunct prerequisite Courses
		// every prereq must be fulfilled 
		// to make Course available
		else {
			if ( checkCourseForPrerequisite(nodePtr->coursePtr, prereqName) == 1 ) {
				if ( (*counterPtr) > 0) {
					printf(", ");
				}
				printf("%s (still requires", nodePtr->coursePtr->name);
				while (prereqPtr != NULL) {
					if ( strcmp(prereqPtr->name, prereqName) != 0 ) {
						printf(" %s", prereqPtr->name); 
					}
					prereqPtr = prereqPtr->next;
				}	
				printf(")");
				(*counterPtr)++;
			}
		}
	}
	// recursive call - right subtree
	traverseAndPrintCoursesWithPrereq(nodePtr->right, prereqName, counterPtr);

	return;
}

/*
 * printAllCoursesWithPrerequisite() takes a CourseBinaryTree
 * pointer (parameter bt), and a C string for the name
 * of the prerequisite Course to be checked for 
 * (parameter prereqName) as arguments
 *
 * printAllCoursesWithPrerequisite() checks for vaild input
 * and then passes the appropriate arguments into the
 * helper function, traverseAndPrintCoursesWithPrereq(), to 
 * print the name of any Course that contains the prerequisite
 * Course named prereqName in the CourseBinaryTree, *bt
 */
void printAllCoursesWithPrerequisite( CourseBinaryTree *bt, char *prereqName ) {

	// checking for vaild input arguments
	if (prereqName == NULL) {
		printf("\nCannot print all Courses with "
				"a given prerequisite with no "
				"prerequisite name argument\n");
		return;
	}
	if (bt == NULL) {
		printf("\nCannot print all Courses with "
				"prerequisite %s with NULL "
				"CourseBinaryTree pointer "
				"argument\n", prereqName);
		return;
	}

	// checking for empty tree, initializing counter, 
	// and calling helper function
	if ( bt->root != NULL) {
		int *counterPtr = (int*) malloc(sizeof(int));
		*counterPtr = 0;
		traverseAndPrintCoursesWithPrereq(bt->root, prereqName, counterPtr);
		if (*counterPtr == 0) {
			printf("%s is not a prerequisite for "
					"any Course", prereqName);
		}
		printf("\n");
		return;
	} else {
	
		printf("\nCannot print Courses with "
				"prerequisite %s with empty "
				"CourseBinaryTree\n", prereqName);
		return;
	}
}

/*
 * traverseAndRemovePrereqCourse() takes a CourseBTNode pointer
 * (parameter nodePtr) and a C string for a prerequisite Course
 * name (parameter prereqName) as arguments
 *
 * traverseAndRemovePrereqCourse() traverses the CourseBinaryTree
 * and all of its subtrees removing the prerequisite Course, 
 * prereqName, from all Courses' prerequisite lists on the 
 * CourseBinaryTree
 */
void traverseAndRemovePrereqCourse( CourseBTNode *nodePtr, char *prereqName) {

	// passed leaf node
	if (nodePtr == NULL) {
		return;
	}
	
	// recursive call - left subtree
	traverseAndRemovePrereqCourse(nodePtr->left, prereqName);

	// checking Course's prerequisites and removing prereqName
	// if present
	if ( checkCourseForPrerequisite(nodePtr->coursePtr, prereqName) == 1) {

		removeFromLinkedList( &(nodePtr->coursePtr->firstPrereq), prereqName);
	}

	// recursive call - right subtree
	traverseAndRemovePrereqCourse(nodePtr->right, prereqName);

	return;

}

/*
 * removeCourseFromAllPrereqs() takes a CourseBinaryTree
 * pointer (parameter bt), and a C string for the name
 * of the prerequisite Course to be removed 
 * (parameter prereqName) as arguments
 *
 * removeCourseFromAllPrereqs() checks for vaild input
 * and then passes the appropriate arguments into the
 * helper function, traverseAndRemovePrereqCourse(), to 
 * remove every instance of prereqName from all Courses'
 * prerequisite lists in the CourseBinaryTree, *bt
 */
void removeCourseFromAllPrereqs( CourseBinaryTree *bt, char *prereqName) {

	// checking for valid input arguments
	if (prereqName == NULL) {
		printf("\nCannot remove given prerequisite "
				"Course from all Courses on "
				"the CourseBinaryTree with "
				"no prereqName string argument\n");
		return;
	}

	if (bt == NULL) {
		printf("\nCannot remove prerequisite Course %s "
				"from all Courses' prerequisite "
				"list with NULL CourseBinaryTree "
				"pointer argument\n", prereqName);
		return;
	}

	// making sure tree isn't empty and 
	// calling helper function
	if (bt->root != NULL) {

		traverseAndRemovePrereqCourse( bt->root, prereqName);
		return;
	// empty CourseBinaryTree
	} else {
		printf("\nCannot remove prerequisites Course %s "
				"from all Courses' prereq list "
				"with empty "
				"CourseBinaryTree\n", prereqName);
		return;
	}
}
