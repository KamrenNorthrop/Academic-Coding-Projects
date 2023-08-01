//NAME: Kamren Northrop
//DATE: 1/18/23
//CLASS: CSE 222 - Intro to Data Structures

#include "main.h" //All function, node, library declarations

//------Function Declarations------

//------INIT------
//The initlize function is the first function called in main.c on start up, this function will create a sentinel node, set the data field to "SENTINEL" for identification   purposes and  then set the next section of the node equal to NULL and implement this node as the first node of the linked list as a place holder to continue linking others.

struct DataNode *init(){
        struct DataNode *Sent = malloc(sizeof(struct DataNode)); //initialized sentinel node
        strcpy(Sent->data, "SENTINEL"); //saving the word "SENTINEL" to the data field of the node
        Sent->next=NULL; //pointing to NULL
        return Sent; //returning the node
}

//------ADD------
///The add function is for when the user would like to add data into the linked list alphabetically. Main.c will pass the arguments of the list and the data the user would   like to add. Once passed, the add function will create a new node labeled newNode, allocate memory for it, then set pointers to the first node on the list and the second   node on the list. Once it's done this, it will check to see if memory was able to be allocated or if we ran out of memory and either continue or return 0 and inform the userwe ran out of memory. If it was able to successfully allocate for the new node, it will take the data the user would like to add and copy the string into the newNode->data  section and then begin to compare it with the data sections of all the other nodes within the linked list to identify if the data comes before or after alphabetically with  what is already present. Once the add function has identified the correct place the newNode should be placed, it rearranges the pointers so that the node to the left  pointsto our new node and our new node points to the node on the right and inserts newNode in between them and returns 1 to prompt the user that adding of the new data has  been  done successfully.

int add(struct DataNode *list, char *data){
        struct DataNode *newNode = malloc(sizeof(struct DataNode)); //creating new node, and allocating memory 

        struct DataNode *previous = list; //setting to point to the first node of the list
        struct DataNode *current = list->next; //setting to point to the second node of the list

        if (newNode == NULL){ //checking if there is memory
                return 0; //return 0 if there is no memory left.
        }

        strcpy(newNode->data, data); //copying the data input by the user and passed to function to the data section of the node

        while (current != NULL && strcmp(data,current->data) > 0){ //checking to see if newNode comes after previous and before current
                previous = current; //increments previous node to where current is
                current = current->next; //increments current to the node to the right of where it's located
        }
	//once the function has found the spot where new node should be placed
        previous->next = newNode; //points previous node(node to the left) to the new node
        newNode->next = current; //points new node to the current(node on the right)
        return 1; //addition of new node was successful

}

//------DELETE------
//The delete function is for when the user would like to delete data present in the linked list. Main.c will pass the arguments of the list and the data the user would like to delete. Once passed,the delete function will go through all the data present in the list by set pointers to the first node on the list and the second node on the list.   Once it's done this, it will begin a series of checks to identify if any of the nodes hold data that is the same as what we want to delete. Once it identifies said node to  delete it will then make the node to the left of the node to be deleted point to the node to the right of the node to be deleted to remove its link from the list. Then the  delete function will use the command free() to release that area in memory so that we are able to reuse it later if needed to avoid memory issues. If the delete function is able to successfully delete and free the node indicated for deletion, it will return 1 informing the user the deletion was successful, otherwise, if our delete function is  unable to find any matching data to delete, it will return 0 informing the user that the data was not present in our linked list.

int delete(struct DataNode *list, char *data){
	struct DataNode *previous = list; //setting first pointer to first node in the linked list
        struct DataNode *current = list->next; //setting second pointer to second node in the linked list

        while (current != NULL){ //looping while current(node always on the right) is not NULL(at the end of the list)
                if (strcmp(data, current->data) == 0){ //comparing the data passed by the user with the data present in the nodes, if it is a match
                        previous->next = current->next; //then point the node to the left of the matched node to the node to the right of the matched node
                        free(current); //free the malloc'd memory of the node that is to be deleted
                        return 1; //SUCCESSFUL DELETION
                }
		//If match didn't occur
                previous = current; //increment previous to where current is located at
                current = current->next; //increment current to the node to the right of itself
        }
        return 0; //NO MATCH FOUND, No deletion took place
}

//------SEARCH------
//The search function gives the user the option to check to see if something already exists in their list. Main.c will take user input and pass the present linked list and  the data the user would like to search the list for as arguments. Once the function receives these, it will increment through the list by setting a pointer to the first nodeon the list and compare the data section of the nodes to the data the user input. If the function is able to find it a match, it will return a 1 informing the user that the data they were looking for is present in the list. Otherwise, if the function is unable to find any matches, it will return a 0 and inform the user that the data they are   looking for is not present in the list.
	
int search(struct DataNode *list, char *data){
        struct DataNode *current = list->next; //points to the second node in the linked list

        while (current != NULL){ //looping through until it hits the end of the linked list
                if(strcmp(current->data, data) == 0){ //if the function finds a match in the list
                        return 1; //returns successful match
                }
                current = current->next; //if data field was not a match, increments to the node to the right
        }
        return 0; //no match was found in the list
}


//------CLEANUP------
//The cleanup function is used when the user indicates they would like to exit the program, it is called and the linked list is passed as an argument. Once the function     receives the linked list it will begin to iterate through the list by setting two pointers that point to the first node and the second node. From there it will use the      command free() to begin releasing the node on the left through the entire list until all of the nodes that within the linked list that have malloc'd memory are free'd to    avoid memory leaks.

void cleanup(struct DataNode *list){
	struct DataNode *previous; //setting to point to the left of current
        struct DataNode *current = list; //setting to point to the first node of the list

        while (current != NULL){
                previous = current; //iterates to current's location
                current = current->next; //iterates to the right of it's current location
                free(previous); //free's malloc'd memory that previous is pointing at
        }
}


//------PRINT------
//The print function is so that the user is able to see the data that is present in their linked list on a single line. Main.c will pass the linked list as an argument, oncethe linked list is received the print function will set a single pointer that points to the second node present in the linked list to avoid printing "SENTINEL" as it's just a place holder. It will then begin iterating through all of the nodes within the linked list and printing the data section on a single line separated by a single space in   alphabetical order.
 
void print(struct DataNode *list){
        struct DataNode *current = list->next; //setting to point at the second node, skipping printing SENTINEL
	printf("\n"); //formatting for easy reading
        while (current != NULL){ //iterating through the list until we hit the end
                printf("%s ", current->data); //prints the data section of the node on a single line separated by a space
                current=current->next; //increments to the node to the right of its current location
        }
        printf("\n\n"); //formating for easy reading
}



