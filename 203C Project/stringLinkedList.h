/*
 *
 *	Header file for string LinkedList ADT interface
 *
 *	In terms of this program, the string 
 *	LinkedList is used for recording a 
 *	Course's Degree programs and 
 *	prerequisite Course names
 *
 *	The following functions make these 
 *	Degree and prerequisite lists
 *	easy to add to and remove from
 */

#ifndef STRINGLINKEDLIST_H
#define STRINGLINKEDLIST_H

// struct for LinkedList Nodes
typedef struct linkedListNode {
	char *name;
	struct linkedListNode *next;
	struct linkedListNode *prev;
} LinkedListNode;


// interface

/*
 * initializes a LinkedListNode with
 * the given string argument 
 * 
 * in terms of this program, each
 * LinkedListNode will have a Degree
 * or prerequisite name string
 *
 * returns a pointer to the new node
 *
 * string - the string argument
 * used to fill in the new 
 * LinkedListNode's data member
 */
LinkedListNode* initListNode(char* string);

/*
 * inserts a new LinkedListNode after
 * the node specified, linking as needed
 *
 * nodePtr - pointer to the existing 
 * LinkedListNode we insert after
 * 
 * newNodePtr - pointer to the
 * LinkedListNode we want to insert into
 * the list
 */
void insertAfterListNode(LinkedListNode* nodePtr, LinkedListNode* newNodePtr);

/*
 * frees all LinkedListNodes after the
 * given list head argument and clears 
 * the list head reference
 *
 * listPtr - pointer to the LinkedListNode
 * pointer at the head of the list
 */
void clearLinkedList(LinkedListNode** listPtr);

/*
 * removes every LinkedListNode with the 
 * given string data member after the 
 * given list head argument
 *
 * relinks all other LinkedListNodes as
 * needed
 *
 * listPtr - pointer to the LinkedListNode
 * pointer at the head of the list
 *
 * listString - the string data member
 * we are searching the LinkedList for
 */
void removeFromLinkedList(LinkedListNode** listPtr, char* listString);

#endif
