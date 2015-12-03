
.PHONY: clean


libfuncs.a: move_block.c
	ar rv libfuncs.a 
%.o: %.c
	gcc -c -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a  move_block.c
