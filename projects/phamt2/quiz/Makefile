all: run

run: test
	./test

test: testme.o testme.gcno
	gcc -o test testme.c -coverage -fpic -lm

.PHONY: all run

clean:
	rm testme.o test
