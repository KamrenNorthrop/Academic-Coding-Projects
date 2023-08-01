//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------List Add------
/*List add is the main function that is called when the program reads a file and wants to add the information read into an area on the hash table. It does so by taking in 4 arguments: A pointer to the sent node, a pointer to the plate, a pointer to the firstname and a pointer to the last name. It then creates a new node and allocates memory for said node. From there it will begin allocating memory for the pieces of the node: newnode->plate, newnode->first, newnode->last to store the information accordingly. It    Once the memory is allocated, this function then sets a pointer to point at the first node in the given list where we want to store the plate number as recognized by the    hash function. If newnode returns NULL, it indicates to the user that they are out of memory. If newnode does not return NULL, it will begin a series of strcpy, saving the  data held in the arguments passed to their corresponding area's within the new node. Once the data is stored, it then stores the memory address that's present in sent->next into newNode->next and then points the sentinel node at the new node. It's worth noting that this function will always throw a new node at the beginning of the list when    added.*/

#include "main.h" //including header file for function declaration

void listAdd(struct node *sent, char *plate, char *firstname, char *lastname){ //start of function definition
        hashEntry newNode = malloc(sizeof(struct node)); //declaring the new node as type struct node, allocating memory for it
	newNode->plate=malloc((strlen(plate)+1)*(sizeof(char))); //allocating memory for where the plate information will be stored
	newNode->first=malloc((strlen(firstname)+1)*(sizeof(char))); //allocating memory for where the first name will be stored
	newNode->last=malloc((strlen(lastname)+1)*(sizeof(char))); //allocating memory for where the last name will be stored

        hashEntry current = sent; //setting pointer to start at the sentinel node of the list
	
        if (newNode == NULL){ //if new node equals null
                printf("Out of memory\n"); //inform user they're out of memory 
        }

        strcpy(newNode->plate, plate); //otherwise, copy the plate argument to the newnode section for plate
	strcpy(newNode->first, firstname); //copy the first name argument to the newnode section for first name
	strcpy(newNode->last, lastname); //copy the last name argument to the new node section for last name

	newNode->next = sent->next; //saving the memory address in sentinels next to newNodes next area
        sent->next = newNode; //pointing the sentinel node to the new node

} //end of function definition
