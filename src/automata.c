#include <stdio.h>
#include <stdlib.h>
#include "automata.h"

int getNextNumber(FILE *file, char* number, int* numIndex){
    STATE state = START;
    *numIndex = 0;

    int currentChar;
    char charType;

    while((currentChar=fgetc(file)) != EOF){
        charType = getCharType(currentChar); //check the type of the character(i.e, Digit(D), dot(.), other(*))
        if(charType == -1){
            printf("It wasn't possible to identify the next character (%c).\nFinishing getNextNumber function...\nFinishing program....", currentChar);
            exit(EXIT_FAILURE);
        }

        switch(state){
            case START:
                state = start(currentChar, charType, number, numIndex);    
                break;
            case II:
                state = ii(currentChar, charType, number, numIndex);
                break;
            case III:
                state = iii(currentChar, charType, number, numIndex);
                break;
            case IV:
                state = iv(currentChar, charType, number, numIndex);
                break;
            default:
                return 0;
        }
    }
    
    return -1;
}

char getCharType(int currentChar){
    char possibleChar[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    int index = -1;

    for(int i = 0; i<11; i++){
        if((char)currentChar == possibleChar[i]){
            index = i;
        }
    }
    
    if(index <= 9 && index > -1){
        return 'D';
    }else if(index == 10){
        return '.';
    }else if(index == -1){
        return '*';
    }else{
        return -1;
    }
}

STATE start(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'D'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return II;
    }else if(charType == '*' || charType == '.'){
        return START;
    }else{
        return -1;
    }
}

STATE ii(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'D'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return II; 
    }else if(charType == '.'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return III;
    }else if(charType == '*'){
        number[*numIndex] = '\0';
        return F1;
    }else{
        return -1;
    }
}

STATE iii(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'D'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return IV;
    }else if(charType == '*' || charType == '.'){
        *numIndex = 0;
        return START;
    }else{
        return -1;
    }
}

STATE iv(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'D'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return IV;
    }else if(charType == '*' || charType == '.'){
        number[*numIndex] = '\0';
        return F2;
    }else{
        return -1;
    }
}