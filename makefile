all: shell.o
	gcc -o GreenShell shell.o

shell.o: shell.c
	gcc -c shell.c

run: all
	./GreenShell

clean:
	rm -rf *.o *~ GreenShell debugo

debug: shell.c
	gcc -o debugo -g shell.c

valgrind: debug
	valgrind --leak-check=yes ./debugo

gdb: debug
	gdb ./debugo
