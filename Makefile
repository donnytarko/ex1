COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG -g

prog: RLEList.o tool/AsciiArtTool.o main.o
	gcc RLEList.o tool/AsciiArtTool.o -o 
RLEList.o: RLEList.c RLEList.h
	gcc -c ${COMP_FLAG} RLEList.c
AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	gcc -c ${COMP_FLAG} tool/AsciiArtTool.c
main.o: main.c tool/AsciiArtTool.h RLEList.h
	gcc -c ${COMP_FLAG} main.c
clean:
	rm -f RLEList.o tool/AsciiArtTool.o main.o prog