COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c

prog: RLEList.o AsciiArtTool.o main.o
	gcc RLEList.o AsciiArtTool.o -o 
RLEList.o: RLEList.c RLEList.h
	gcc -c ${COMP_FLAG} RLEList.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	gcc -c ${COMP_FLAG} AsciiArtTool.c
main.o: main.c AsciiArtTool.h RLEList.h
	gcc -c ${COMP_FLAG} main.c
clean:
	rm -f RLEList.o AsciiArtTool.o main.o prog