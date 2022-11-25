#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AsciiArtTool.h"
#include "RLEList.h"

struct RLEList_t{
    int repetitions;
    char letter;
    struct RLEList_t* next;
};

RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    char* buffer;
    int i = 0;
    while(buffer[0] = buffer[i]) {
        fgets(buffer, i, in_stream);
    }
    RLEListAppend(list, buffer);
};

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    char* string = malloc(RLEListSize(list) + 1);
    if (!string) 
        return RLE_LIST_OUT_OF_MEMORY;
    int pointer = 0;
    RLEList currentList = list;
    RLEListResult *result = malloc(sizeof(RLEListResult));
    while (currentList) {
        for (int i = 0; i < RLEListSize(currentList) - RLEListSize(currentList->next); i++){
            string[pointer + i] = RLEListGet(currentList, 0, *result);
        }
        pointer += RLEListSize(currentList) - RLEListSize(currentList->next);
        currentList = currentList->next;
    }
    fputs(string, out_stream);
    free(string);
    return RLE_LIST_SUCCESS;
};

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if (list == NULL || out_stream == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    char* string = malloc(RLEListSize(list) + 1);
    if (!string) 
        return RLE_LIST_OUT_OF_MEMORY;
    RLEListResult *result = malloc(sizeof(RLEListResult));
    string = RLEListExportToString(list, result);
    fputs(string, out_stream);
    free(string);
    return RLE_LIST_SUCCESS;
};