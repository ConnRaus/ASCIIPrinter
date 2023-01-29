#include <stdio.h>

int main(int argc, char *argv[]) {
    //counts characters in a file
    //argv[1] is the file to be read
    
    //check for correct number of arguments
    if(argc < 2) {
        printf("Error: no file given\n");
        return 1;
    }

    FILE* inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    int count = 0;
    char c;
    while((c = fgetc(inFile)) != EOF) {
        count++;
    }
    printf("Number of characters: %d\n", count);

    return 0;
}