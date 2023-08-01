plate: main.o functions.o 
	gcc -g -o plate main.o functions.o
main.o: main.c main.h
	gcc -g -c main.c
functions.o: functions.c main.h
	gcc -g -c functions.c
tar:
	tar cvf pa3.tar main.h Makefile main.c functions.c 
clean: 
	rm plate main.o functions.o
