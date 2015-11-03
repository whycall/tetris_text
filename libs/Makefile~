CC = gcc -c
.PHONY: clean


libfuncs.a: func1.o func2.o
	ar rv libfuncs.a func1.o func2.o
%.o: %.c
	$(CC) -g -Wall $< -o $@  
clean:
	rm -f libfuncs.a func1.o func2.o
