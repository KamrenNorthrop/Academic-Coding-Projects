/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index 
Due Date: 10/21/22
Finished Date: 10/20/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.    	       Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are   	    present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input. 
*/

#include "index.h" // including header file for all libraries and function declarations.

void main()
{
  int numWords; // using to store the number of words from readKeyWords function
  char keyWords[100][32]; // storing keyWords
  int count[100] = {0}; // storing the tally count

  numWords = readKeyWords("keywords.txt", keyWords); // storing number of words to variable based on words read in txt file.

  if (numWords == -1){ // returning -1 if error with reading file
  	printf("Error: Couldn't Open KeyWords File");
	return; //exiting
  }
  
  char newWord[35]; //using to store words   

  while(NULL !=  getWord(newWord)){ //throwing word into getWord call to cross reference with keyWords in Tally
 	 tally(newWord, keyWords, count, numWords); // cross referencing STDIN with KeyWords.txt words
  }

  displayResults(keyWords,count,numWords); // displaying the results of occurences of words after the cross reference between STDIN and KeyWords.txt

  return; //program end
}
