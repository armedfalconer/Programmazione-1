#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/errors.h"

typedef struct QueueNodeTag {
    int data;
    struct QueueNodeTag* next;
} QueueNode;

QueueNode* initNode(int d);
QueueNode** initHead();
bool isEmpty(QueueNode** head);
void enqueue(QueueNode** head, int d);
void dequeue(QueueNode** head);
void freeQueue(QueueNode** head);
void printList(QueueNode** head);

int main(void) {
    QueueNode** head = initHead();
    for(int i = 0; i < 20; i++) enqueue(head, i+1);
    printList(head);
    for(int i = 0; i < 20; i++) {
        if(i % 2 == 0) dequeue(head);
    }
    printList(head);
    freeQueue(head);
}

QueueNode* initNode(int d) {
    QueueNode* node = malloc(sizeof(QueueNode));
    if(!node) raise(QUEUERR, "Allocation failed");

    node->data = d;
    node->next = NULL;

    return node;
}

QueueNode** initHead() {
    QueueNode** head = malloc(sizeof(QueueNode*));
    if(!head) raise(QUEUERR, "Allocation failed");

    *head = NULL;

    return head;
}

bool isEmpty(QueueNode** head) {
    return (*head == NULL);
}

void enqueue(QueueNode** head, int d) {
    QueueNode* newNode = initNode(d);
    if(isEmpty(head)) {
        *head = newNode;
    }
    else {
        QueueNode* it = *head;

        while(it->next != NULL) {
            it = it->next;
        }

        it->next = newNode;
    }
}

void dequeue(QueueNode** head) {
    if(isEmpty(head)) raise(QUEUERR, "Empty queue");

    QueueNode* tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void freeQueue(QueueNode** top) {
    QueueNode* current = *top;
    QueueNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(top);
}

void printList(QueueNode** head) {
    for(QueueNode* it = *head; it != NULL; it = it->next) {
        printf("%d ", it->data);
    }
    puts("");
}