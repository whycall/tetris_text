.PHONY: clean


libfuncs.a: init_tetris_table.o getchar.o
	ar rv libfuncs.a init_tetris_table.o getchar.o
%.o: %.c
	gcc -c -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a init_tetris_table.o getchar.o
