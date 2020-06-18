#include <stdio.h>
#include <stdlib.h>

enum STATE {START, II, III, IV, F1, F2};
typedef enum STATE STATE;


int getNextNumber(FILE *file, char* number, int* numIndex);
STATE start(int currentChar, char charType, char* number, int* numIndex);
STATE ii(int currentChar, char charType, char* number, int* numIndex);
STATE iii(int currentChar, char charType, char* number, int* numIndex);
STATE iv(int currentChar, char charType, char* number, int* numIndex);


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
    for(int i=0;i<3;i++){
        getNextNumber(file, number, numIndex);
        printf("Next number is: %s\n", number);
    } 

    free(number);
    free(numIndex);
    printf("\nFinishing program..\n");
    return 0;
}

int getNextNumber(FILE *file, char* number, int* numIndex){
    STATE state = START;
    *numIndex = 0;

    int currentChar;
    char charType;
    char possibleChar[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    int index;

    while((currentChar=fgetc(file)) != EOF){
        //check the type of the character(i.e, N, *, .)
            index = -1;
            for(int i = 0; i<11; i++){
                if((char)currentChar == possibleChar[i]){
                    index = i;
                }
            }
           
            if(index <= 9 && index > -1){
                charType = 'N';
            }else if(index == 10){
                charType = '.';
            }else if(index == -1){
                charType = '*';
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
}

STATE start(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'N'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return II;
    }else if(charType == '*' || charType == '.'){
        return START;
    }
}

STATE ii(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'N'){
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
    }
}

STATE iii(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'N'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return IV;
    }else if(charType == '*' || charType == '.'){
        *numIndex = 0;
        return START;
    }
}

STATE iv(int currentChar, char charType, char* number, int* numIndex){
    if(charType == 'N'){
        number[*numIndex] = (char)currentChar;
        *numIndex += 1;
        return IV;
    }else if(charType == '*' || charType == '.'){
        number[*numIndex] = '\0';
        return F2;
    }
}
