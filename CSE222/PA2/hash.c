//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------HASH FUNCTION------
/*The hash function takes in the argument of the plate variation(mix of numbers/letters) and from there it initalizes a variable called sum and sets it equal to zero. After it intializes the variable, it begins a for loop and iterates the length of plate times. While doing so, it takes the value of i at that time and multiplies it by (2i+3)^2  multiplied by indexes of the plate passed in as an argument. It takes the value from the arithmatic and intilizes it to the sum variable, while adding all the values through the iterations to sum as it continues. Once the for loop has ended, this function returns a value that is calculated by taking the value of sum and moduloing it by the global variable that holds the size of the hash table. The value that is returned indicates the index of the hashtable that we want the plate to be stored.*/

#include "main.h" //including header for function delcarations

int hash(char *plate){ //start of function definition
	extern int size; //indicating global variable is an external variable
	int sum = 0; //intilizing sum to 0

	for (int i = 0; i < strlen(plate); i++){ //looping through the following equal to the length of the plate
		sum += (((2*i+3)*(2*i+3))*plate[i]); //incrementing i, doing the following math and adding it and saving it to sum variable
	} 
	return sum%size; //taking the value received from the for loop, modulo'ing it by the size of our hash table and returning the value outcome
} //end of function definition
