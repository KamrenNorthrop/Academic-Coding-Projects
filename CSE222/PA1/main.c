//NAME: Kamren Northrop
//DATE: 1/18/23
//CLASS: CSE 222-Intro to Data Structures
//SYNOPSIS: PA1 allows users to store data alphabetically in the format of a string into a linked list that is memory cautious. Further more,the program implements a        SENTINEL node upon start up and allows the user to maniuplate the linked list through 5 major functions: Add, Delete, Print, Search,and Clean up as needed which allows the  storage of said string data while maintaining overall memory allocation and avoiding memory leaks upon exit.

#include "main.h" //includes all function, library, and node declarations.

int main(){
  struct DataNode *myList = init(); //initilizing sentinel node
  char data[16]; //To capture data the user wants to add, delete, or search.
  char command[4]; //To capture the first letter: i, d, p, s, x to decide what function to trigger.
  char input[20]; //capturing user input through stdin.
   
  while(1){ // start of main function while loop.
	printf("> ");
	fgets(input, sizeof(input), stdin); //capturing STDIN input and saving to input variable.
	int parseResult=sscanf(input, "%s", command); //saving the first string/letter to command to decide where to navigate

	if (parseResult == 1){ //Using to decide if users first string is valid
		if (strcmp(command, "i") == 0){ //If user chose i to insert new data into linked list
			sscanf(input, "%s %s", command, data); //parsing new string to include first letter and data they wish to insert.
		
                	int searchResult = search(myList, data); //searching linked list to see if data is already present

	 		if (searchResult == 0){ //if data is not present
				int result =  add(myList, data); //add data to linked list
	
				if (result == 1){ //if add returns 1
					printf("\nSUCCESS\n\n"); //data was inserted successfully.
				}
				else{ //if add returns 0
					printf("\nOut of memory\n\n");//The newNode was not able to be allocated and we are out of memory.
				}
			}	
			else{ //if searchResult returns 1
				printf("\nNode already exists\n\n");//The data already exists and does not add to avoid duplicates.
				continue; //reprompt user to menu.
			}
		}

		else if (strcmp(command, "p") == 0){ //If user chose p to print
			print(myList); //prints the elements in the linked list on a single line spaced out.
		}	

		else if (strcmp(command, "s") == 0){ //if user chose s to search
		
			sscanf(input, "%s %s", command, data); //creates string with s and data entered

	        	int searchResult = search(myList, data); //searches the linked list for data captured
		
			if (searchResult == 1){ //If search returns 1
				printf("\nFOUND\n\n"); //Data was found in the linked list
			}
			else{ //otherwise, if search returns 0
				printf("\nNOT FOUND\n\n"); //Data was not found in the linked list
			}
		}

		else if (strcmp(command, "x") == 0){ //If user chooses x to exit the program
			printf("\nGoodbye!\n\n"); //gives user farewell.
			cleanup(myList); //Goes into clean up mode to release all current nodes to avoid memory leaks
			break; //breaks the while loop, exits the program.
		}

		else if (strcmp(command, "d") == 0){ //If the user chooses d to delete an element
			sscanf(input, "%s %s", command, data); //formats a string d data

                	int result = delete(myList, data); //Check's linked list for a node that is the same as the data input
		
			if (result == 1){ //if delete returns 1
				printf("\nSUCCESS\n\n"); //Node was found and successfully deleted
			}
			else{ //Otherwise, if delete returns 0
				printf("\nNODE NOT FOUND\n\n"); //Node was not found in linked list
			}
		}
		else{ //If user enters a first letter that is not i, p ,s, d, or x or just hits enter
			printf("\nPlease Enter one of the following commands\n");
                	printf("i string        insert string into the list\n");
                	printf("p               print the list in order\n"); //It shows the user a list of all legal commands/operations
                	printf("s string        search for string in the list\n");
                	printf("d string        to delete from the list\n");
                	printf("x               exit the program\n\n");
		}//end of if's using strcmp
	}
	else{ //If user does enters a first letter that is not i, p, s, d, or x or just hits enter
		printf("\nPlease Enter one of the following commands\n");
                printf("i string        insert string into the list\n");
                printf("p               print the list in order\n"); //It shows the user a list of all legal commands/operations
                printf("s string        search for string in the list\n");
                printf("d string        to delete from the list\n");
                printf("x               exit the program\n\n");
	}//end of if parseResult

  }// end of while
}//end of main program
