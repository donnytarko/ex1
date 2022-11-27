
#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif // ASCII_ART_TOOL_H