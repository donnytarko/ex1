prog: RLEList.o AsciiArtTool.o main.o
	gcc RLEList.o AsciiArtTool.o -o 
RLEList.o: RLEList.c RLEList.h
	gcc -c RLEList.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	gcc -c AsciiArtTool.c
main.o: main.c AsciiArtTool.h RLEList.h
	gcc -c main.c
clean:
	rm -f RLEList.o AsciiArtTool.o main.o prog