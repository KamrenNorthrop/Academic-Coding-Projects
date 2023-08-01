//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

//------LIST FIND------
/*list find takes in 2 arguments: the pointer to the sentinel node and a pointer to the plate entered. It also includes a pointer to first name and last name to be stored if the plate is located. Once a plate is identified, the function will set a pointer to the node that comes after the sentinel node, it will then go into a while loop which   which will iterate until current either equals NULL at which point it will return 0 indicating a match was not found. Otherwise, if the strcmp between the plate entered and the pointer->plate section returns 0, the function will copy the current->first/last into the firstname/lastname pointers and return 1 indicating that a match was found.*/

#include "main.h" //including header file for function declarations

int listFind(struct node *sent, char *plate, char *firstname, char *lastname){ //start of function definition
	hashEntry current = sent->next; //setting pointer to point at the node that comes after the sent node

        while (current != NULL){ //while current doesn't equal NULL
                if(strcmp(current->plate, plate) == 0){ //compare the plate entered with the plate in current -> plate until strcmp returns 0
			strcpy(firstname, current->first);//if strcmp returns 0, copy the firstname from current->first to firstname pointer
			strcpy(lastname, current->last);  //if strcmp returns 0, copy the lastname from current->last to lastname pointer
                        return 1; //return 1 indicating match was found
                }
                current = current->next; //increment if strcmp does not return 0
        }
        return 0; //If current equals NULL and strcmp never return'd 0, return 0 indicating no match was found

} //end of function definition
