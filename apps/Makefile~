cc= gcc -c
.PHONY: clean

main:main.o
	$(CC) main.c -L../lib -lfuncs -o main
 
clean:
	rm -f libfuncs.a func1.o func2.o
