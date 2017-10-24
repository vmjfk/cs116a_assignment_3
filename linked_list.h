/*
*
* linked_list.h
*
* cs149 section 1
*
* hw 4
*
* John Kennedy 
* 001462826
*
*/
typedef struct node Node;
typedef struct linkedlist LinkedList; 

struct node {
	Node* next;
	Node* prev;
	void* item;
	int node_id;
};

struct linkedlist {
	Node* head;
	Node* tail; 
	int count; 
};
LinkedList* createLinkedList();

Node* createNode(int node_id, void* item);

void insertItem(LinkedList* list, int node_id, void* item);

void* removeItem(LinkedList* list, int node_id);

void* peekItem(LinkedList* list, int node_id); 

void enqueue(LinkedList* list, int node_id, void* item);

void* dequeue(LinkedList* list);

void* peekOrdinal(LinkedList* list, int ordinal);

int peekOrdinalId(LinkedList* list, int ordinal);

