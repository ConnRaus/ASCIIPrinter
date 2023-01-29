#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDimensions(char* filename) {
    FILE* inFile = fopen(filename, "r");
    int c;
    int combine = 0;
    for(int i = 0; i < 4; i++) {
        c = fgetc(inFile);
        combine = combine<<8 | c;
    }
    fclose(inFile);
    return combine;
}

void skipChars(FILE* inFile, int num) {
    for(int i = 0; i < num; i++) {
        fgetc(inFile);
    }
}

//takes in argv[1] and returns "images/argv[1].asc"
char* getASCName(char* filename) {
    char* ascName = malloc(strlen(filename));
    strcpy(ascName, "images/");
    strcat(ascName, filename);
    strcat(ascName, ".asc");
    return ascName;
}

int main(int argc, char* argv[]) {
    
    if(argc < 3) {
        printf("Usage: %s <input name, no extension> <scaleFactor>\n", argv[0]);
        return 1;
    }


    //import .asc file
    char* fileName = getASCName(argv[1]);

    if(fopen(fileName, "r") == NULL) {
        printf("%s.asc does not exist\n", argv[1]);
        return 1;
    }
    if(atoi(argv[2]) < 1) {
        printf("Scale factor must be greater than 0\n");
        return 1;
    }
    
    //.asc file format is a text file with header "xxxx" where the first 2 characters are width and the second 2 characters are height in hex. This is in big endian format.
    //The rest of the file is the grayscale representation of the image.
    unsigned int width = getDimensions(fileName)>>16;
    unsigned int height = getDimensions(fileName)&0xFFFF;  
    printf("width: %d, height: %d\n", width, height);

    char brightnessList[] = " .:-=+*#%@";

    FILE* inFile = fopen(fileName, "r");
    skipChars(inFile, 4);

    int skip = width%32;

    int c;
    int scalefactor = atoi(argv[2]);
    //prints the image to console in ascii, scaled by scalefactor
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            c = fgetc(inFile);
            if((col%scalefactor == 0 && row%scalefactor == 0)) {
                printf("%c%c%c", brightnessList[c/26], brightnessList[c/26], brightnessList[c/26]);
                if(argv[3] != NULL) {
                    printf("%c%c%c", brightnessList[c/26], brightnessList[c/26], brightnessList[c/26]);
                }
            }
        }
        if(row%scalefactor == 0) {
            printf("\n");
        }
    }
    return 0;
}