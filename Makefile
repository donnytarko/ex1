COMP_FLAG = -Wall -pedantic-errors -Werror
OBJS = tool/AsciiArtTool.o tool/main.o RLEList.o
STD = -std=c99
DNDEBUG_FLAG = -DNDEBUG
EXEC = AsciiArtTool
FILE_FLAG = -I/home/mtm/public/2223a/ex1 -Itool/

$(EXEC) : $(OBJS)
	gcc -o $@ $(DNDEBUG_FLAG) $(OBJS)

tool/main.o : tool/main.c tool/AsciiArtTool.h RLEList.h
	gcc $(STD) -c $(DNDEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

RLEList.o : RLEList.c
	gcc $(STD) -c $(DNDEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h
	gcc $(STD) -c $(DNDEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

clean:
	rm -f $(OBJS) $(EXEC)