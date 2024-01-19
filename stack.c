#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "lib/errors.h"

typedef struct StackNodeTag {
    int data;
    struct StackNodeTag* next;
} StackNode;

StackNode* initNode(int d);
StackNode** initTop();
bool isEmpty(StackNode** top);
void push(StackNode** top, int d);
StackNode* peek(StackNode** top);
void pop(StackNode** top);
size_t stackSize(StackNode** top);
void freeStack(StackNode** top);
void printStack(StackNode** top);

int main(void);

StackNode* initNode(int d) {
    StackNode* node = malloc(sizeof(StackNode));
    if(!node) raise(MEMERR, "Allocation failed");

    node->data = d;
    node->next = NULL;

    return node;
}

StackNode** initTop() {
    StackNode** top = malloc(sizeof(StackNode*));
    if(!top) raise(MEMERR, "Allocation failed");
    *top = NULL;

    return top;
}

bool isEmpty(StackNode** top) {
    return (*top == NULL);
}

void push(StackNode** top, int d) {
    StackNode* newNode = initNode(d);

    if(isEmpty(top)) {
        *top = newNode;
        (*top)->next = NULL;
    }
    else {
        newNode->next = *top;
        *top = newNode;
    }
}

StackNode* peek(StackNode** top) {
    return *top;
}

void pop(StackNode** top) {
    if(isEmpty(top)) raise(STACKERR, "Empty Stack pop");

    StackNode* tmp = *top;
    *top = (*top)->next;
    free(tmp);
}

size_t stackSize(StackNode** top) {
    size_t counter = 0;

    for(StackNode* it = *top; it != NULL; it = it->next) {
        counter++;
    }

    return counter;
}

void freeStack(StackNode** top) {
    StackNode* current = *top;
    StackNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(top);
}

void printStack(StackNode** top) {
    for(StackNode* it = *top; it != NULL; it = it->next) {
        printf("%d\n", it->data);
    }
}
