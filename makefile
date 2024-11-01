Executable : initialisations.o V1.o Player.o Rounds.o
	gcc -Wall initialisations.o V1.o Player.o Rounds.o -o Executable
initialisations.o: initialisations.c initialisations.h
	gcc -Wall -c initialisations.c
V1.o : V1.c
	gcc -Wall -c V1.c
Player.o : Player.c	Players_Management.h
	gcc -Wall -c Player.c
Rounds.o : Rounds.c	Rounds.h
	gcc -Wall -c Rounds.c