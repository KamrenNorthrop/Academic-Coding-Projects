knapsack: main.o functions.o 
	gcc -g -o knapsack main.o functions.o
main.o: main.c main.h
	gcc -g -c main.c
functions.o: functions.c main.h
	gcc -g -c functions.c
tar:
	tar cvf pa4.tar main.h Makefile main.c functions.c 
clean: 
	rm knapsack main.o functions.o

