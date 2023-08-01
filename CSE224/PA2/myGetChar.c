/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index
Due Date: 10/21/22
Finished Date: 10/20/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.              Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are             present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input.
*/

#include "index.h" //including header file

int myGetChar(){
  char character;

  while(character = getchar()){ //calling getchar and saving it to character, should update through each iteration 		
	if (isspace(character)){//check if it's a space
  		return (' ');//if so, returning a space.
  	}

	if (isalpha(character)){//checking if it's a character
  		return toupper(character);//if so, converting it to uppercase and returning the uppercase character.
  	}

	if (character == EOF){//if it's equal to the EOF
  		return EOF;//returning EOF
  	}
  }
  return -1;//returning -1 if error
}
