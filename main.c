#include <stdio.h>
#include <stdlib.h>

enum STATE {START, II, III, IV, F1, F2};
typedef enum STATE STATE;

char* getNextNumber(FILE *file);
STATE start(int c, char cType, char* number, int* numIndex);
STATE ii(int c, char cType, char* number, int* numIndex);
STATE iii(int c, char cType, char* number, int* numIndex);
STATE iv(int c, char cType, char* number, int* numIndex);


int main (void){
    FILE *file;
    file = fopen("file.txt", "rb");
    if(!file){
        printf("Could not open the file.\n");
        exit(EXIT_FAILURE);
    }else{
        printf("file opened!\n");
    } 

    char* number;
    for(int i=0;i<3;i++){
        number = getNextNumber(file);
        printf("Next number is: %s\n", number);
    } 

    free(number);
    printf("\nFinishing program..\n");
    return 0;
}

char* getNextNumber(FILE *file){
    STATE state = START;
    
    //Recognizes numbers until 7 digits
    char* number = (char*) malloc(sizeof(char) * 100);
    int* numIndex = (int*) malloc(sizeof(int));
    *numIndex = 0;

    int c;
    char cType;
    int index;
    char possibleChar[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

    while((c=fgetc(file)) != EOF){
        //check the type of the character(i.e, N, *, .)
            index = -1;
            for(int i = 0; i<11; i++){
                if((char)c == possibleChar[i]){
                    index = i;
                }
            }
           
            if(index <= 9 && index > -1){
                cType = 'N';
            }else if(index == 10){
                cType = '.';
            }else if(index == -1){
                cType = '*';
            }

        switch(state){
            case START:
                state = start(c, cType, number, numIndex);    
                break;
            case II:
                state = ii(c, cType, number, numIndex);
                break;
            case III:
                state = iii(c, cType, number, numIndex);
                break;
            case IV:
                state = iv(c, cType, number, numIndex);
                break;
            case F1:
                free(numIndex);
                return number;
            case F2:
                free(numIndex);
                return number;
        }
    }
}

STATE start(int c, char cType, char* number, int* numIndex){
    if(cType == 'N'){
        number[*numIndex] = (char)c;
        *numIndex += 1;
        return II;
    }else if(cType == '*' || cType == '.'){
        return START;
    }
}

STATE ii(int c, char cType, char* number, int* numIndex){
    if(cType == 'N'){
        number[*numIndex] = (char)c;
        *numIndex += 1;
        return II; 
    }else if(cType == '.'){
        number[*numIndex] = (char)c;
        *numIndex += 1;
        return III;
    }else if(cType == '*'){
        return F1;
    }
}

STATE iii(int c, char cType, char* number, int* numIndex){
    if(cType == 'N'){
        number[*numIndex] = (char)c;
        *numIndex += 1;
        return IV;
    }else if(cType == '*' || cType == '.'){
        *numIndex = 0;
        return START;
    }
}

STATE iv(int c, char cType, char* number, int* numIndex){
    if(cType == 'N'){
        number[*numIndex] = (char)c;
        *numIndex += 1;
        return IV;
    }else if(cType == '*' || cType == '.'){
        return F2;
    }
}
