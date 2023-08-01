//NAME: Kamren Northrop
//DATE: 2/2/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *hashEntry;

struct node{
  char *plate;
  char *first;
  char *last;
  struct node *next;
};

hashEntry *hashInit(int hashsize);

int hash(char *plate);

int hashFind(hashEntry *hashTable, char *plate, char *first, char *last);

void hashDist(hashEntry *hashTable);

void hashDump(hashEntry *hashTable, int cellNum);

void hashFree(hashEntry *hashTable);

void hashAdd(hashEntry *hashTable, char *plate, char *first, char *last);

struct node *listInit();

void listAdd(struct node *sent, char *plate, char *firstname, char *lastname);

int listFind(struct node *sent, char *plate, char *firstname, char *lastname);

int listLen(struct node *sent);

void listPrint(struct node *sent);

void listFree(struct node *sent);


