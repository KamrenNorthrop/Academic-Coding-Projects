index: index.o displayResults.o getWord.o myGetChar.o readKeyWords.o tally.o
	gcc -g -o index index.o displayResults.o getWord.o myGetChar.o readKeyWords.o tally.o
index.o: index.c index.h
	gcc -g -c index.c
displayResults.o: displayResults.c index.h
	gcc -g -c displayResults.c
getWord.o: getWord.c index.h
	gcc -g -c getWord.c
myGetChar.o: myGetChar.c index.h
	gcc -g -c myGetChar.c
readKeyWords.o: readKeyWords.c index.h
	gcc -g -c readKeyWords.c
tally.o: tally.c index.h
	gcc -g -c tally.c
clean:
	rm index index.o displayResults.o getWord.o myGetChar.o readKeyWords.o tally.o
