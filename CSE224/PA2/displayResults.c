/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index
Due Date: 10/21/22
Finished Date: 10/20/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.              Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are             present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input.
*/

#include "index.h" //including header file

void displayResults(char keyWords[100][32], int tally[100], int numWords){

  for(int i=0; i < numWords; i++){//incrementing through the number of words
  	printf("%s : %d\n", keyWords[i], tally[i]); //printing the keywords saved, printing the tally saved
  
  }

  return; //returning
}
