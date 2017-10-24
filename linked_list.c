/*
*
* linked_list.c
*
* cs149 section 1
*
* hw 4
*
* John Kennedy 
* 001462826
*
*/

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INT_MIN	-1*pow(2,31)
#define INT_MAX (pow(2,31) - 1) 

Node* createNode(int node_id, void* item)				// creates and sets the vars for a node
{
	Node* node =  (Node*)malloc(sizeof(Node)); 
	node->next = NULL; 
	node->prev = NULL; 
	node->item = item; 
	node->node_id = node_id; 
	return node; 
}

LinkedList* createLinkedList()		// creates and sets the vars for a LinkedList
{
	
	LinkedList* ret = (LinkedList*)malloc(sizeof(LinkedList));
	ret->head = createNode(INT_MIN,"head"); 
	ret->tail = createNode(INT_MAX,"tail"); 
	ret->head->next = ret->tail; 
	ret->tail->prev = ret->head; 
	ret->count = 0; 
	return ret; 
}

void insertItem(LinkedList* list, int node_id, void* item)
{
	Node* new = createNode(node_id, item); 

	Node* ptr = list->head; 

	while(new->node_id > ptr->node_id)
	{
		ptr = ptr->next; 
	}

	new->next = ptr; 
	new->prev = ptr->prev; 
	
	new->prev->next = new; 
	new->next->prev = new; 
	list->count++; 
	return; 
}

void* removeItem(LinkedList* list, int node_id)
{
	Node* ptr = list->head->next; 
	while(ptr != list->tail)
	{
		if(ptr->node_id == node_id)break; 
		ptr = ptr->next; 
	}
	if(ptr == list->tail)return NULL; 

	void* item = ptr->item; 
	ptr->prev->next = ptr->next; 
	ptr->next->prev = ptr->prev;
	free(ptr); 
	list->count--; 
	return item; 
}
void* peekItem(LinkedList* list, int node_id) // returns NULL if node_id not present
{
	Node* ptr = list->head->next; 
	while(ptr != list->tail)
	{
		if(ptr->node_id == node_id)break; 
		ptr = ptr->next; 
	}
	if(ptr == list->tail)return NULL; 
	return ptr->item; 
	
}
void enqueue(LinkedList* list, int node_id, void* item)
{
	Node* new = createNode(node_id, item); 
	Node* ptr = list->tail; 
	
	new->prev = list->tail->prev; 
	new->next = list->tail; 
	
	new->prev->next = new; 
	list->tail->prev = new; 	
	list->count++; 
	return; 
	
}
void* dequeue(LinkedList* list)
{
	// returns item from the start of list. 
	if(list->count == 0) return NULL; 
	 
	return removeItem(list, list->head->next->node_id); 	

}
void* peekOrdinal(LinkedList* list, int ordinal)
{
	// returns NULL if ordinal >= count
	if(ordinal >= list->count)return NULL; 
	Node* ptr = list->head->next; 
	while(ordinal > 0)
	{
		ptr = ptr->next;
		ordinal--; 
	}
	return ptr->item; 
}
int peekOrdinalId(LinkedList* list, int ordinal)
{
	// returns NULL if ordinal >= count
	if(ordinal >= list->count)return INT_MIN; 
	Node* ptr = list->head->next; 
	while(ordinal > 0)
	{
		ptr = ptr->next;
		ordinal--; 
	}
	return ptr->node_id; 
}
	

