FLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
OBJS = tool/AsciiArtTool.o tool/main.o RLEList.o
EXEC = AsciiArtTool
FILE_FLAG = -I/home/mtm/public/2223a/ex1 -Itool/

$(EXEC) : $(OBJS)
	gcc -o $@ $(DEBUG_FLAG) $(OBJS)

tool/main.o : tool/main.c tool/AsciiArtTool.h RLEList.h
	gcc -c $(FLAGS) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@
 
RLEList.o : RLEList.c
	gcc -c $(FLAGS) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h 
	gcc -c $(FLAGS) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@
 
clean:
	rm -f $(OBJS) $(EXEC)