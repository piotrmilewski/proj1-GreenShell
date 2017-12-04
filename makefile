all: shell.o exec.o parse.o prompt.o
	gcc -o GreenShell shell.o exec.o parse.o prompt.o

shell.o: shell.c shell.h
	gcc -c shell.c

exec.o: exec.c exec.h
	gcc -c exec.c

parse.o: parse.c parse.h
	gcc -c parse.c

prompt.o: prompt.c prompt.h
	gcc -c prompt.c

run: all
	./GreenShell

clean:
	rm -rf *.o *~ GreenShell debugo

debug: shell.c
	gcc -o debugo -g shell.c exec.c parse.c prompt.c

valgrind: debug
	valgrind --leak-check=yes ./debugo

gdb: debug
	gdb ./debugo
