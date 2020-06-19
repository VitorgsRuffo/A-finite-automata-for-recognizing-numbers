CC = gcc

flags = -g -Wall -Werror

obj = main.o automata.o

program: $(obj)
	$(CC) $(obj) -o program -lm

main.o: main.c automata.h
	$(CC) $(flags) -c main.c

automata.o: automata.c automata.h
	$(CC) $(flags) -c automata.c

clean: 
	rm $(obj) program