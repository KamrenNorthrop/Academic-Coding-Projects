//NAME: Kamren Northrop
//DATE: 2/22/23
//CLASS: CSE 222-Intro to Data Structures
//Assignment: PA3
/*Synopsis: PA3 is an implementation of a binary search tree. This program will read from a database file and use strcmp to determine where a node(or leaf) should be placed.Upon reading, it will create a node, and copy the data as read. It will then determine where that data should be placed by using strcmp to compare the string coming in with the string that is at the root. All strings greater then the current node being compared will go to the right, all string less then the current node being compared will go  to the left until all the data has been read. From there the user has 4 options for commands: They can look up to see if a plate exists within the tree by typing in a plate and hitting enter. The user can type *DUMP and it will display the height of the tree, if it is balanced, as well as the LNR, NLR, and LRN traversals of the current data.   The user can also delete data from the tree by typing *DELETE plate, if the plate exists, it will move nodes accordingly. If the user attempts to delete the root node,      the program will follow 3 steps: If there are nodes to the left of the root, it will take the highest value of the left sub tree and implement it as the new root. If there  is a left sub tree but the root of the left sub tree has no right children, the root of the left sub tree will become the new root of the tree itself. If there is no left   sub tree, the right child of root will become the new root. The user can also hit ctrl+D, which will immediately exit the program and free all allocated memory. This program can be run with any data base file as long as the file is given as a command line argument when attempting to run the .exe, if no command line argument is given, error     will occur and inform the user of the format needed to run.*/

#include "main.h" //including header file for function / library declarations

void main(int argc, char *argv[]){ // taking in command line arguments

	Node root = NULL; //initializing tree to NULL
	
	FILE *fp; //using to open file
	char *filename; //using to point to the name of the file passed in
	char word[1024]; //using to capture the words in the text file
	char wordRead[3][1024]; //using to transfer words into an array of arrays: an array of 3 arrays size 1024
        char space[2] = " "; //strtok delimiter 
	char *token; //using to point at a string before the delimiter when using strtok
	char plate[1025]; //using to capture the plate entered from stdin
	char parsedPlate[1025]; //using to parse the plate and hold string values
	char first[1024]; //using to hold the first name read from file
	char last[1024]; //using to hold last name read from file
	char command[1024]; //using to hold the command entered at stdin

	if (argc == 2){ //if user only gives 1 command line argument
		filename = argv[1]; //pointing to the filename given
	}
	else{
		printf("Usage: %s databasefile\n", argv[0]); //otherwise, print error, inform user of format needed to run
		return;	//exit program
	}
	
	fp = fopen(filename, "r"); //opening file

	if (!fp){ 
		printf("Can not open %s\n", argv[1]); //if file can't be open, inform user of error
		return; //exit program
	}

	while(fgets(word, 1024, fp) != NULL){
		word[strlen(word)-1] = '\0'; //removing fgets inherant \n, replacing with \0

		token = strtok(word, space); //setting token pointer to the word read before the space delimiter
		int i = 0; //setting i = 0 for upcoming loop so it resets every iteration

		while(token != NULL){ //while the word pointer isn't at the end of the line
			strcpy(wordRead[i], token);//copying each word before the delimiter(space) and capturing it in wordRead indexes
			i++; //incrementing i to next index
			token = strtok(NULL, " \n"); // setting pointer to Null at end
		}
		root = add(root, wordRead[0], wordRead[1], wordRead[2]);//Adding captured data to the hashtable			
	}
	fclose(fp); //closing the file


	while(1){ 
		printf("Enter command or plate: "); //prompting user to enter command or plate number

		if (fgets(plate, 1024, stdin) == NULL){ //if user hits ctrl+D
			printf("Freeing memory...\n"); //inform freeing memory
			treeFree(root); //free the tree
			return; //exit program
		}
		plate[strlen(plate)-1] = '\0'; //if they don't hit ctrl+D, replace fgets inherent new line with null terminator
		
		int parseResult = sscanf(plate, "%s %s", command,  parsedPlate); //parsing data, holding first thing entered as command, second as plate
	
		if (strcmp(plate, "*DUMP") == 0){ //if user types DUMP
			int the_height = height(root); //find height and save to variable
			printf("TREE HEIGHT: %d\n", the_height); //displaying found tree height to user
		
			int balance_check = balanced(root); //find if the tree is balanced, save to variable
			if(balance_check == 1){ //if function returns 1
				printf("BALANCED: YES\n"); //inform user the tree is balanced
			}
			else{
				printf("BALANCED: NO\n"); //otherwise, inform user the tree is not balanced
			}
	
	    		printf("\nLNR TRAVERSAL:\n"); //informing user printing LNR traversal
    			LNR(root); //printing LNR traversal

			printf("\nNLR TRAVERSAL:\n"); //informing user printing NLR traversal
			NLR(root); //printing NLR traversal

			printf("\nLRN TRAVERSAL:\n"); //informing user printing LRN traversal
			LRN(root); //printing NLR traversal

		} //end of dump
	       	
		else if (strcmp(command, "*DELETE")==0 && parseResult == 2){ //if the user types delete followed by another string and the parse returns 2
			int findResult = search(root, parsedPlate, first, last); //search the tree to see if the plate parsed is in the tree

			if (findResult == 1){ //if the search function returns 1
				root = delete(root, parsedPlate); //delete the plate entered, capturing the root returned
				printf("SUCCESS\n"); //inform user plate was deleted successfully
			}
			else{
				printf("Plate not found\n"); //otherwise, if search returns 0, inform user the plate was not found
			}
		} 
		else{
			int findResult = search(root, plate, first, last); //otherwise, any thing else typed in, search the tree for it

			if (findResult == 1){ //if search returns 1
				printf("First name: %s\n", first); //printing first name for user
				printf("Last name: %s\n", last); //printing last name for user
			}
			else{ //other wise if search returns 0 
				printf("Plate not found\n"); //inform user plate wasn't found in tree
			}
		}
	}// end of while
}//end of main
