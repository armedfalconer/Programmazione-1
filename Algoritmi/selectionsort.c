#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int* array, size_t size);

#define SIZE 40
#define MAX 100

int main(void) {
    srand(time(NULL));
    int array[SIZE];
    for(size_t i = 0; i < SIZE; i++) array[i] = rand() % MAX;
    selectionsort(array, SIZE);

    for(size_t i = 0; i < SIZE; i++) printf("%d ", array[i]);
    puts("");   
}

void selectionSort(int* array, size_t size) {
    for(size_t i = 0; i < size-1; i++) {
        size_t indxmin = i;
        
        for(size_t j = i+1; j < size; j++) {
            if(array[j] < array[indxmin]) indxmin = j;
        }

        if(indxmin != i) {
            int tmp = array[i];
            array[i] = array[indxmin];
            array[indxmin] = tmp;
        }
    }
}