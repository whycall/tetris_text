
.PHONY: clean


libfuncs.a: func1.o func2.o
	ar rv libfuncs.a collision.o 
%.o: %.c
	gcc -c -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a collision.o 
