#include <stdio.h>
#include <string.h> 
#include "lib/hospital.h"
#include "../lib/errors.h"

int main(void) {
    QueueNode** head = initHead();
    readFromFile(head, "names.txt");

    printQueue(head);
}