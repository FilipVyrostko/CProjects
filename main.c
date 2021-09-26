#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct {
    char ch;
} StackData;

typedef struct node {
    StackData data;
    struct node *next;
} Node, *NodePtr;

typedef struct stack {
    int size;
    NodePtr top;
} Stack, *StackPtr;


StackPtr initialize();
StackData pop(StackPtr);
void push(StackPtr, StackData);
int isEmpty(StackPtr);


int main() {
    char buffer[100];
    int i = 0;
    StackData data;
    StackPtr sp = initialize();

    printf("\nEnter some string:\n");
    fgets(buffer, 100, stdin);

    while (buffer[i] != '\n'){
        data.ch = buffer[i];
        push(sp, data);
        i++;
    }

    printf("\nString in reversed order:\n");

    while (!isEmpty(sp)) {
        data = pop(sp);
        printf("%c", data.ch);
    }
}


StackPtr initialize() {
    StackPtr sp = (StackPtr) malloc(sizeof(Stack));
    sp -> top = NULL;
    sp -> size = SIZE;
    return sp;
}

void push(StackPtr sp, StackData data) {

    if (sp -> size == 0) {
        printf("\nStack Overflow\n");
        exit(-1);
    }

    NodePtr np = malloc(sizeof(Node));
    np -> data = data;
    np -> next = sp -> top;
    sp -> top = np;
    sp -> size -= 1;
}

StackData pop(StackPtr sp) {
    if (isEmpty(sp)) {
        printf("\nStack Underflow\n");
        exit(1);
    } else {
        StackData data = sp -> top -> data;
        NodePtr temp = sp -> top;
        sp -> top = sp -> top -> next;
        sp -> size += 1;
        free(temp);
        return data;
    }
}

int isEmpty(StackPtr sp) {
    return sp -> top == NULL;
}