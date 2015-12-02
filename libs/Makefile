
.PHONY: clean


libfuncs.a: collision.o move_block.c
	ar rv libfuncs.a collision.o 
%.o: %.c
	gcc -c -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a collision.o move_block.c
