/*
 *
 *	C source file containing the implementation 
 *	of the string LinkedList ADT
 *
 *	In terms of this program, the string 
 *	LinkedList is used for recording a 
 *	Course's Degree programs and 
 *	prerequisite Course names
 *
 *	The following functions make these 
 *	Degree and prerequisite lists
 *	easy to add to and remove from
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringLinkedList.h"

/*
 * initListNode() takes a C string, or array of char as
 * its argument
 *
 * initListNode() allocates space for a LinkedListNode
 * in heap space
 * 
 * initListNode() initializes linked list node with
 * a string as data and initializes its prev and
 * next LinkedListNode pointers with NULL
 *
 * initListNode() returns a pointer to the new
 * LinkedListNode
 */
LinkedListNode* initListNode(char* string) {

	// checking for NULL pointer argument
	if (string == NULL) {
		printf("\nCannot initialize string linked list "
				"node with NULL name string "
				"argument\n");
		return NULL;
	}

	// allocating heap space	
	LinkedListNode *nodePtr = (LinkedListNode*) malloc(sizeof(LinkedListNode));
	// filling in data members
	nodePtr->name = string;
	nodePtr->next = NULL;
	nodePtr->prev = NULL;
	return nodePtr;
}

/*
 * insertAfterListNode() takes two LinkedListNode 
 * pointers as arguments
 *
 * insertAfterListNode() inserts newNodePtr after
 * the nodePtr by linking up prev and next pointers
 */
void insertAfterListNode(LinkedListNode *nodePtr, LinkedListNode *newNodePtr) {

	// checking for null pointers
	if (nodePtr == NULL || newNodePtr == NULL) {
		printf("\nCannot insert into string linked list "
				"with a NULL node pointer\n");
		return;
	}

	// skip if node pointer after nodePtr is NULL
	if (nodePtr->next != NULL) {
		nodePtr->next->prev = newNodePtr;
	}
	// rest of the (list) node linking 
	newNodePtr->next = nodePtr->next;
	newNodePtr->prev = nodePtr;
	nodePtr->next = newNodePtr;
	return;
}

/*
 * clearLinkedList() takes a pointer to a list
 * of LinkedListNodes as an argument
 *
 * clearLinkedList() frees all LinkedListNodes
 * from memory
 */
void clearLinkedList(LinkedListNode **listPtr) {

	// checking for NULL pointer argument
	if (listPtr == NULL) {

		printf("\nCannot clear string linked "
				"list with a NULL head "
				"node pointer argument\n");
		return;
	}

	// clearing all LinkedListNodes
	LinkedListNode *currNodePtr = *listPtr;
	LinkedListNode *nextNodePtr;

	while (currNodePtr != NULL) {

		nextNodePtr = currNodePtr->next;
		free(currNodePtr);
		currNodePtr = nextNodePtr;	
	}

	*listPtr = NULL;
	return;
}

/*
 * removeFromLinkedList() takes a pointer to a
 * list of LinkedListNodes and a string as arguments
 *
 * removeFromLinkedList() removes every LinkedListNode 
 * with listString as its name data member and relinks
 * other LinkedListNodes accordingly
 */
void removeFromLinkedList(LinkedListNode **listPtr, char *listString) {

	// checking for NULL pointer arguments
	if (listString == NULL) {
		printf("\nCannot remove string from linked "
				"list with no string name "
				"argument\n");
		return;
	}
	if (listPtr == NULL) {
		printf("\nCannot remove %s from linked "
				"list without a list pointer "
				"argument\n", listString);
		return;
	}

	LinkedListNode *currNodePtr = *listPtr;
	LinkedListNode *nextNodePtr = NULL;
	int listCounter = 0;
	// looping through all LinkedListNodes
	while (currNodePtr != NULL) {
		listCounter++;
		nextNodePtr = currNodePtr->next;
		// if listString matches, removing currNodePtr
		if ( strcmp(currNodePtr->name, listString) == 0 ) {
			if (currNodePtr == *listPtr) {
				*listPtr = nextNodePtr;
			}
			if (currNodePtr->prev != NULL) {
				currNodePtr->prev->next = nextNodePtr;
			}
			if (nextNodePtr != NULL) {
				nextNodePtr->prev = currNodePtr->prev;
			}
			currNodePtr->next = NULL;
			currNodePtr->prev = NULL;
			free(currNodePtr);
			listCounter--;
		}
		currNodePtr = nextNodePtr;
	}

	if (*listPtr != NULL) {
		// remove OR if needed
		if ( (strcmp( (*listPtr)->name, "OR") == 0) && (listCounter <= 2) ) {
			removeFromLinkedList(listPtr, "OR");	
		}
	}

	return;
}
