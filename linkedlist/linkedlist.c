#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/errors.h"

typedef struct LinkedListNodeTag {
    int data;
    struct LinkedListNodeTag* next;
} LinkedListNode;

LinkedListNode* initNode(int d);
LinkedListNode** initHead();
bool isEmpty(LinkedListNode** head);
bool areEqual(LinkedListNode* nodeOne, LinkedListNode* nodeTwo);
void insert(LinkedListNode** head, int d);
void delete(LinkedListNode** head, LinkedListNode* key);
void printList(LinkedListNode** head);

int main(void);

LinkedListNode* initNode(int d) {
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    if(!node) raise(MEMERR, "Allocation failed");

    node->data = d;
    node->next = NULL;

    return node;
}

LinkedListNode** initHead() {
    LinkedListNode** head = malloc(sizeof(LinkedListNode*));
    if(!head) raise(MEMERR, "Allocation failed");

    *head = NULL;

    return head;
}

bool isEmpty(LinkedListNode** head) {
    return (*head == NULL);
}

bool areEqual(LinkedListNode* nodeOne, LinkedListNode* nodeTwo) {
    return (nodeOne->data == nodeTwo->data);
}

void insert(LinkedListNode** head, int d) {
    LinkedListNode* newNode = initNode(d);

    if(isEmpty(head)) {
        *head = newNode;
        (*head)->next = NULL;
    }
    else {
        LinkedListNode* it = *head;

        while(it->next != NULL) {
            it = it->next;
        }

        it->next = newNode;
    }
}

void delete(LinkedListNode** head, LinkedListNode* key) {
    if(isEmpty(head)) raise(LISTERR, "Empty List");
    if(!key) raise(LISTERR, "NULL node");

    if (areEqual(*head, key)) {
        LinkedListNode* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    bool found = false;
    for(LinkedListNode* it = *head; it->next != NULL && !found; it = it->next) {
        if(areEqual(it->next, key)) {
            LinkedListNode* curr = it->next;
            it->next = curr->next;

            free(curr);
            found = true;
        }
    }
}

void printList(LinkedListNode** head) {
    for(LinkedListNode* it = *head; it != NULL; it = it->next) {
        printf("%d ", it->data);
    }
    puts("");
}