//Names: Wyatt Pigeon, Kamren Northrop
//Date: 3/6/23
//Class: CSE 222 - Intro to datastructres
//Assignment: PA4 - Knapsack Problem

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct maxNode{
    int maxVal;
    int items[128];
};

struct item{
    int value;
    int weight;
    char name[128];
};

struct maxNode maxVal(int capacity, struct item items[], int arrayLen, struct maxNode cache[]);
