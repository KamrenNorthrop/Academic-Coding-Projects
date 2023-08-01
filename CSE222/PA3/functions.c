//NAME: Kamren Northrop
//DATE: 2/22/23
//CLASS: CSE 222 - Intro to Data Structures
//Assignment: PA3

#include "main.h" //including header file for all library / function declarations

//------freeNode-----
/*freeNode is an extra function I chose to make for cleaner code. Passing in the root of the tree as an argument, freeNode will then free(): plate, first, and last area's   malloced for the node and then it will also free the node itself.*/

void freeNode(Node root){ //start of function definition
	free(root->plate); //freeing memory malloc'd for plate
	free(root->first); //freeing memory malloc'd for first
	free(root->last); //freeing memory malloc'd for last
	free(root); //freeing memory malloc'd for root
} //end of freeNode

//------SEARCH------
/*Search is a function that will locate if a given entry is present in the tree. When the program gets a plate from the user via stdin, it will call the search function and begin a series of string comparisons. If it determines that the plate string in the root is greater then zero it will shift left, if it is less then zero it will shift right and compare the strings in the new node until the comparison equals 0. If the search function finds the given string, it will return 1, otherwise, if the root is NULL or   the given string is not in the tree the function will return 0.*/
 
int search(Node root, char *plate, char *first, char *last){ //start of function definition
	//if the tree is empty or string is not found 
	if (root == NULL){ //if the root is NULL
		return 0; //not found
	}

	//If the strings match
	if (strcmp(root->plate, plate) == 0){ //if strings match
		strcpy(first, root->first); //copy the root->first string to first array
		strcpy(last, root->last); //copy the root->last string to last array 
		return 1; //return one
	}
	//Left
	if (strcmp(root->plate, plate) > 0){ // if comparison between root->plate and plate is greater then 0
		return(search(root->left, plate, first, last)); //recurse through the left sub tree
	} 
	//Right
	else{ //otherwise
		return(search(root->right, plate, first, last)); //recurse through the right sub tree
	}
		
}

//------DELETE------
/*Delete is used by the user to delete a plate from the given tree. If the user uses the command *DELETE followed by a plate at stdin, the main program will use the search 
function to identify if the string is in the tree. If it is it will call the delete function. Once the delete function is called it will check to see if the tree is empty, 
if it is, thefunction will return NULL. Otherwise, it will begin a series of string comparisons. If the comparison between the plate passed in and root->plate is less  then 0 the function will recurse through the left sub tree, if the comparison is greater then 0, the function will recurse through the right sub tree. Once the node is found
the function will then delete the node associated with t he matching string by freeing the malloc'd memory. If the user attempts to delete the root of the tree itself, the  delete function will then do a series of sub checks. It will first check to see if there is a left sub tree, if so, it will check to see if the root of the left sub tree has any right children. If so, it will find the right most node until it hits one where the right is NULL idenitfying this node as the biggest in the left sub tree. From there it will then make the parent node of that biggest node adopt the biggest nodes left children, then it will make that biggest node adopt the left and right children of the   root and then it will delete the root. In the case of a left sub tree being present but the root of the left sub tree does not have any right children, the function will    then make the root of the left sub tree adopt the right children of the root inevitably making the root of the left sub tree the root of the overall tree, then release the  previous root. If there is no left sub tree, the function will then make the roots first right child the new root of the tree. The function will then return the root of the tree which will be captured by a variable in main.*/

Node delete(Node root, char *plate){ //start of function definition
	//if root is NULL
	if (root == NULL){
		return root; // return the root or NULL
	}

	//if note deleting root: >0 left, <0 right
        if(strcmp(plate, root->plate) <  0){ //if the plate string is less then root->plate
        	root->left = delete(root->left, plate); //recurse through left sub tree
		return root; //returning root
        }
        else if (strcmp(plate, root->plate) > 0){ //Otherwise if plate string is greater then 0
                root->right = delete(root->right, plate); //recurse through right sub tree
		return root; //return root
                
        }
	else{ //otherwise, comparison == 0
	//If deleting root of the tree
		//case 1: Replace root with the largest node in the left sub tree
		if (root->left != NULL && root->left->right != NULL){ //if a left sub tree exists and the left sub tree has right children
			Node biggestNode = root->left; //pointing biggest node at the root of the left sub tree
			Node parent = root; //pointing parent at the root of the entire tree

			while (biggestNode->right != NULL){ //while the right child of the biggest node is not NULL
				parent = biggestNode; //parent iterates to the node biggestNode currently occupies
				biggestNode = biggestNode->right; //biggestNode iterates right to the next node
			}
			
			//When the while loop breaks because the nodes right child is NULL - biggestNode found
			parent->right = biggestNode->left; //parent node of the biggestNode adopts the biggestNodes left children as its right children
			biggestNode->left = root->left; //biggestNode adopts the left children of the root of the tree on its left
			biggestNode->right = root->right; //biggestNode adopts the right children of the root of the tree on its right
			freeNode(root); //free's the memory allocated for the previous root of the tree

			return biggestNode; //returns biggestNode as the new root of the tree
		}//end of case 1

		//case 2: Left sub tree exists, no right children
		else if (root->left != NULL && root->left->right == NULL){ //else if a left sub tree exists but the root of the left sub tree has no right children
			Node newRoot = root->left; //set variable newRoot to point to the root of the left sub tree
			newRoot->right = root->right; //newRoot adopts the right children of the original root of the tree
			freeNode(root); //free's the memory allocated for the previous root of the tree

			return newRoot; //returns newRoot as the new root of the tree
		} //end of case 2
	
		//case 3: no left sub tree, or left child equals NULL
		else if (root->left == NULL){ //if the left sub tree doesn't exist, or a left child doesn't exist
			Node newRoot = root->right; //set variable newRoot to point to the root of the right sub tree
			freeNode(root); //free's the memory allocated for the previous root of the tree

			return newRoot; //returns newRoot as the new root of the tree
		} //end of case 3
	}//end of strcmp
}//end of delete

//------ADD------
/*Add is used to add new information to the tree. When the main function is reading the file and parsing the data it will call this function. Once called, the function will then begin a series of string comparisons. If the comparison results in an int greater then zero, if it results in an int less then zero the functionw ill shift left. Once  add encounters the first NULL value, it will then allocate memory for the node and all sections needed to save the data. Once the memory is allocated, add will then strcpy  all the data into the correct locations to be stored. Once the data is stored in the node, it will then set this new nodes right and left children to be NULL and then returnthe root.*/

Node add(Node root, char *plate, char *first, char *last){ //Beginning of function definition
	if (root == NULL){ //if the tree is empty or encounters a NULL value
		//allocate: root, plate, first, last.
		root = malloc(sizeof(struct node)); //allocate memory for the root node
		root->plate = malloc((strlen(plate)+1)*(sizeof(char))); //allocate memory for the plate section of root
		root->first = malloc((strlen(first)+1)*(sizeof(char))); //allocate memory for the first section of root
		root->last = malloc((strlen(last)+1)*(sizeof(char))); //allocate memory for last section of root

		//copy data: strcpy plate, first, last
		strcpy(root->plate, plate); //copying plate string to plate section of root
		strcpy(root->first, first); //copying first string to first section of root
		strcpy(root->last, last); //copying last string to last section of root

		//set left right to NULL
	 	root->left=root->right=NULL; //setting new nodes children on right and left to be NULL
		
		return root; //returning root
	
	}

	//compare
	int result = strcmp(plate, root->plate);//if strcmp is  >0=Right, if <0=Left

	if (result > 0){ //right - if greater then 0
		root->right = add(root->right, plate, first, last); //recursing to right child
	}
	else{ //otherwise, left
		root->left = add(root->left, plate, first, last); //recursing to left child
	}
} //end of add

//------BALANCED-------
/*Balanced will evaluate the height of both the right and left sub trees by calling the height function and storing the returning value into a variable. Once returned, the  function will then take the different of the left-right sub tree and evaluate if the difference is within the balanced range of [-1,1] inclusive. If the difference of the   tree's are out of range, it will return 0 and inform the user that the tree is not balanced. Otherwise, if it is in range, the function will then recurse and check if the   right and left sub trees are also balanced. If they are, the function will return 1 and inform the user that the tree is balanced. If one of the sub trees is not balanced,  the function will return 0 and inform the user the tree is not balanced when *DUMP is called*/

int balanced(Node root){ //start of function definition
	if (root == NULL){ //if the tree is empty
		return 1; //return 1, tree is balanced
	}
	
	int left_height = height(root->left); //calling height and capturing in variable to find the height of the left sub tree
	int right_height = height(root->right); //calling height and capturing in variable to find the height of the right sub tree
	int height_difference = left_height-right_height; //taking the values returned from height and subtracting right from left and storing difference in variable

	if (height_difference < -1 || height_difference > 1){ //if the difference stored in height_difference is less then -1 or greater then 1
		return 0; //out of range, not balanced
	} 
	else{
		if (balanced(root->left) && balanced(root->right)){ //Otherwise, recurse, check to see if right and left sub trees are also balanced
			return 1; //if so, return 1, tree has zen like balance
		} 
		else{
			return 0; //if not, return 0, tree does not have zen like balance
		}
	}
} //end of balance

//------HEIGHT------
/*Height will take in the argument of the root of the tree, from there it will checek to see if the tree is empty. If it is, it will return the value of -1 to indicate such.if the tree is not empty, height will recurse down the left and right sub trees and capture the integer varaible returned in a variable. Once integer values are returned    from the recursive statements, it will then check to see which variable holds a greater integer value and then save that value into another variable: tree_height. Once that is done, the function will then return the value of tree_height+1 to account for the jump from the root to the sub tree and inform the user what that value is when *DUMP is called.*/

int height(Node root){ //start of function definition
	if (root == NULL){ //if the tree is empty
		return -1; //return -1, inform user tree is empty
	}
	//if tree is not empty
	int left_height = height(root->left); //recurse to left sub tree and find height of said sub tree
	int right_height = height(root->right); //recurse to right sub tree and find height of said sub tree
	int tree_height; //variable declaration for storage of value that is determined to be the height of the tree

	if (left_height > right_height){ //if left sub tree has more depth then the right
		tree_height = left_height; //left height is the height of the tree
	} 
	else{ //if right sub tree has more depth
		tree_height = right_height; //right height is the height of the tree
	}

	return tree_height+1; //returning determined height of tree +1 to account for the jump from root to sub tree.
} //end of height

//------LNR TRAV------
/*LNR is a tree print function that will take the information within the tree by accepting the argument of the root of the tree.  When the user calls the command *DUMP, LNR will print the information of the tree in a left, root, right pattern that should display the information from lowest to highest strcmp values.*/

void LNR(Node root){ //start of function definition
	if (root == NULL){ //if the tree is empty,
		return; //exit function
	}
	//if tree is not empty
	LNR(root->left); //recurse into the left most leaf in the left sub tree
	printf("Plate:<%s> Name: %s,%s\n", root->plate, root->last, root->first); //print the data in the node	
	LNR(root->right); //recurse to the right node
} //end of LNR

//------NLR TRAV------
/*NLR is a second tree print function that will take the information within the tree by accepting the argument of the root of the tree. When the user calls the command *DUMPNLR will print the information in a: root, left, right pattern that should display the information of the root first, left sub tree second and then the right sub tree to end.*/

void NLR(Node root){ //start of function definition
	if (root == NULL){ //if tree is empty
		return; //exit function
	}
	//if tree is not empty
	printf("Plate:<%s> Name: %s,%s\n", root->plate, root->last, root->first); //print root of tree
	NLR(root->left); //print left sub tree
	NLR(root->right); //print right sub tree
} //end of NLR

//------LRN TRAV------
/*LRN is a third tree print function that will take the information within the tree by accepting the argument of the root of the tree. When the user calls the command *DUMP NLR will print the information in a: left, right, root pattern that should display the informatino of the left sub tree first, then the right sub tree and then the root to  end.*/

void LRN(Node root){ //start of function definition
	if (root == NULL){ //if the tree is empty
		return; //exit function
	}
	//if tree is not empty
	LRN(root->left); //print left sub tree
	LRN(root->right); //print right sub tree
	printf("Plate:<%s> Name: %s,%s\n", root->plate, root->last, root->first); //print the root
}

/*treeFree is a function that will free all the memory allocated for the nodes upon exit. When the user uses the command of ctrl+D, the program will then exit. When exiting,the treeFree function will recurse through the left sub tree releasing all the nodes and sections of the nodes that have been malloc'd, then it will go through the right subtree also releasing all the nodes and sections of said nodes that have been malloc'd. once the right and left sub trees have been free'd, it will then release the root node itself before ending.*/

void treeFree(Node root){ //start of function definition
	if(root == NULL){ //if the tree is empty
		return; //exit function
	}
	//if tree isn't empty
	treeFree(root->left); //free the allocated memory in the left sub tree
	treeFree(root->right); //free the allocated memory in the right sub tree
	freeNode(root);	//free the root and all the sections that had memory allocated
} //end of treeFree
