// exam.h
#ifndef EXAM_H
    #define EXAM_H
    #include <stdbool.h>

    // errors macro
    #define MEMERR "Memory"
    #define PARAMERR "Parameters"
    #define FILERR "File"
    #define INPERR "Input"
    #define STACKERR "Stack"

    typedef struct RecordTag {
        short n;
        char* fileName;
    } Record;

    typedef struct ArrayTag {
        int* data;
        size_t size;
    } Array;

    typedef struct StackNodeTag {
        float data;
        struct StackNodeTag* next;
    } StackNode;

    // general function
    void raise(char* errType, char* err);
    bool checkExtension(char* ext, char* fileName);

    // Record functions
    Record decodeParameters(int argc, char** argv);
    void printRecord(Record a);

    // Array functions
    Array readInput(char* fileName);
    void printArray(Array arr);

    // Stack functions
    StackNode* initNode(float d);
    StackNode** initTop();
    bool isEmpty(StackNode** top);
    void push(StackNode** top, float d);
    StackNode* peek(StackNode** top);
    void pop(StackNode** top);
    void createStack(StackNode** top, Array arr, short n);
    void freeStack(StackNode** top);
    void printStack(StackNode** top);

    float* findMinMaxMean(StackNode** top);


#endif // EXAM_H