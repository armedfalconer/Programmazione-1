#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/errors.h"
#include "hospital.h"

Customer* initCustomer(char* name, char* surname, unsigned short age, unsigned short priority) {
    // variable
    Customer* c = malloc(sizeof(Customer));
    if(!c) raise(MEMERR, "Allocation failed");
    
    // name
    c->name = malloc(sizeof(char)*strlen(name)+1);
    if(!c->name) raise(MEMERR, "Allocation failed");
    strcpy(c->name, name);
    c->name[strlen(c->name)+1] = 0;

    // surname
    c->surname = malloc(sizeof(char)*strlen(surname)+1);
    if(!c->surname) raise(MEMERR, "Allocation failed");
    strcpy(c->surname, surname);
    c->surname[strlen(c->surname)+1] = 0;

    // age
    c->age = age;
    c->priority = priority;

    return c;
}

void freeCustomer(Customer* c) {
    free(c->name);
    free(c->surname);
    free(c);
}

void printCustomer(const Customer* c) {
    printf("%s %s %hu %hu\n", c->name, c->surname, c->age, c->priority);
}


QueueNode* initNode(Customer* c) {
    QueueNode* node = malloc(sizeof(QueueNode));
    if(!node) raise(QUEUERR, "Allocation failed");

    node->cust = c;
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

void enqueue(QueueNode** head, Customer* c) {
    QueueNode* newNode = initNode(c);
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
        freeCustomer(current->cust);
        free(current);
        current = next;
    }

    free(top);
}

void printQueue(QueueNode** head) {
    for(QueueNode* it = *head; it != NULL; it = it->next) {
        printCustomer(it->cust);
    }
}


void getString(FILE* fp, char** string) {
    unsigned int size = 1;
    char check;
    *string = (char*)malloc(size * sizeof(char));

    if(!(*string)) {
        fprintf(stderr, "ERROR: Memory Allocation\n");
        exit(EXIT_FAILURE);
    }

    do {
        check = fgetc(fp);

        if (check != EOF && check != '\n') {
            (*string)[size - 1] = check;
            size++;
            *string = realloc(*string, size * sizeof(char));

            if(!(*string)) {
                fprintf(stderr, "ERROR: Memory Allocation\n");
                exit(EXIT_FAILURE);
            }
        }
    } while(check != EOF && check != '\n');

    (*string)[size - 1] = '\0';
}

void readFromFile(QueueNode** head, char* fileName) {
    FILE* fp = fopen("names.txt", "r");
    if(!fp) raise(FILERR, "File not found");
    
    char* string;

    while(!feof(fp)) {
        getString(fp, &string);

        char* name;
        char* surname;
        unsigned short age;
        unsigned short priority;

        // mame
        char* tok = strtok(string, " ");
        if(tok) {
            name = malloc(sizeof(char)*strlen(tok)+1);
            strcpy(name, tok);
            name[strlen(name)] = 0; 
        }

        
        // surname
        tok = strtok(NULL, " ");
        if(tok) {
            surname = malloc(sizeof(char)*strlen(tok)+1);
            strcpy(surname, tok);
            surname[strlen(surname)] = 0;
        }
               
        // age
        tok = strtok(NULL, " ");
        if(tok) {
            age = atoi(tok);
        }

        // priority
        tok = strtok(NULL, " ");
        if(tok) {
            priority = atoi(tok);
        }
       
        Customer* c = initCustomer(name, surname, age, priority);
        enqueue(head, c);        
    }
}

/*
void selectionSort(QueueNode** head) {
    for(QueueNode* it = *head; it != NULL; it = it->next) {
        QueueNode* currMin = it;
        QueueNode* itPrev = NULL;

        for(QueueNode* jt = it->next; jt != NULL; jt = jt = jt->next) {
            if(jt->cust->priority < currMin->cust->priority) currMin = jt;
        }

        if(currMin == it) {

        }
    }
}*/



