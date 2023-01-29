#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//get width and heights
void getDimensions(FILE* inFile, int* width, int* height) {
    char c;
    int i = 0;
    //get width(18th-21st bytes, little endian)
    while ((c = fgetc(inFile)) != EOF) {
        if(i >= 18 && i <= 21) {
            *width = *width | ((c&0xFF) << (8*(i-18)));
        }
        //get height(22nd-25th bytes, little endian)
         else if(i >= 22 && i <= 25) {
            *height = *height | ((c&0xFF) << (8*(i-22)));
        }
        if(i > 25) {
            break;
        }
        i++;
    }
}

void generateASC(FILE* inFile, FILE* outFile) {
    char c;
    //get total number of characters to be averaged in file
    int width = 0;
    int height = 0;
    getDimensions(inFile, &width, &height);
    int totalsize = width*height;

    //output size to .asc file
    fprintf(outFile, "%c%c%c%c", width>>8, width&0xFF, height>>8, height&0xFF);

    // print all characters in reverse order until the header
    // (the header is 54 bytes long)

    
    //calculate bitmap line padding
    int pitch = width*3;
    if(pitch%4 != 0) {
        pitch = pitch + (4 - (pitch%4));
    }
    int padding = pitch - width*3;
    
    //this block is to go up the file line by line(until the 54 character long header) and average the characters to get the grayscale value
    //pixel = 0.3g + 0.59b + 0.11r
    //values start from bottom left of image, get values with fseek
    //dont forget to take into account padding on each line!
    int pixVal;
    for(int row = height-1; row >= 0; row--) {
        fseek(inFile, 54 + (row*width*3) + (row*padding), SEEK_SET);
        for(int col = 0; col < width; col++) {
            int blue = fgetc(inFile);
            int green = fgetc(inFile);
            int red = fgetc(inFile);
            pixVal = (0.3*red) + (0.59*green) + (0.11*blue);
            fprintf(outFile, "%c", pixVal);
        }
    }
}

int main(int argc, char *argv[]) {

    //check for correct number of arguments
    if(argc < 2) {
        printf("Usage: %s <input filename, no folder or extension>\n", argv[0]);
        return 1;
    }

    //filename is frames/argv[1].bmp
    char inName[100];
    char outName[100];
    strcpy(inName, "frames/");
    strcat(inName, argv[1]);
    strcat(inName, ".bmp");

    strcpy(outName, "frames/");
    strcat(outName, argv[1]);
    strcat(outName, ".asc");
    

    FILE* inFile = fopen(inName, "r");
    if (inFile == NULL) {
        printf("Error opening files\n");
        return 1;
    }
    FILE* outFile = fopen(outName, "w");

    generateASC(inFile, outFile);

    fclose(inFile);
    fclose(outFile);

    return 0;
}


