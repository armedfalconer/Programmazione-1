#ifndef ERRORS_H
    #define ERRORS_H

    #define MEMERR "Memory"
    #define PARAMERR "Parameters"
    #define FILERR "File"
    #define INPERR "Input"
    #define STACKERR "Stack"
    #define LISTERR "Linked List"
    #define QUEUERR "Queue"

    void raise(char* errType, char* err);

#endif // ERRORS_H