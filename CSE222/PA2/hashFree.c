//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASH FREE------
/*Hash free is a function that when called in main, it works in unison with list free. This function is called when the user indicates that they would like to exit the      program. Upon doing so, hash free runs with the single argument of the hash table, it will go into a for loop that starts at 0 and increments through each index of the hash table to call the list free function until it has incremented an amount of times that is equal to the integer value stored in the global variable size. After incrementing   the last time, hash free will exit the loop and call the free function on the hashtable itself to release the memory allocated.*/

#include "main.h" //including header file for function delcarations

void hashFree(hashEntry *hashTable){ //start of function definition
	extern int size; //delcaring the global variable size is an external variable

	for (int i = 0; i < size; i++){ //iterating from 0 to the number that is equal to the int value stored in the global variable size. Ending with size-1
		listFree(hashTable[i]); //calling listfree for every index of the hashTable
	}
	free(hashTable); //For loop ends, releasing the memory allocated for the hashtable itself
} //end of function definition
