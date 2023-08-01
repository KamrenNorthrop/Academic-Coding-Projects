//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASH FIND------
/*Hash find is called with 2 arguments: the hashtable, and a plate number, also passing in a pointer for the first name and last name. When called the function sets the variable index equal to the hash function that returns a value and saves it to index that indicates where in the hashtable to look for the passed in plate. Once that value is   recieved, the function sets the variable result to t he listFind function while passing in the hashtable and the index recieved previously saved in the index variable, the plate number and the pointers for the first and last name. Once the listFind function has gone through the list it will either save the value of 0 if the plate was not found or a 1 indicating that it was found while saving the first and last name of the associated plate into the first and last pointer variables, hash find then returns the 0 or 1value.*/

#include "main.h" //including header file for function declarations

int hashFind(hashEntry *hashTable, char *plate, char *first, char *last){ //start of function defintion 

	int index = hash(plate); //Using the index variable to call and capture the value returned from the hash function to indicate where to look in the table
  	int result = listFind(hashTable[index], plate, first, last);//Using the result variable to call listfind and capture the return value to indicate if match was found

        return result; //returning the value returned from list find to indicate 0 or 1, not found or found

} //end of function definition
