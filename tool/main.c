#include <stdio.h>
#include <string.h>
#include "/home/mtm/public/2223a/ex1/RLEList.h"
#include "AsciiArtTool.h"

#define CHUNK_SIZE 2
#define FLAG 1
#define INPUT_FILE 2
#define OUTPUT_FILE 3

int main(int argc, char** argv) {
    if (argc < 4) {
        return 0;
    }
    
    FILE* inputFile = fopen(argv[INPUT_FILE], "r");
    FILE* outputFile = fopen(argv[OUTPUT_FILE], "w");

    if (strcmp(argv[1],"-e") == 0) {
        RLEList list = asciiArtRead(inputFile);
        asciiArtPrintEncoded(list, outputFile);
        RLEListDestroy(list);        
    }
    else {
        char buffer[CHUNK_SIZE];
	    while (fgets(buffer, CHUNK_SIZE, inputFile) != NULL) {
            if (buffer[0] == ' ') {
                buffer[0] = '@';
            }
            else if (buffer[0] == '@') {
                buffer[0] = ' ';
            }
		    fputs(buffer, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}