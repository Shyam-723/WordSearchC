#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//I worked with Shyam Gupta on this project

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
int makeUpperCase(char* word);
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void checkSurroundings(char** block, char* word, int* count, int indexI, int indexJ);
// void checkSurroundings(char** arr, char* word);
int bSize;
int** searchPath;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...

    for(int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i)+ j));
        }
        printf("\n");
    }
    printf("\n");

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    int wordLength = makeUpperCase(word);
    int count, foundWord = 0;

    //Make 2D array of ints and assign each value to be == 0
    //This will be the grid that is printed at the end and is the search pattern
    // searchPath = (int**)malloc(bSize * sizeof(int*));
    // for (int i = 0; i < bSize; i++) {
    //     *(searchPath + i) = (int*)malloc(bSize * sizeof(int));
    //     for (int j = 0; j < bSize; j++) {
    //         *(*(searchPath + i) + j) = 0;
    //     }
    // } 
    searchPath = (int**)calloc(bSize,sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        *(searchPath + i) = (int*)calloc(bSize,sizeof(int));
    }    

    //Finds first letter and starts checking surrounding letters
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (*(*(arr + i)+ j) == *word) {
                *(*(searchPath + i) + j) = 1;
                count = 1;
                checkSurroundings(arr, word + 1, &count, i, j);

                if(count == wordLength){
                    foundWord++;
                }
            }
        }
    }

    if(!foundWord){
        printf("Word not found!\n");
    } else {
        for(int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                printf("%d ", *(*(searchPath + i)+ j));
            }
            printf("\n");
        }
    }    
    
}

int makeUpperCase(char* word) {
    int i;
    int length = 0;
    char* wordStart = word;

    while (*wordStart){
        if(*wordStart <= 96){
            // printf("Is Capital\n");
        } else {
            // printf("Is Not Capital\n");
            *wordStart -= 32;
        }
        wordStart++;
        length++;
    }    

    return length;
}


void checkSurroundings(char** block, char* word, int* count, int indexI, int indexJ) {
    //Oh my god the nested if statements
    int found = 0;
    if (*word != '\n') {
        for(int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                if (i >= indexI - 1 && i <= indexI + 1 ) {
                    if (j >= indexJ - 1 && j <= indexJ + 1) {
                        //Making sure we're not reusing the same letter
                        if (!(i == indexI && j == indexJ)) {
                            if (*(*(block + i)+ j) == *word) {
                                (*count)++;
                                *(*(searchPath + i)+ j) = *(*(searchPath + i)+ j) * 10 + *count;
                                checkSurroundings(block, word + 1, count, i, j);
                                found = 1;
                            }
                        }
                    }
                }
                if (found == 1) {
                    break;
                }
            }
            if (found == 1) {
                break;
            }           
        }
        
    }
}

