//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------List Print------
/*listPrint takes 1 argument: a pointer to the sentinel node. Once the function is called it will set a pointer to point at the node whose memory address is stored in the   sent->next field of the sentinel node to ensure we do not print the contents of the sentinel node. From there, the functil will begin a while loop that will loop until      current is equal to NULL(we have hit the end), through each loop the function will print the plate, first name and last name data that is stored at the current node it is   pointing at. Once the data is printed, it will then increment the pointer and move to the next node until it hits the end of the list.*/

#include "main.h" //including header file for function declarations

void listPrint(struct node *sent){ //start of function definition
	hashEntry current = sent->next; //setting pointer to point at the node whose memory address is stored in the sentinel node

        while (current != NULL){ //looping until current equals null
                printf("Plate: <%s>  Name: %s, %s \n", current->plate, current->last, current->first); //printing plate, lastname, firstname
                current=current->next; //incrementing the pointer to the next node
        } //end of while loop
} //end of function definition
