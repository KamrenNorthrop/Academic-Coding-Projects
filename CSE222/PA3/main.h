//Name: Kamren Northrop
//Date: 2/22/23
//Class: CSE 222 - Intro To Data Structures
//Assignment: PA3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char *plate;
	char *first;
	char *last;
	struct node *left;
	struct node *right;
};

typedef struct node* Node;

int balanced(Node root);
int height(Node root);
int search(Node root, char *plate, char *first, char *last);

Node add(Node root, char *plate, char *first, char *last);
Node delete(Node root, char *plate);

void LNR(Node root);
void NLR(Node root);
void LRN(Node root);

void freeNode(Node root);
void treeFree(Node root);
