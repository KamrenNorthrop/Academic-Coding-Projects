//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASHADD------
/*Hash add is a function that works in line with listadd.c and hash.c. All together, hashAdd takes the arguments: The table, plate number, first name, and last name read from the database file then runs the plate through the hash function by calling hash(plate) and setting the returning value back to a variable called index. Based on the value that index picks up, it then takes that value and then calls list add, using the arguments of the hash table, using the index value to indicate where on the table it should orient itself. It also passes in the plate read, first name, and last name to add all the information read to the hash table at the given index. Upon success, the following information will be stored in the hash table at the given index.*/

#include "main.h" //including header file for function declarations

void hashAdd(hashEntry *hashTable, char *plate, char *first, char *last){ //start of function definition

	int index = hash(plate); //using variable to catch return value of the hash function
	listAdd(hashTable[index], plate, first, last); //calling list add and using the caught return value to indentify where to place the users information

} //end of function definition
