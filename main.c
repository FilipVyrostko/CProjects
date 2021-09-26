#include <stdio.h>
#include "stdlib.h"


typedef struct {
    int value;
    struct Node *next;
}Node, *NodePtr;


typedef struct {
    NodePtr top, tail;
}List, *ListPtr;

NodePtr make_new_node(int);
void print_list(NodePtr);

int main() {
    char buffer[100];
    int size = 0, value = 0;
    NodePtr top = NULL, last = NULL, np;

    printf("Enter the size of the linked list: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d", &size);

    for (int i=0; i<size; i++) {
        printf("Enter a value for a node number %d: ", i);
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%d", &value);
        np = make_new_node(value);
        if (top == NULL) top = np;
        else last -> next = (struct Node *) np;
        last = np;
    }

    print_list(top);

}


NodePtr make_new_node(int value) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    np -> value = value;
    np -> next = NULL;
    return np;
}

void print_list(NodePtr node) {
    while (node != NULL) {
        printf("%d \n", node -> value);
        node = (NodePtr) node->next;
    }
}