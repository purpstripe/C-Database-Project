/*
 *
 *	Header file for the StudentBinaryTree ADT
 *	interface
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
 *	We can search, insert, and print
 *	the StudentBinaryTree
 *
 *	We can remove completed Courses
 *	from the tree
 *
 */
#ifndef STUDENTBT_H
#define STUDENTBT_H

#include "student.h"

// ADT structs
// Student node struct
typedef struct studentBTNode {
	struct studentBTNode *left;
	struct studentBTNode *right;
	Student *studentPtr;	
} StudentBTNode;

// Student tree struct
typedef struct studentBinaryTree {
	StudentBTNode *root;
	int size;
} StudentBinaryTree;


// interface

/*
 * creates a StudentBTNode with the given
 * Student pointer argument
 *
 * returns a pointer to the new StudentBTNode
 * or returns NULL if there is an issue
 *
 * newStudentPtr - pointer to the Student
 * to be referenced by the new node
 */
StudentBTNode* createStudentBTNode(Student* newStudentPtr);

/*
 * creates a StudentBinaryTree for the 
 * program's Students
 */
StudentBinaryTree* createStudentBinaryTree();

/* 
 * recursively searches the tree starting
 * at rootPtr for a Student with the name
 * studentName
 *
 * returns a pointer to the StudentBTNode
 * if found
 *
 * returns NULL otherwise
 *
 * rootPtr - pointer to the StudentBTNode
 * on the StudentBinaryTree or subtree
 * we want to start traversing from 
 *
 * studentName - string for the name
 * of the Student that we want to find
 * on the StudentBinaryTree
 */
StudentBTNode* findInStudentBinaryTree(StudentBTNode* rootPtr, char* studentName);

/*
 * inserts a Student pointer into the
 * StudentBinaryTree organized alphabetically
 *
 * bt - pointer to the StudentBinaryTree
 *
 * newStudentPtr - pointer to the Student
 * to be added to the tree
 */
void insertInStudentBinaryTree(StudentBinaryTree* bt, Student* newStudentPtr );

/*
 * prints all Student information starting at
 * the tree/subtree with stuNodePtr as root
 *
 * traverses the tree in-order so that 
 * Students are printed alphabetically
 *
 * stuNodePtr - pointer to the StudentBTNode
 * we want to treat as the tree root, 
 * where we want to start
 */
void printStudentBinaryTreeInOrder(StudentBTNode* stuNodePtr);

/*
 * removes a completed Course from all
 * Students in the StudentBinaryTree
 *
 * bt - pointer to the StudentBinaryTree
 *
 * courseName - name of the Course we want
 * to remove from all completed Courses
 *
 */
void removeCompletedCourseFromAllStudents(StudentBinaryTree* bt, char* courseName);

#endif
