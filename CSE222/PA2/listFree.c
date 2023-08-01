//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------List Free------
/*List free accepts one argument, a pointer to the sentinel node. When called, list free will set a pointer for previous, and current pointing current immediately to the    sentinel node. From there it will go into a while loop and loop until current equals NULL. Upon start of the loop, it will shift both pointers to the right one space. Previous will point to the sentinel node and current will point to the node after sentinel node. Once the pointers have incremented over one space, it will then release the memoryallocated via malloc for the plate, first, last sections of the node and then release the node as a whole. It will continue to do this until all memory allocated via malloc for the nodes in the hash table and the sections of the hash table have been successfully free'd to avoid memory leaks.*/

#include "main.h" //including header file for function declarations

void listFree(struct node *sent){ //start of function definition
	hashEntry previous; //initializing pointer previous
        hashEntry current = sent; //initializing pointer current and pointing to sentinel node

        while (current != NULL){ //will loop until current equals NULL(hits the end)
		previous = current; //incrementing previous to the node current is pointing at
                current = current->next; //incrementing current to the memory address stored in next field of the node it's pointing at
                free(previous->plate); //freeing memory malloc'd for the plate section of the node previous is pointing at
		free(previous->first); //freeing memory malloc'd for the first name section of the node previous is pointing at
		free(previous->last); //freeing memory malloc'd for the last name section of the node previouis is pointing at
		free(previous); //freeing memory malloc'd for the node previous is pointing at
        } //end of while loop
} //end of function definition
