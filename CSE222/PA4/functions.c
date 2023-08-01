#include "main.h"
//Names: Kamren Northrop & Wyatt Pigeon


struct maxNode maxVal(int capacity, struct item items[], int arrayLen, struct maxNode cache[]){
    struct maxNode bestResult;
    int bestValue = 0;
    bestResult.maxVal = 0;

    if (capacity <= 0){
    	return bestResult;
    }

    for (int j = 0; j < 128; j++){
        bestResult.items[j] = 0;
    }

    if (cache[capacity].maxVal > 0){
        return cache[capacity];
    }

    for (int i = 0; i < arrayLen; i++){
        if (items[i].weight <= capacity){
            struct maxNode subResult = maxVal((capacity - items[i].weight), items, arrayLen, cache);

            if (subResult.maxVal + items[i].value > bestResult.maxVal){
                bestResult = subResult;
                bestResult.maxVal = subResult.maxVal + items[i].value;
                bestResult.items[i]++;
            }
        }
    }

    cache[capacity] = bestResult;
    return bestResult;
}

