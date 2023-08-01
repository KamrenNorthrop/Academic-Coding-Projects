//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------Hash init------
/*Hash init is called to initialize the hashtable on program startup. It does so by accepting the argument that represents the size of the table on the command line or auto defaulting to 50. Once the size is defined and captured in the global variable size, it sets size = hashsize which is the general argument of the function. From there this  function will then allocate space for the hash table by using the size of a struct node and multiplying it by the size of the table. Then it will begin a for loop that      iterates the variable i starting at 0 until it reaches the number that is equal to the int value stored in hashsize, resulting range is 0 to size-1. While this loop is      happening it is using the value of i to index through the table and calling the list init function to initilize each linked list of the table. Once the for loop breaks, thisfunction will return the resulting table that was intialized.*/ 

#include "main.h" //include header for function declarations

int size; //declaring global variable

hashEntry *hashInit(int hashsize){ //start of function definition
	size = hashsize; //setting size equal to hashsize
	hashEntry *table = malloc(sizeof(hashEntry)*size); //allocating memory for the hash table
	

	for (int i=0; i < hashsize; i++){ //start of for loop: iterating from 0 to size - 1
		table[i] = listInit();	//incrementing through the indexes of the table and calling listInit to initalize all the lists for each index
	}
	
	return table; //returning the initilized hash table
} //end of function definition
