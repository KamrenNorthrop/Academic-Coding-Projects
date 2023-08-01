/*
Name: Kamren Northrop
Class: CSE224 - Programming Tools
Assignment: PA2 - Index
Due Date: 10/21/22
Finished Date: 10/18/22
Synopsis: This index program will read both stdin input and a keyWords.txt file, convert the words present to uppercase and remove any non-characters before saving them.              Once the words are converted and saved, the program will then compare each word and keep a tally of any word that pops up in the stdin input with words that are             present in the keyWords.txt file. It will then display how many times those words appear in the given stdin input.
*/

//----FUNCTION DECLARATIONS----
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

int readKeyWords(char *filename, char keyWords[100][32]);
void tally(char *word,char keyWords[100][32],int count[100],int numWords);
char *getWord(char *word);
int myGetChar();
void displayResults(char keyWords[100][32],int tally[100],int numWords);
