#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "exam.h"

void raise(char* errType, char* err) {
    fprintf(stderr, "%s error: %s\n", errType, err);
    exit(EXIT_FAILURE);
}

bool checkExtension(char* ext, char* fileName) {
    size_t extLen = strlen(ext);
    size_t fileNameLen = strlen(fileName);

    for(size_t i = 0; i < extLen; i++) {
        if(fileName[i+fileNameLen-extLen] != ext[i]) return false;
    }

    return true;
}

Record decodeParameters(int argc, char** argv) {
    if(argc != 3) raise(PARAMERR, "Wrong parameters number");
    Record par;
    
    sscanf(argv[1], "%hd", &par.n);
    if(par.n < 5 || par.n > 20) raise(PARAMERR, "First parameter < 5 or > 20");

    par.fileName = (char*)malloc(sizeof(char)*strlen(argv[2]));
    strcpy(par.fileName, argv[2]);
    if(!checkExtension(".dat", par.fileName)) raise(PARAMERR, "Wrong file extension");

    return par;
}

void printRecord(Record a) {
    printf("Integer: %d\nFile name: %s\n", a.n, a.fileName);
}

Array readInput(char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if(!fp) raise(FILERR, "File not found");

    int inp, counter = 0;
    
    while(fscanf(fp, "%d", &inp) != EOF) {
        counter++;
    }

    Array arr;
    arr.data = (int*)malloc(sizeof(int)*counter);
    if(!arr.data) raise(MEMERR, "Allocation failed");
    arr.size = counter;
    inp = 0;

    rewind(fp);

    for(size_t i = 0; i < arr.size || inp != EOF; i++) {
        inp = fscanf(fp, "%d", &arr.data[i]);
        if(inp != 1 && inp != EOF) raise(INPERR, "Wrong input");
    }
    
    fclose(fp);

    return arr;
}

void printArray(Array arr) {
    for(size_t i = 0; i < arr.size; i++) {
        printf("%d\n", arr.data[i]);
    }
}

StackNode* initNode(float d) {
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

void push(StackNode** top, float d) {
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

void createStack(StackNode** top, Array arr, short n) {
    push(top, arr.data[0]);

    for(size_t i = 1; i < arr.size; i++) {
        if(arr.data[i] % n != 0) {
            float tmp = peek(top)->data;
            pop(top);
            tmp = (float)(tmp + arr.data[i])/2.0;
            push(top, tmp);
        }
        else {
            push(top, arr.data[i]);   
        }
    }
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
        printf("%f\n", it->data);
    }
}

float* findMinMaxMean(StackNode** top) {
    if(isEmpty(top)) raise(STACKERR, "Empty stack");
    
    // values[0] = min, values[1] = max, values[2] = average
    float* values = malloc(sizeof(float)*3);
    if(!values) raise(MEMERR, "Allocation failed");
    size_t counter = 0;

    // setting the elements
    values[0] = peek(top)->data;
    values[1] = values[0];
    values[2] = 0;

    for(StackNode* it = *top; it != NULL; it = it->next) {
        if(it->data < values[0]) values[0] = it->data; // min
        if(it->data > values[1]) values[1] = it->data; // max

        // average
        values[2] += it->data;
        counter++;
    }   

    values[2] = values[2] / counter;

    return values;
}