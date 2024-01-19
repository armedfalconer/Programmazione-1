#ifndef HOSPITAL_H
    #define HOSPITAL_H
    
    #include <stdbool.h>

    typedef struct CustomerTag {
        char* name;
        char* surname;
        unsigned short age;
        unsigned short priority;
    } Customer;

    typedef struct QueueNodeTag {
        Customer* cust;
        struct QueueNodeTag* next;
    } QueueNode;

    // customer
    Customer* initCustomer(char* name, char* surname, unsigned short age, unsigned short priority);
    void freeCustomer(Customer* c);
    void printCustomer(const Customer* c);

    // Queue
    QueueNode* initNode(Customer* c);
    QueueNode** initHead();
    bool isEmpty(QueueNode** head);
    void enqueue(QueueNode** head, Customer* c);
    void dequeue(QueueNode** head);
    void freeQueue(QueueNode** head);
    void selectionSort(QueueNode** head);
    void printQueue(QueueNode** head);

    // file
    void readFromFile(QueueNode** head, char* fileName);

#endif // HOSPITAL_H