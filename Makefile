all: test.c
	gcc test.c -o test -lraylib -lm -Werror -Wall -std=c11 -pedantic
clean:
	rm test
