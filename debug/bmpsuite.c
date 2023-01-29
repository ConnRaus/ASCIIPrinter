#include <stdio.h>
#include <stdlib.h>

void hexDump(FILE* inFile, FILE* outFile) {
    int c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        //output hex values of colors in bmp file
        fprintf(outFile, "%02x ", c);
    }
}

unsigned char charToHex(char charnum) {
    unsigned char hex;
    if(charnum >= '0' && charnum <= '9') {
        hex = charnum - '0';
    } else if(charnum >= 'a' && charnum <= 'f') {
        hex = charnum - 'a' + 10;
    } else if(charnum >= 'A' && charnum <= 'F') {
        hex = charnum - 'A' + 10;
    }
}


void dumpfileToImg(FILE* inFile, FILE* outFile) {
    //converts file of hex values to bmp file
    int c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        //output hex values of colors in bmp file
        char out = charToHex(c) << 4;
        c = fgetc(inFile);
        out = out + charToHex(c);
        c = fgetc(inFile);
        fprintf(outFile, "%c", out);
    }
}

void multiply(FILE* inFile, FILE* outFile, float factor) {
    //converts bmp values to bmp*factor
    int c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        if(c*factor > 255) {
            c = 255;
        } else {
            c = c*factor;
        }
        fprintf(outFile, "%c", (int)(c));
    }
}


void movePastHeader(FILE* inFile) {
    int c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        //output hex values of colors in bmp file
        if(i > 54) {
            break;
        }
        i++;
    }
}


void copyHeader(FILE* inFile, FILE* outFile) {
    int c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        //output hex values of colors in bmp file
        if(i > 54) {
            fgetc(inFile);
            fgetc(inFile);
            break;
        }
        fprintf(outFile, "%c", c);
        i++;
    }
    
}

//get width and heights
void getDimensions(FILE* inFile, int* width, int* height) {
    char c;
    int i = 0;
    while ((c = fgetc(inFile)) != EOF) {
        if(i >= 18 && i <= 21) {
            *width = *width + (c << (8*(i-18)));
        } else if(i >= 22 && i <= 25) {
            *height = *height + (c << (8*(i-22)));
        }
        if(i > 25) {
            break;
        }
        i++;
    }
}

//moves to end and appends average hex value of each pixel to outFile backwards
void copyAvg(FILE* inFile, FILE* outFile) {
    //get last character using fseek
    char c;
    //get total number of characters to be averaged in file
    int width = 0;
    int height = 0;
    getDimensions(inFile, &width, &height);
    int totalsize = width*height;

    //output size to .asc file
    fprintf(outFile, "%c%c%c%c", width>>8, width&0xFF, height>>8, height&0xFF);

    // print all characters in reverse order until the header
    for(int row = height; row > 0; row--) {
        for(int col = 0; col < width; col++) {
            fseek(inFile, 54 + (row*width + col)*3, SEEK_SET);
            int avg = 0;
            for(int i = 0; i < 3; i++) {
                c = fgetc(inFile);
                avg = avg + c;
            }
            avg = avg/3;
            fprintf(outFile, "%c", avg);
        }
    }
}

void usage(char *argv[]) {
    printf("Usage: %s <input file> <output file> <option> [factor]\n", argv[0]);
    printf("Option 1: convert bmp to hex\n");
    printf("Option 2: convert hex to bmp\n");
    printf("Option 3: multiply bmp by factor\n");
    printf("Option 4: output to .asc file\n");
    printf("Option 5: print dimensions\n");
}

int main(int argc, char *argv[]) {

    //check for correct number of arguments
    if(argc < 4) {
        usage(argv);
        return 1;
    }

    FILE* inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error opening files\n");
        return 1;
    }
    FILE* outFile = fopen(argv[2], "w");

    //if argv[3] == 1, convert chars to hex
    //if argv[3] == 2, convert hex to chars
    //if argv[3] == 3, convert bmp to bmp*factor
    //if argv[3] == 4, output to .asc file
    //if argv[3] == 5, print dimensions of bmp file
    if(argv[3][0] == '1') {
        hexDump(inFile, outFile);
    } 
    else if(argv[3][0] == '2') {
        dumpfileToImg(inFile, outFile);
    }
    else if(argv[3][0] == '3') {
        copyHeader(inFile, outFile);
        if(argv[4] == NULL) {
            printf("Error: no factor given\n");
            return 1;
        }
        multiply(inFile, outFile, atof(argv[4]));
    } 
    else if(argv[3][0] == '4') {
        copyAvg(inFile, outFile);
    }
    else if(argv[3][0] == '5') {
        int width = 0;
        int height = 0;
        getDimensions(inFile, &width, &height);
        printf("width: %d, height: %d\n", width, height);
    }
    else {
        printf("Error: invalid argument\n");
        return 1;
    }

    fclose(inFile);
    fclose(outFile);

    return 0;
}


