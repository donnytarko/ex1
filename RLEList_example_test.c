#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "test_utilities.h"

typedef bool (*testFunc)(void);

bool basicTest();

#define TESTS_NAMES             \
    X(basicTest)               \

testFunc tests[] = {
#define X(name) name,
    TESTS_NAMES
#undef X
};

const char *tests_names[] = {
#define X(name) #name,
    TESTS_NAMES
#undef X
};

static int number_of_tests = sizeof(tests) / sizeof(tests[0]);


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
    int i = 0;
    RLEList currentList = list->next;
    RLEList previousList;
    while (i + currentList->repetitions < index) {
        if (currentList->next == NULL) {
            return (RLE_LIST_INDEX_OUT_OF_BOUNDS);
        }
        i += currentList->repetitions;
        currentList = currentList->next;
        previousList = currentList;
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



int main(int argc, char **argv)
{
    if (argc == 1)
    {
        for (int test_idx = 0; test_idx < number_of_tests; test_idx++)
        {
            RUN_TEST(tests[test_idx], tests_names[test_idx]);
        }
        return 0;
    }
    if (argc != 2)
    {
        fprintf(stdout, "Usage: tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > number_of_tests)
    {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], tests_names[test_idx - 1]);
    return 0;
}

bool basicTest(){
    RLEList list = RLEListCreate();
    bool result=true;
    ASSERT_TEST(list != NULL, destroy);

    //adding elements to the list
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // a
    ASSERT_TEST(RLEListAppend(list, 'c') == RLE_LIST_SUCCESS, destroy);    // ac
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acb
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acba
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbab
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbaba
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbabab
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababa
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababaa
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababaaa

    ASSERT_TEST(RLEListRemove(list, 1) == RLE_LIST_SUCCESS, destroy); // abababaaa

    // check if the represented string is "abababaaa"
    const char *s = "abababaaa";
    char it;
    
    for(int i=0; i<RLEListSize(list); i++)
    {
        it=RLEListGet(list, i, NULL);
        fprintf(stdout, "it: %c\n", it);
        fprintf(stdout, "s[i]: %c\n", s[i]);
    }
    for(int i=0; i<RLEListSize(list); i++)
    {
        it=RLEListGet(list, i, NULL);
        fprintf(stdout, "it: %c\n", it);
        fprintf(stdout, "s[i]: %c\n", s[i]);
        ASSERT_TEST(it == s[i++], destroy);
    }
    //check if the length's are equal
    ASSERT_TEST(RLEListSize(list)==strlen(s), destroy);
    
    destroy:
    RLEListDestroy(list);
    return result;
}