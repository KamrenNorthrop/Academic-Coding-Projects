/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index
Due Date: 10/21/22
Finished Date: 10/20/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.              Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are             present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input.
*/

#include "index.h" // including header file

char *getWord(char *word){
  char bird[32] = {0};//setting bird to size 32 of all null terminators to replace
  int bird_index = 0;//using to index bird
    
  while(bird_index < 31){ //saying if less then 31 because we know all words will be within the 0-31 range
  	char character = myGetChar(); // calling myGetChar to read characters
                
        if (bird_index == 0) // if index = 0, checking for EOF or if there is a leading space
        {
            if (character == EOF) // checking if it's EOF? if so NULL
                return NULL; //Null
            
            if (isspace(character)) //checking if it's a space
                continue; //skip
        }
        
        if (!character) // checking to see if what is being read is not a character
            continue;//skip
       
        if (isalpha(character)) // checking to see if it is a character
        {
            bird[bird_index] = character; // indexing through bird to save characters to create word because bird is the word.
 	    bird_index++;//indexing bird to get ready for new char and create word
        }
        
        else{
            break;
   	}
  }
  strcpy(word, bird);// copying bird to word, so that bird is the word.
    
  return word; // returning the word that was copied from bird.
}
