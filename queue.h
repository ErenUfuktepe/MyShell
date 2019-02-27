#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
	char *data;
	struct Node* next;
};

struct Node *createNode(char* data) ;
struct Node *enqueue(char* data);
void dequeue();
int number_of_nodes();
void display();


