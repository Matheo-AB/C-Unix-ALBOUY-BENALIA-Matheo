CC=gcc
LN=gcc
OPT=-Wextra -Werror -g -finline-functions -std=c99 
LIB=-lrt -lm

all: 
	$(CC) $(OPT) -c main.c
	$(LN) main.o -o main $(LIB)

test:
	./main < test.txt

clean:
	rm -f main main.o
