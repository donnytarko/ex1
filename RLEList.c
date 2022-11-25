#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"

struct RLEList_t{
    int repetitions;
    char letter;
    struct RLEList_t* next;
};

RLEList RLEListCreate(){
    RLEList list = malloc(sizeof(*list));
	if(!list) {
		return NULL;
	}
	list->next = NULL;
	return list;
};

void RLEListDestroy(RLEList list) {
    while(list) {
        RLEList listToDelete = list;
        list = list->next;
        free(listToDelete);
    }
};

RLEListResult RLEListAppend(RLEList list, char value) {
    if (list == NULL || value == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList currentList = list;
    while(currentList->next) {
        currentList = currentList->next;
    }
    if (currentList->letter == value) {
        currentList->repetitions++;
    }
    else {
        RLEList newList = malloc(sizeof(*newList));
        if(!newList)
		    return RLE_LIST_OUT_OF_MEMORY;
        newList->letter = value;
        newList->repetitions = 1;
        newList->next = NULL;
        currentList->next = newList;
    }
    return RLE_LIST_SUCCESS;
};

int RLEListSize(RLEList list) {
    int count = 0;
    while(list) {
        count+=list->repetitions;
        list = list->next;
    }
    return (count);
};

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return (0);
    }
    for (int i = 0; i < index; i++) {
        if (list->next == NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return (0);
        }
        list = list->next;
    }
    *result = RLE_LIST_SUCCESS;
    return (list->letter);
};

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char* string = malloc(1);
    int size = 0;
    while(list) {
        string = realloc(string, size + 3);
        string[size] = list->letter;
        string[size + 1] = '0' + list->repetitions;
        strcat(string, "\n");
        size+=3;
        list = list->next;
    }
    *result = RLE_LIST_SUCCESS;
    return (string);
};