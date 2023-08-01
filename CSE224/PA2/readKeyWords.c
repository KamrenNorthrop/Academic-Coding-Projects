/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index
Due Date: 10/21/22
Finished Date: 10/20/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.              Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are             present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input.
*/

#include "index.h" //including header file

int readKeyWords(char *filename, char keyWords[100][32]){
  FILE *fp; //declaring file variable
  int keyWords_index=0;//using as array index
  char word[35];//using to hold a word from keyWords.txt file

  fp = fopen(filename, "r");//opening file and setting it to r to read only
 
  if (!fp){ //if it's not file, return -1
    return -1;
  }

  while(fgets(word, 35, fp) != NULL){//loop to read file and save to word as long as it's greater then 0, as it'd indicate a failure 
  	word[strlen(word)-1] = '\0'; //Removing \n that comes with fgets.
	for(int i=0; i <= strlen(word); i++){//loop to iterate through the length of the word
        	keyWords[keyWords_index][i] = toupper(word[i]);//saving the converted to uppercase words to keywords
  	}
  	keyWords_index++;//incrementing keywords index to identify the number of words read	
  }
  fclose(fp);//closing file
 
  return keyWords_index;//returning the number of keywords read.
}
