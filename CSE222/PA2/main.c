//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222-Intro to Data Structures
//Assignment: PA2
/*SYNOPSIS: PA2 is a program that reads a database text file full of peoples names and license plate numbers. While it's reading the names and plates from the text file, it initializes a hash table and uses a hash function to figure out how to store each entry in a way that doesn't cause any collisions. The program has a small amount of variability as it allows users to decide how many indexes are in the hash table by including a number between the executable and database files on the command line, otherwise it   will auto default to size of 50. There are two  functions built in that allow the user to see different pieces of data, DIST and DUMP. DIST will print every cell and show the user the length of each cell in the hashtable.The user can type DUMP to show all the information in all the cells from cell number, to first/last names and plate numbers or they can choose to dump just one specific cellby doing DUMP n, n being a number between 0 and the size of the hashtable they chose. The user can exit the program by hitting ctrl+d. Once hit, the program will begin freeing all of the memory that was malloc'd to store the information from the text file until everything is cleared and then it   will exit.
*/

#include "main.h" //including header file for function declarations.

void main(int argc, char *argv[]){ //start of main, including option for command line arguments
	FILE *fp; //using to open file
	char *filename; //using to point to the name of the file passed in
	char extra[1024]; //using to catch extra inputs
	char word[1024]; //using to capture the words in the text file
	char wordRead[3][1024]; //using to transfer words into an array of arrays: an array of 3 arrays size 1024
        char space[2] = " "; //using as a strtok delimiter
	char *token; //using to point as the string before the delimiter when using strtok
	int size; //using to declare the size of the hash table and save in global variable 

//------DECLARING SIZE, OPENING FILE, READING FILE------
	if (argc == 3){ //if the user includes 3 arguments: file, size, database file
		int sizeChoice=sscanf(argv[1], "%d%s", &size, extra); //parse result, set the global variable size to user selected value
		filename = argv[2]; //using to point to index 2 to identify the database file included on command line		

		if (sizeChoice != 1){ //if sizeChoice does not parse correctly
			printf("Usage: %s [hashsize] database.\n", argv[0]); //give user error showing them the format on how to run the program
			return; //exit program
		}
		
		if (size < 1){ //if size chosen is less then 1
			printf("ERROR: Hashsize should be atleast 1.\n"); //give user error telling them it needs to be at least 1
			return; //exit program
		}  
	}

	if (argc == 2){ //if user only gives 1 command line argument
		size = 50; //auto defaulting to size 50 if user only calls program and database file
		filename = argv[1]; //pointing to the filename given
	}

	if (argc > 3 || argc < 2){ //if more then 3 or less then 2 arguments are given on command line
		printf("Usage: %s [hashsize] database.\n", argv[0]); //give user error showing them the format on how to run the program
		return; //exit program
		
	}

	hashEntry *table = hashInit(size); //hashTable initilizing
	fp = fopen(filename, "r"); //opening text file

	if (!fp){ //if file isn't given or can't open and returns NULL
		printf("ERROR: Could not open database file.\n"); //give user error informing the database file couldn't open
		return; //exit program
	}

	while(fgets(word, 1024, fp) != NULL){
		word[strlen(word)-1] = '\0'; //removing fgets inherant \n, replacing with \0

		token = strtok(word, space); //setting token pointer to the word read before the space delimiter
		int i = 0; //setting i = 0 for upcoming loop so it resets every iteration

		while(token != NULL){ //while the word pointer isn't at the end of the line
			strcpy(wordRead[i], token);//copying each word before the delimiter(space) and capturing it in wordRead indexes
			i++; //incrementing i to next index
			token = strtok(NULL, space); // setting pointer to Null at end	
		}
		hashAdd(table, wordRead[0], wordRead[1], wordRead[2]);//Adding captured data to the hashtable			
	}
	fclose(fp); //closing the file
		
//------START OF MAIN WHILE LOOP------	
	while(1){
		char plate[1024]; //using to capture the plate from user input
		char parsedPlate[1024]; //using to parse the user input if needed
		char firstname[1024]; //using to capture first names
		char lastname[1024]; //using to capture last names
		int cellNum = 0; //using to indicate hashtable cell numbers

		printf("Enter a command or plate: "); //asking user what they'd like to do
		
		if (fgets(plate, 1024, stdin) == NULL){ //using to capture ctrl+d by user by looking for NULL
        	        printf("\nFreeing memory\n"); //informing user memory currently allocated is being free
                	hashFree(table); //calling hashFree function to iterate through list to start freeing all malloc'd memory
                        return; //exiting program
                }
		
		int ParseResult=sscanf(plate,"%s %d", parsedPlate, &cellNum); //using to parse user input 
	
		if (cellNum > size-1 || cellNum < 0){ //if the user chooses a cell number that is greater then the size-1 of the hash table or less then 0
			printf("ERROR: cell must be between 0 and %d.\n", size-1); //Informing user to choose a cell number between 0 and the size-1 of the table
			continue; //using to restart the loop
		}  
		
		if (strcmp(plate, "*DIST\n") == 0){ //if fgets user input matches the string "*DIST\n"
                        hashDist(table); //calling hashDist to show the lengths of each cell in the hash table
                }
		
		else if (strcmp(parsedPlate, "*DUMP") == 0){ //Otherwise if the parsed result from user input is equal to "*DUMP"
			if (strcmp(plate, "*DUMP\n") == 0 && ParseResult == 1){ //and the fgets input is equal to "*DUMP\n" and Parseresult parses successfully
				for (int i = 0; i < size; i++){ //using to loop through the following command i times until it has done so size times
					printf("Contents of cell %d\n", i); //using to indicate cell numbers to user
					hashDump(table, i); //Dumping and displaying the contents of all cells in the hash table
					printf("----------------------------------\n"); //using to separate each cell

				}
			}
			else if (ParseResult == 2){ //Otherwise, if DUMP and a number was given at user input
				printf("Contents of cell %d\n", cellNum); //printing to display the cell number to the user
                                hashDump(table, cellNum); //printing the cell number that the user chose
                                printf("----------------------------------\n"); //using to separate the cell from the next command
			}
			else{
				int findReturn=hashFind(table, parsedPlate, firstname, lastname); //otherwise, if not dump\n or dump %d, search for plate
				
				if(findReturn == 1){ //if it finds plate
					printf("Firstname: %s \n", firstname); //print the user the first name associated
					printf("Lastname: %s \n", lastname); //print the user the last name associated
				}
				else{ //if no match found
					printf("Plate not found.\n"); //print the user and inform no match found
				}
			}
		}

		else{ //if DUMP or DIST wasn't typed, checking for plate
			int findReturn=hashFind(table, parsedPlate, firstname, lastname); //using variable to capture return from hashFind and save first/last names
				
			if (findReturn == 1){ //if hashFind finds the matched plate
				printf("First name: %s \n", firstname); //Printing associated first name to user
				printf("Last name: %s \n", lastname);	//Printing associated last name to user
			}
			else{
				printf("Plate not found.\n"); //Otherwise, if hashFind doesn't find the plate, indicating it was not found
			}
		}
	}//end of while(1)
}//end of program
