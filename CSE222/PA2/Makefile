plate: main.o listAdd.o listFind.o listFree.o listInit.o listLen.o listPrint.o hashFind.o hashInit.o hashDist.o hashDump.o hash.o hashAdd.o hashFree.o
	gcc -g -o plate main.o listAdd.o listFind.o listFree.o listInit.o listLen.o listPrint.o hashFind.o hashInit.o hashDist.o hashDump.o hash.o hashAdd.o hashFree.o
main.o: main.c
	gcc -g -c main.c
listAdd.o: listAdd.c 
	gcc -g -c listAdd.c
listFind.o: listFind.c
	gcc -g -c listFind.c
listFree.o: listFree.c 
	gcc -g -c listFree.c
listInit.o: listInit.c 
	gcc -g -c listInit.c
listLen.o: listLen.c 
	gcc -g -c listLen.c
listPrint.o: listPrint.c 
	gcc -g -c listPrint.c
hashFind.o: hashFind.c 
	gcc -g -c hashFind.c
hashInit.o: hashInit.c 
	gcc -g -c hashInit.c
hashDist.o: hashDist.c 
	gcc -g -c hashDist.c
hashDump.o: hashDump.c 
	gcc -g -c hashDump.c
hash.o: hash.c 
	gcc -g -c hash.c
hashAdd.o: hashAdd.c 
	gcc -g -c hashAdd.c
hashFree.o: hashFree.c 
	gcc -g -c hashFree.c
tar:
	tar cvf pa2.tar hashAdd.c hash.c hashDist.c hashDump.c hashFind.c hashFree.c hashInit.c listAdd.c listFind.c listFree.c listInit.c listLen.c listPrint.c main.c main.h Makefile	
clean:
	rm plate main.o listAdd.o listFind.o listFree.o listInit.o listLen.o listPrint.o hashFind.o hashInit.o hashDist.o hashDump.o hash.o hashAdd.o hashFree.o 

