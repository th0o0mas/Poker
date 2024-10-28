Executable : initialisations.o V1.o
	gcc -Wall initialisations.o V1.o -o Executable
initialisations.o: initialisations.c
	gcc -Wall -c initialisations.c
V1.o : V1.c
	gcc -Wall -c V1.c
