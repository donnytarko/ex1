#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define CHUNK_SIZE 256
#define FLAG 1
#define INPUT_FILE 2
#define OUTPUT_FILE 3

int main(int argc, char** argv) {
    fprintf(stdout, "we up in here boiiii\n");
    FILE* inputFile = fopen(argv[INPUT_FILE], "r");
    FILE* outputFile = fopen(argv[OUTPUT_FILE], "w");
    fprintf(stdout, "kkki\n");
    RLEList list = asciiArtRead(inputFile);
    fprintf(stdout, "%s\n", argv[1]);
    fprintf(stdout, "%s\n", argv[2]);
    fprintf(stdout, "%s\n", argv[3]);

    if (strcmp(argv[FLAG],"-e") == 0) {
        fprintf(stdout, "now we here\n");
        asciiArtPrintEncoded(list, outputFile);        
    }
    else {
        fprintf(stdout, "iii\n");
        //char buffer[CHUNK_SIZE];
        /*while (fgets(buffer, CHUNK_SIZE, inputFile) != NULL) {
            fprintf(stdout, "and now here\n");
            for (int i = 0; i < CHUNK_SIZE; i++) {
                if (buffer[i] == ' ') {
                    buffer[i] = '@';
                }
                else if (buffer[i] == '@') {
                    buffer[i] = ' ';
                }
            }
            fputs(buffer, outputFile);
        }*/
        char buffer[CHUNK_SIZE];
	    while (fgets(buffer, CHUNK_SIZE, inputFile) != NULL) {
		    fputs(buffer, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    RLEListDestroy(list);
    return 0;
}