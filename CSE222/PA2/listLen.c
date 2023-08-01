//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------List Len------
/*listLen takes 1 argument: a pointer to the sentinel node of a given index in the hashtable. Once called, the function will set a pointer to point at the node whose memory address is saved in the sentinel node to ensure we don't count it in the tally. We then initilize a count variable to keep track of how many nodes are in a given list.      the function will then start a while loop that will loop until the current pointer is equal to NULL. While looping, the count variable will increment and the pointer will   increment once per iteration. Once current equals NULL(we are at the end) it will then return the count to indicate the length of the given list in the hash table.*/

#include "main.h" //including header file for function declarations

int listLen(struct node *sent){ //start of function definition
	hashEntry current = sent->next;	//setting pointer to point at the next node in the list
	int count=0; //initializing count variable to increment and capture the amount of nodes in a given list

	while ( current != NULL ){ //while current doesn't equal NULL (not at the end of the list)
		count++; //incrementing the count variable to count the node
		current = current->next; //incrementing the pointer to the next node
	}

	return count; //returning the count variable to indicate the number of nodes in the given list

} //end of function definition
