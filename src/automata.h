enum STATE {START, II, III, IV, F1, F2};
typedef enum STATE STATE;


int getNextNumber(FILE *file, char* number, int* numIndex);
char getCharType(int currentChar);
STATE start(int currentChar, char charType, char* number, int* numIndex);
STATE ii(int currentChar, char charType, char* number, int* numIndex);
STATE iii(int currentChar, char charType, char* number, int* numIndex);
STATE iv(int currentChar, char charType, char* number, int* numIndex);