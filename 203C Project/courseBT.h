/*
 *
 *	Header file for the CourseBinaryTree interface
 *
 *	CourseBinaryTree is a binary search tree that 
 *	organizes nodes containing Course pointers 
 *	alphabetically by Course name (ex. CS 150)
 *
 *	The CourseBinaryTree stores every Course from 
 *	every file loaded from the command line with as 
 *	much information about each Course as possible
 *	This includes:
 *		Course name
 *		Course title
 *		The Department it belongs to
 *		All Degrees it belongs to
 *		Its prerequisite courses
 *	Some of this information may be redundant; 
 *	however, I've included it in the Course ADT 
 *	for ease of programming in some instances, and 
 *	runtime efficiency in others.
 *
 *	The Department, Degree, and Student ADT's contain 
 *	Course pointers that refer to Courses on the 
 *	CourseBinaryTree.
 *	
 *	With the interface below, Courses can be added,
 *	searched for, and removed from the
 *	CourseBinaryTree. Additionally, Courses with
 *	a given prerequisite can be printed and
 *	specified prerequisites can be removed from
 *	all Courses of the CourseBinaryTree.
 * 	
 */

#ifndef COURSEBT_H
#define COURSEBT_H

#include "course.h"

/*
 * tree node with references to right and left 
 * children and a pointer to a Course
 */
typedef struct courseBTNode {
	struct courseBTNode *left;
	struct courseBTNode *right;
	Course *coursePtr;
} CourseBTNode;

/* 
 * struct for binary search tree containing 
 * the root node pointer
 * the tree is organized lexicographically
 */
typedef struct courseBinaryTree {
	CourseBTNode *root;
} CourseBinaryTree;


// CourseBinaryTree interface


/* 
 * allocates heap space for CourseBTNode,
 * and initializes its data members, and
 * returns a CourseBTNode pointer
 *
 * newCoursePtr - Course pointer to be 
 * initialized in the new CourseBTNode
 */
CourseBTNode* createCourseBTNode( Course* newCoursePtr );


/* 
 * allocates heap space for a CourseBinaryTree,
 * initializes its root pointer to NULL, and 
 * returns a CourseBinaryTree pointer
 */
CourseBinaryTree* createCourseBinaryTree();


/*
 * searches CourseBinaryTree for a CourseBTNode with a
 * specified Course name, recursively, and returns a pointer 
 * to that CourseBTNode, if found
 * otherwise, returns NULL
 *
 * rootPtr - CourseBTNode pointer to the root of a
 * CourseBinaryTree or subtree
 *
 * courseName - string for the name of the Course we are
 * looking for
 */
CourseBTNode* findInCourseBinaryTree(CourseBTNode* rootPtr, char* courseName);


/*
 * searches CourseBinaryTree for a spot to insert
 * a CourseBTNode with given Course name
 * if the location is found and empty, then a node is
 * inserted into the tree and a Course pointer is 
 * returned
 * if the location is found to be filled, then a pointer
 * to the previously existing Course is returned
 *
 * bt - pointer to a CourseBinaryTree
 *
 * courseName - string for the name of the Course and
 * CourseBTNode to be initialized/found in the CourseBT
 *
 * returns a pointer to a Course with courseName on the
 * CourseBinaryTree
 */
Course* insertInCourseBinaryTree(CourseBinaryTree* bt, char* courseName);


/*
 * removes Course with the given Course name argument
 * from the CourseBinaryTree, linking nodes and copying data
 * appropriately so that the tree remains a binary search tree
 *
 * bt - pointer to a CourseBinaryTree
 *
 * courseName - string for the name of the Course to be
 * removed from the CourseBinaryTree
 */
void removeFromCourseBinaryTree(CourseBinaryTree* bt, char* courseName);


/*
 * prints all Course names of Courses with a specified
 * prerequisite name argument from the CourseBinaryTree
 *
 * bt - pointer to CourseBinaryTree
 *
 * prereqName - string for the name of the prerequisite
 * Course
 */
void printAllCoursesWithPrerequisite(CourseBinaryTree* bt, char* prereqName);

/*
 * removes every instance of a specified Course name from
 * all Courses' prerequisite lists
 *
 * bt - pointer to CourseBinaryTree
 *
 * prereqName = string for the name of the prerequisite
 * to be removed from all Courses' prerequisite list
 */ 
void removeCourseFromAllPrereqs(CourseBinaryTree* bt, char* prereqName);

#endif
