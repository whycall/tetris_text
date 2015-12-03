
.PHONY: clean


libfuncs.a: block.o move_block.o
	ar rv libfuncs.a 
%.o: %.c
	gcc -c -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a block.o move_block.o
