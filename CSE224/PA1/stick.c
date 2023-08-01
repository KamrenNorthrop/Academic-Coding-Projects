/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA1 - Stick Game
Due Date: 9/30/22 
Finished Date: 9/28/22
Synopsis: Stick game is a game where you and another player(Computer in this instance) put a certain number of sticks down. 
	  You both alternate picking up minimum 1 to maximum of 3 sticks at a time. Whoever picks up the last sticks wins!
	  The game will auto default to 21 sticks; however, you can put an integer as a command line argument to decide if you'd like to play with more or less.
*/


#include <stdio.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0


int computersMove(int x); //declaration of function that will decide how many sticks the computer takes

int main(int argc, char **argv){
  int number_of_sticks=21; //setting equal to 21 to auto default to 21 sticks if no command line argument given
  int invalid_choice=0, playerTakes, computerTakes;//using to store values for invalid moves, amount of sticks player and computer want to take
  char extra[120];//using to store characters upon trying to convert input to an integer
  bool playing=TRUE;//using to identify when the game loop should start
  bool playersTurn=TRUE, CPUturn=FALSE;//using to identify when the players and computers turns are

//----CHECKING TO SEE IF 2 COMMAND LINE ARGUMENTS ARE GIVEN------
  if (argc >= 3){ 
	printf("Invalid option, please only enter 1 command line argument!\n");
       	return 0; //using to exit program if invalid command line arguments given
  }

//-----Determining number of sticks to play with--------------------
  if (argc == 2){ //-----Is there a command line argument?----
  	int playerChoice=sscanf(argv[1], "%d%s", &number_of_sticks, extra);//Converting arg to int/checking for illegal characters. If converted, saving to variable
        if (playerChoice != 1){ //checking to see if a valid conversion happened
		printf("Invalid option\n");
		return 0; //using to exit program if invalid characters are input
	}
  }


//---Checking to see if positive int was given-----
  if (number_of_sticks  < 0){ //Using to check that command line argument is not a negative number. If so, exit.
         printf("Invalid option, you can only play with positive sticks!\n");
         return 0;           
  }
   

//----------Stick DISPLAY------------------------------------
  printf("You're playing with %d sticks\n", number_of_sticks);//telling user how many sticks there are

  for(int i=0; i < number_of_sticks; i++){ //using for loop to make sure that the number of |'s printed is equal to the int held in number_of_sticks
  	printf("|");
  }
  printf("(%d)\n", number_of_sticks); //using to print the number of sticks numerically

//-----------------Game Moves-------------
   while(playing){ //Using boolean loop to make sure the game repeats itself

	if(invalid_choice == 2){ //using variable invalid_choice to keep track of how many illegal moves someone has made, exiting if 2 have been made consecutively
		printf("Come back when you're ready to play sticks!\n");
		return 0;
	}	

	if(playersTurn==TRUE){ //using boolean value to determine when it is the players turn

		 printf("How many sticks do you want to take: 1, 2, or 3?\n");
       		 fgets(extra, 120, stdin); //using to accept run time input from the user so the user can decide how many sticks they want to take
       		 int playersMove=sscanf(extra,"%d%s", &playerTakes, extra); //using to convert the user input into an integer
                
		 if (playersMove != 1){ //using again to determine if successful conversion has happened and there are no illegal characters
       			  printf("Invalid option\n"); 
			  invalid_choice++; //incrementing to keep track of consecutive illegal move made
        		  continue;
	         }
		 

      	 	 if (playersMove == 1){ //using to determine sscanf conversion was successful
	        	 if (playerTakes < 1 || playerTakes > 3){ //using to stop the player from taking 0 sticks or more then 3 sticks at a time
                 		 printf("Invalid option\n");
                 		 invalid_choice++; //incrementing to keep track of consecutive illegal move made
                 		 continue;
                 	}

			invalid_choice=0; //setting variable to zero to allow players to make 2 consecutive invalid inputs at any given time inside the while loop
			number_of_sticks -= playerTakes; //Using the value converted from sscanf in player turn to subtract and set number of sticks equal to new value

			for (int i=0; i < number_of_sticks; i++){ //for loop to print updating amount of | sticks after subtraction has taken place
				printf("|");
			}

			printf("(%d)\n", number_of_sticks); //using to print number of sticks numerically
			playersTurn=FALSE; //using to indicate players turn is over
			CPUturn=TRUE; //using to indicate it is the computers turn
		}
	}
	else{
			printf("Invalid option!\n"); 
			invalid_choice++; //incrementing to keep track of consecutive illegal move made
			continue;
	}
	                	
  	if(CPUturn==TRUE){ //using to determine when it is the computers turn to take sticks
		if(number_of_sticks >= 1){ //using to stop the computer from taking a turn if number_of_sticks is zero
			computerTakes = computersMove(number_of_sticks); //calling function to determine how many sticks the computer will take, saving it to variable
			number_of_sticks -= computerTakes; //subtracting the computers decision from number_of_sticks /  setting number_of_sticks equals to the new value
			printf("Your opponent takes %d stick(s)\n", computerTakes);
			for (int i=0; i < number_of_sticks; i++){ //using to print updated number of | sticks
	               		 printf("|");
               		 }
               		 printf("(%d)\n", number_of_sticks); //using to print updated number of sticks numerically
               		 playersTurn=TRUE; //using to indicate it's the players turn
               		 CPUturn=FALSE; //using to indicate computers turn is over
		}

  	}

	if (number_of_sticks <= 1){ //using to indicate to the computer that the game is over

		if (CPUturn==FALSE){ //since CPU turn automatically sets itself false during it's turn, False = last turn taken
			printf("Your Opponent Wins!\n");
		}
		else{ //using to indicate if it's not false, then the other party wins
			printf("Player Wins!\n");
		}
		return 0; //using to end game
	}
}
  
  return 0; //end of program
}

//-----------------FUNCTIONS----------------------

int computersMove(int x){

  if (x%4 == 0){ //using to indicate if a number is a multiple of 4 to determine if CPU needs to  take 1 stick
    return 1;
  }
  else{ //Using to indicate if number is not a multiple of 4 to determine if the CPU needs to take x%4's outcome of sticks
    return x%4;
  }

}

