#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

void raise(char* errType, char* err) {
    fprintf(stderr, "%s error: %s\n", errType, err);
    exit(EXIT_FAILURE);
}