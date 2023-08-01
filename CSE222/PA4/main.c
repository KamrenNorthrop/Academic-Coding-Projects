//Names: Wyatt Pigeon, Kamren Northrop
//Date: 3/6/23
//Class: CSE 222 - Intro to datastructres
//Assignment: PA4 - Knapsack Problem
/*Synopsis: PA4 is a dynamic programing solution to the 0-1 knapsack problem. The program will accept two command line arguments: a bag capacity and a datafile. It will then read the datafile which will include items, their value, and their weights and save them into a structure. Once the items are read, it will then call a maxVal function     which will calculate the maximum value based on the bag capacity using dynamic programming. The function will then return the maximum value that is able to be achieved to   the user, inform them what that value is and what items will need to be picked to achieve that value.*/ 

#include "main.h" //Including libraries, structure/function declarations

int main(int argc, char **argv){ //start of main
    int capacity; //holds the capacity of the bag from command line argument
    struct item items[128]; //holds the weight, value, and names of the items from the database file
    int arrayLen = 0; //tracking the length of the arrays created
    char input[1024]; //using to read from file
    char *filename; //pointer to database file
    FILE *fp; //using to open file

    if (argc != 3){ //if user does not give 3 command line arguments
        printf("Usage: %s <capacity> <filename>\n", argv[0]); //inform of usage format
        return -1; //exit program
    }

    if (sscanf(argv[1], "%d", &capacity) != 1 || capacity <= 0 || capacity > 1024){ //if sscanf conversion does not work, or capacity is <=0 or >1024
        printf("Illegal capacity: should be between 1 and 1024.\n"); //inform user of legal capacity range
        return -1; //exit program
    } 
    
    filename = argv[2]; //pointing to database file
    fp = fopen(filename, "r"); //opening and reading database file

    if (!fp) { //if file can't be opened
        printf("Could not open file: %s\n", argv[2]); //inform user, file can't be opened
        return -1; //exit program
    }

    while (fgets(input, 1024, fp) != NULL){ //while we're not at the end of the file
        char name[128]; //storing names
        int value, weight; //storing values and weights of items

        if (sscanf(input, "%s %d %d", name, &value, &weight) != 3) { //if conversion is not successful
            printf("Format error in %s:\n %s", filename, input); //inform user there is a format error
	    printf("Error: no weight/value pairs read\n"); //inform user weight / values are missing
            return -1; //exit program
        }
        if (arrayLen == 129) { //if the array exceeds the assumed 128 items
            printf("Too many items in file (maximum 128)\n"); //inform user too many items
            return -1; //exit program
        }

        items[arrayLen].value = value; //save value read to struct items value section
        items[arrayLen].weight = weight; //save weight read to struct items weight section
        strcpy(items[arrayLen].name, name); //save name read to struct items name section
        arrayLen++; //tracking array length
    }

    fclose(fp); //close file
//------END OF READING FILE------

//------START OF THE GOOD STUFF------
    struct maxNode cache[capacity+1]; //initializing cache for dynamic programming

    for (int i = 0; i <= capacity; i++){ //while i is less then or equal to the capacity chosen
        cache[i].maxVal = 0; //fill cache index i's with 0's
    }

    printf("Weight  Value  Name\n"); //printing weight, value, names read from file for user
    printf("------  -----  ----\n"); //printing lines for formatting
    for (int j = 0; j < arrayLen; j++){ //while j is less than the arrayLen tracked
    	printf("%4d   %4d    %-4s\n", items[j].weight, items[j].value, items[j].name); //print weight right justified, value right justified, and name left justified
    }
    printf("-------------------------"); //printing lines for formatting

    struct maxNode result = maxVal(capacity, items, arrayLen, cache); //initializing results struct, calling maxVal function 

    printf("\nBag's Capacity=%d\n", capacity); //informing user of capacity chosen
    printf("Maximum value: %d\n", result.maxVal); //informing user of maxVal achievable 
    printf("Items in the bag:\n"); //informing user of the items in bag to achieve the maxVal

    for (int i = 0; i < arrayLen; i++){ //while i is less then the array length
        if (result.items[i] > 0) { //and the index is greater then 0
            printf("Item %d (%s): %d \n", i, items[i].name, result.items[i]); //print item number, name of item, and the amount of that item in the bag to achieve max value
        }
    }

    return 0; //exit program
} //end of main
