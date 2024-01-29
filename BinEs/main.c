#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BIN_READ "rb"
#define BIN_WRITE "wb"

typedef struct PersonTag {
    size_t nameLen;
    char* name;
    size_t surnameLen;
    char* surname;
    unsigned short age;
} Person;

typedef struct ArrayTag {
    Person** data;
    size_t size;
} Array;

Person* initPerson(char* name, char* surname, unsigned short age) {
    Person* pers = malloc(sizeof(Person));
    if (!pers) exit(EXIT_FAILURE);

    pers->nameLen = strlen(name);
    pers->name = malloc(sizeof(char) * (pers->nameLen + 1));
    if (!pers->name) exit(EXIT_FAILURE);
    strcpy(pers->name, name);

    pers->surnameLen = strlen(surname);
    pers->surname = malloc(sizeof(char) * (pers->surnameLen + 1));
    if (!pers->surname) exit(EXIT_FAILURE);
    strcpy(pers->surname, surname);

    pers->age = age;

    return pers;    
}

void printPerson(Person pers) {
    printf("%s %s %hu\n", pers.name, pers.surname, pers.age);
}

Person* parsePerson(const char *input) {
    char *token;
    char tempInput[strlen(input) + 1];
    strcpy(tempInput, input);

    // Allocate memory for the Person
    Person *person = malloc(sizeof(Person));
    if (!person) exit(EXIT_FAILURE);

    // Parsing name
    token = strtok(tempInput, " ");
    person->nameLen = strlen(token);
    person->name = malloc(sizeof(char) * (person->nameLen + 1)); // +1 for null terminator
    strcpy(person->name, token);

    // Parsing surname
    token = strtok(NULL, " ");
    person->surnameLen = strlen(token);
    person->surname = malloc(sizeof(char) * (person->surnameLen + 1)); // +1 for null terminator
    strcpy(person->surname, token);

    // Parsing age
    token = strtok(NULL, " ");
    person->age = atoi(token);

    return person;
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

Array getInput(FILE* fp) {
    Array arr;
    arr.size = 0;
    arr.data = malloc(sizeof(Person*));
    if (!arr.data) {
        fprintf(stderr, "ERROR: Memory Allocation\n");
        exit(EXIT_FAILURE);
    }

    char* inp;
    do {
        getString(fp, &inp);

        // Check if inp is not an empty string
        if (strlen(inp) > 0) {
            Person* pers = parsePerson(inp);
            arr.size++;
            arr.data = realloc(arr.data, sizeof(Person*) * arr.size);
            if (!arr.data) {
                fprintf(stderr, "ERROR: Memory Allocation\n");
                exit(EXIT_FAILURE);
            }
            arr.data[arr.size - 1] = pers;
        }
        free(inp); // Free the allocated memory for inp
    } while (!feof(fp));

    return arr;
}

void printArray(Array arr) {
    for(size_t i = 0; i < arr.size; i++) printPerson(*arr.data[i]);
}

void writeFile(char* fileName, Array arr) {
    FILE* fp = fopen(fileName, BIN_WRITE);
    if(!fp) exit(EXIT_FAILURE);

    // writing the size of array as first binary sequence
    fwrite(&arr.size, sizeof(size_t), 1, fp);

    for(size_t i = 0; i < arr.size; i++) {
        // how file are written:
        // <32 bit nameLen> <nameLen*8 bit name> <32 bit surnameLen> <surname> <16 bit age>

        fwrite(&arr.data[i]->nameLen, sizeof(size_t), 1, fp); // 32 bit name len
        fwrite(arr.data[i]->name, sizeof(char)*arr.data[i]->nameLen+1, 1, fp); // nameLen*8 bit name
        fwrite(&arr.data[i]->surnameLen, sizeof(size_t), 1, fp); // 32 bit surname len
        fwrite(arr.data[i]->surname, sizeof(char)*arr.data[i]->surnameLen+1, 1, fp); // surnameLen*8 bit surname
        fwrite(&arr.data[i]->age, sizeof(unsigned short), 1, fp); // 16 bit age
    }

    fclose(fp);
}

Array readFile(char* fileName) {
    FILE* fp = fopen(fileName, BIN_READ);
    if(!fp) exit(EXIT_FAILURE);

    Array arr;
        
    // reading the size of the array
    fread(&arr.size, sizeof(size_t), 1, fp);
    arr.data = malloc(sizeof(Person*)*arr.size);
    if(!arr.data) exit(EXIT_FAILURE);

    for(size_t i = 0; i < arr.size; i++) {
        arr.data[i] = malloc(sizeof(Person));
        if(!arr.data[i]) exit(EXIT_FAILURE);

        // how file are read:
        // <32 bit nameLen> <nameLen*8 bit name> <32 bit surnameLen> <surname> <16 bit age>

        // name len
        fread(&arr.data[i]->nameLen, sizeof(size_t), 1, fp); // 32 bit

        // allocating memory
        arr.data[i]->name = malloc(sizeof(char)*arr.data[i]->nameLen+1);
        if(!arr.data[i]->name) exit(EXIT_FAILURE);
        fread(arr.data[i]->name, sizeof(char)*arr.data[i]->nameLen+1, 1, fp); // nameLen*8 bit name

        // surname len
        fread(&arr.data[i]->surnameLen, sizeof(size_t), 1, fp); // 32 bit 

        // allocating memory
        arr.data[i]->surname = malloc(sizeof(char)*arr.data[i]->surnameLen+1);
        if(!arr.data[i]->surnameLen) exit(EXIT_FAILURE);
        fread(arr.data[i]->surname, sizeof(char)*arr.data[i]->surnameLen+1, 1, fp); // surnameLen*8 bit surname

        fread(&arr.data[i]->age, sizeof(unsigned short), 1, fp); // 16 bit age
    }
    
    return arr;
}

int main(void) {
    char* fileName = "data.dat";
    Array arr = getInput(stdin);

    puts("STARTING ARRAY: \n");
    printArray(arr);
    puts("\nWriting...");

    writeFile(fileName, arr);

    puts("File written\n");

    Array arrb = readFile(fileName);

    puts("Reading...");
    puts("ARRAY: \n");
    printArray(arrb);

    puts("\nEND OF THE PROGRAM");

    exit(EXIT_SUCCESS);
}
