#include "queue.h"

#define SIZE 10

struct Node* head = NULL;//Queue's head
struct Node* tail = NULL;//Queue's tail

/*
 * Function:    createNode
 * Purpose:     creates new node
 * In arg:      data: node's data
 * Return val:  created node
 */
struct Node *createNode(char* data) 
{ 
    struct Node *node = (struct Node*)malloc(sizeof(struct Node)); 
    
    node->data = strdup(data);
    node->next = NULL; 

    return node; 
}

/*
 * Function:    enqueue
 * Purpose:     add new node to end of queue
 * In arg:      data: node's data
 * Return val:  new node which is added
 * Global var:  head, tail
 */
struct Node *enqueue(char* data)
{
    struct Node* temp = createNode(data);

    if(head == NULL && tail == NULL)
    {
	head = tail = temp;	
	return temp;
    }
    else
    {
	if(number_of_nodes() == SIZE)
        {
   	    dequeue();	
	}
	tail->next = temp;
	tail = temp;
	return temp;
    }
}

/*
 * Function:    dequeue
 * Purpose:     removes the head of the queue
 * Global var:  head
 */
void dequeue()
{
    struct Node *front = head;

    head = head->next;
    front->next = NULL;

    if(front == head)
    {
	head = NULL;
    }
    free(front);
}

/*
 * Function:    number_of_nodes
 * Purpose:     shows how many nodes exist in
 *		the queue
 * Return val:  number of nodes
 */
int number_of_nodes()
{
    int count = 1;
    struct Node *temp = head;

    while(temp->next != NULL)
    {
	temp = temp -> next;
	count++;
    }	
    return count;
}

/*
 * Function:    display
 * Purpose:     prints the queue elements
 * Global var:  head
 */
void display()
{
    struct Node *temp = head;	
    int count = 1;

    while(temp != NULL)
    {
	printf("[%d]%s\n",count,temp->data);
 	temp = temp -> next;
 	count++;
    }
}

