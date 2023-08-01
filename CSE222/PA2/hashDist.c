//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASH DIST-----
/*hashDist is a function that can be called at runtime of PA2, when the *DIST command is called with an argument of the hashtable it will go into a for loop that will begin at 0 and iterate until the size of the hash table has been reached while printing all the entries in the hashtable and telling the user the length of each entry indicating  how many things are present in each linked list.*/

#include "main.h" //include header for function declaration

void hashDist(hashEntry *hashTable){ //start of function definition
	extern int size; //indicating global variable size is an external variable
	
	for(int i = 0; i < size; i++){ //starting at 0, iterating through the hash table until i is greater or equal to the size of the hashtable
        	printf("Entry %d: length = %d\n", i, listLen(hashTable[i])); //each iteration, printing to the user the entry number and the length of that entry number
	}
} //end of function definition
