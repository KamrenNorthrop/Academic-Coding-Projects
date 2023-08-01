//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------List Init------
/*List init is a function used to initialize a linked list by implementing a sentinel node. It doesn't take any arguments to call. When called, it will create a new node    called sent and allocate memory for it using the malloc function. From there, the function will also malloc memory for the plate section of the node, I chose to malloc spaceof SENTINEL+1 because I knew that the data for these nodes 100% going to be sentinel every single time. From there, this functil will copy the string "SENTINEL" into the    plate section of the node, it will then set the next section of the node to NULL and then return the node to the current index.*/

#include "main.h" //including header file for function declarations

struct node *listInit(){ //start of function definition
        struct node *Sent = malloc(sizeof(struct node)); //allocating memory for sentinel node
	Sent->plate = malloc((strlen("SENTINEL")+1)*(sizeof(char))); //allocating memory for the plate section of the sentinel node

	strcpy(Sent->plate, "SENTINEL"); //copying the string "SENTINEL" into the plate section of the node
        Sent->next=NULL; //setting the next section of the node to NULL
	 
        return Sent; //returning the node
} //end of function definition
