//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASH DUMP------
/*Hash dump is the second of two commands that can be called at runtime in PA2 with two arguments: the hashtable and the cell number under the format of *DUMP or *DUMP n,   n being a valid integer. When *DUMP is called the command will call the listprint function and display to the user the plates, first names, and last names in entirety       through each cell number of the hashtable. If a user would like to only look at one specific cell number, they can do so *DUMP n, n being a valid integer and the program    will only show that specific cell number and all the plates, first names, last names stored in that location.*/

#include "main.h" //including header file for function delcarations

void hashDump(hashEntry *hashTable, int cellNum){ //start of function definition

	listPrint(hashTable[cellNum]); //calling listprint function to print the specified index of the hashtable that is stored in the cellNum variable

} //end of function definition
