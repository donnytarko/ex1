#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define CHUNK_SIZE 256
#define FLAG 1
#define INPUT_FILE 2
#define OUTPUT_FILE 3

int main(int argc, char** argv) {
    printf("we up in here boiiii");
    FILE* inputFile = fopen(argv[INPUT_FILE], "r");
    FILE* outputFile = fopen(argv[OUTPUT_FILE], "w");
    RLEList list = asciiArtRead(inputFile);
    if (strcmp(argv[FLAG],"-e") == 0) {
        asciiArtPrintEncoded(list, outputFile);        
    }
    else {
        char buffer[CHUNK_SIZE];
        while (fgets(buffer, CHUNK_SIZE, inputFile) != NULL) {
            for (int i = 0; i < CHUNK_SIZE; i++) {
                if (buffer[i] == ' ') {
                    buffer[i] = '@';
                }
                else if (buffer[i] == '@') {
                    buffer[i] = ' ';
                }
            }
            fputs(buffer, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}