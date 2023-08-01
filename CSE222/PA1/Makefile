main: main.o functions.o 
	gcc -g -o PA1 main.o functions.o
main.o: main.c main.h
	gcc -g -c main.c
functions.o: functions.c main.h
	gcc -g -c functions.c
clean: 
	rm PA1 main.o functions.o
