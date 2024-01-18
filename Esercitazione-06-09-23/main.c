// compito 06/09/23
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "exam.h"

int main(int argc, char** argv) {
    
    // Point A
    Record par = decodeParameters(argc, argv);
    puts("POINT A: ");
    printRecord(par);
    puts("");

    // Point B
    Array a = readInput(par.fileName);
    puts("POINT B: ");
    printArray(a);
    puts("");

    // POINT C
    StackNode** P = initTop();
    createStack(P, a, par.n);
    puts("POINT C:");
    printStack(P);
    puts("");

    // POINT D
    float* values = findMinMaxMean(P);
    printf("Min: %f\nMax: %f\nAverage: %f\n", values[0], values[1], values[2]);

    freeStack(P);
    free(values);

    exit(EXIT_SUCCESS);
}
