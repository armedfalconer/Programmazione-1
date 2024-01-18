#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/errors.h"

typedef struct DoubleLinkedListTag {
    int data;
    struct DoubleLinkedListTag* next;
    struct DoubleLinkedListTag* previous;
} DoubleLinkedList;

DoubleLinkedList* initNode(int d);
DoubleLinkedList** initHead();
bool isEmpty(DoubleLinkedList** head);
bool areEqual(DoubleLinkedList* nodeOne, DoubleLinkedList* nodeTwo);
void insert(DoubleLinkedList** head, int d);
void delete(DoubleLinkedList** head, DoubleLinkedList* key);
void printList(DoubleLinkedList** head);

int main(void) {
    DoubleLinkedList** d = initHead();
    for(int i = 0; i < 20; i++) insert(d, i);
    for(int i = 0; i < 10; i++) {
        if(i % 2 == 0) {
            DoubleLinkedList* a = initNode(i);
            delete(d, a);
        }
        
    }
    printList(d);
}

DoubleLinkedList* initNode(int d) {
    DoubleLinkedList* node = malloc(sizeof(DoubleLinkedList));
    if(!node) raise(MEMERR, "Allocation failed");

    node->data = d;
    node->next = NULL;
    node->previous = NULL;

    return node;
}

DoubleLinkedList** initHead() {
    DoubleLinkedList** head = malloc(sizeof(DoubleLinkedList*));
    if(!head) raise(MEMERR, "Allocation failed");

    *head = NULL;

    return head;
}

bool isEmpty(DoubleLinkedList** head) {
    return (*head == NULL);
}

bool areEqual(DoubleLinkedList* nodeOne, DoubleLinkedList* nodeTwo) {
    return (nodeOne->data == nodeTwo->data);
}

void insert(DoubleLinkedList** head, int d) {
    DoubleLinkedList* newNode = initNode(d);

    if(isEmpty(head)) {
        *head = newNode;
        (*head)->next = NULL;
        (*head)->previous = NULL;
    }
    else {
        DoubleLinkedList* it = *head;

        while(it->next != NULL) {
            it = it->next;
        }

        newNode->previous = it;
        it->next = newNode; 
    }
}

void delete(DoubleLinkedList** head, DoubleLinkedList* key) {
    if (isEmpty(head)) {
        raise(LISTERR, "Empty List");
    }
    if (!key) {
        raise(LISTERR, "NULL node");
    }

    // If the key is in the head node
    if (areEqual(*head, key)) {
        *head = (*head)->next;
        if (*head) {
            (*head)->previous = NULL;
        }
        free(key);
        return;
    }

    bool found = false;
    for (DoubleLinkedList* it = *head; it != NULL && !found; it = it->next) {
        if (areEqual(it, key)) {
            // Update the links to remove the node
            if(it->previous) {
                it->previous->next = it->next;
            }
            if(it->next) {
                it->next->previous = it->previous;
            }

            // Free the memory of the node
            free(it);
            found = true;
        }
    }
}

void printList(DoubleLinkedList** head) {
    for(DoubleLinkedList* it = *head; it != NULL; it = it->next) {
        printf("%d ", it->data);
    }
    puts("");
}