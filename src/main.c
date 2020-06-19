#include <stdio.h>
#include <stdlib.h>
#include "automata.h"

int main (void){
    FILE *file;
    file = fopen("file.txt", "rb");
    if(!file){
        printf("Could not open the file.\n");
        exit(EXIT_FAILURE);
    }else{
        printf("file opened!\n");
    } 

    char* number = (char*) malloc(sizeof(char) * 100);
    int* numIndex = (int*) malloc(sizeof(int));
    
    printf("Getting the first number..\n");
    char answer;
    do{
        if(getNextNumber(file, number, numIndex) == 0){
            printf("Next number is: %s\n", number);
        }else{
            printf("There aren't more numbers!\n");
            break;
        }

        printf("Do you want to get the next one?(Y|N)\n");
        scanf(" %c", &answer);

    }while(answer == 'Y' || answer == 'y');

    free(number);
    free(numIndex);
    fclose(file);
    printf("\nFinishing program..\n");
    return 0;
}