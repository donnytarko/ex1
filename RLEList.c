#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"

#define LINE_LENGTH 3

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
}

void RLEListDestroy(RLEList list) {
    while(list) {
        RLEList listToDelete = list;
        list = list->next;
        free(listToDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (list == NULL || !value)
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
}

int RLEListSize(RLEList list) {
    int count = 0;
    while(list) {
        count+=list->repetitions;
        list = list->next;
    }
    return (count);
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list) {
        if (result)
            *result = RLE_LIST_NULL_ARGUMENT;
        return (0);
    }
    int i = 0;
    RLEList currentList = list->next;
    while (i + currentList->repetitions < index) {
        if (currentList->next == NULL) {
            if (result)
                *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return (0);
        }
        i += currentList->repetitions;
        currentList = currentList->next;
    }
    if (result)
        *result = RLE_LIST_SUCCESS;
    return (currentList->letter);
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list)
        return (RLE_LIST_NULL_ARGUMENT);
    int i = -1;
    RLEList currentList = list;
    RLEList previousList;
    while (i + currentList->repetitions < index) {
        if (currentList->next == NULL) {
            return (RLE_LIST_INDEX_OUT_OF_BOUNDS);
        }
        i += currentList->repetitions;
        previousList = currentList;
        currentList = currentList->next;
    }
    if (currentList->repetitions > 1) {
        currentList->repetitions--;
    }
    else {
        previousList->next = currentList->next;
    }
    return (RLE_LIST_SUCCESS);
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        if (result)
            *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int numberOfNodes = 0;
    RLEList currentList = list->next;
    while(currentList) {
        numberOfNodes++;
        currentList = currentList->next;
    }
    char* string = malloc(numberOfNodes * (sizeof(int) + 2*(sizeof(char))) + sizeof(char));
    if (!string) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return (0);
    }
    char oneLineTemp[sizeof(int) + 3*sizeof(char)];
    currentList = list->next;
    while(currentList) {
        sprintf(oneLineTemp, "%c%d\n", currentList->letter, currentList->repetitions);
        strcat(string, oneLineTemp);
        currentList = currentList->next;
    }
    if (result)
        *result = RLE_LIST_SUCCESS;
    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (list == NULL || map_function == NULL)
        return (RLE_LIST_NULL_ARGUMENT);
    while(list) {
        if (list->letter) {
            list->letter = map_function(list->letter);
        }
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}
