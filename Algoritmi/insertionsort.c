#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int* array, size_t size);

#define SIZE 40
#define MAX 100

int main(void) {
    srand(time(NULL));
    int array[SIZE];
    for(size_t i = 0; i < SIZE; i++) array[i] = rand() % MAX;
    insertionSort(array, SIZE);
    for(size_t i = 0; i < SIZE; i++) printf("%d ", array[i]);
    
     
}

void insertionSort(int* array, size_t size) {
    for(size_t i = 1; i < size; i++) {
        for(size_t j = i; j > 0 && array[j-1] > array[j]; j--) {
            int tmp = array[j];
            array[j] = array[j-1];
            array[j-1] = tmp;
        }
    }
}