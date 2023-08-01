//NAME: Kamren Northrop
//DATE: 1/18/23
//CLASS: CSE 222 - Intro to Data Structures

//------LIBRARIES------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------NODE DECLARATION PROTOYPE------
struct DataNode{ 
  char data[16];
  struct DataNode *next;
};

//------FUNCTION PROTOTYPES------
struct DataNode *init();
int add(struct DataNode *list, char *data);
void print(struct DataNode *list);
int delete(struct DataNode *list, char *data);
int search(struct DataNode *list, char *data);
void cleanup(struct DataNode *list);
