#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BSTNode* createNode(char *data);
int getKey(char *data);
int getFreq(char *data);
struct BSTNode* insert(struct BSTNode* root, char *data);
void preOrderTraversal(struct BSTNode* root);
void find (struct BSTNode *p, int data);
int height(struct BSTNode* root);
void rotation(struct BSTNode* root);
struct BSTNode* rotateLeft(struct BSTNode* parentPtr);
struct BSTNode* rotateRight(struct BSTNode* parentPtr);

struct BSTNode {
    int key;
    int frequency;
    struct BSTNode *left;
    struct BSTNode *right;
};


int main() {
//this part of code is for checking the file for how many lines are there in the file so we can declair the size of array depending on it
//--------------------------------------------------------------------------------------------------------------
    FILE *file1;
    char filename1[] = "input2.txt"; 
    
    // Open the file
    file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename1);
        return 1;
    }

    char string[10];
    int lineCount = 0;
    while (fgets(string, 10, file1) != NULL) {
        lineCount++;
    }

//this part of code places the data from the file to an array in the same order
//--------------------------------------------------------------------------------------------------------------

    FILE *file2;
    char filename2[] = "input2.txt"; 
	
    // open the file and check if it is empty
    file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename2);
        return 1;
    }

    char array[lineCount][10];
	int size = 0;
	
    // read data line by line from the file into the array
    while (fgets(array[size], 10, file2) != NULL) {
        size++;
        if (size > lineCount) {
            fprintf(stderr, "Array size exceeded maximum limit\n");
            break;
        }
    }

    // Close the file
    fclose(file1);
    fclose(file2);

    struct BSTNode* root = NULL;
	int i = 0;
    for (i = 0; i < lineCount-1; i++) {
        root = insert(root, array[i]);
    }

    preOrderTraversal(root);

    find(root,8);
    printf("\n");
    
    int possibleRotationNumber = height(root);
	
	// rotation function is used "height" times because if there are smaller frequency values in grandparent nodes, we can avoid errors in this way. 
	// and we are using height for number of function calling because it is the maximum possible value of nodes with lower frequency.
	for(i = 0 ;i < possibleRotationNumber; i++){
		rotation(root);
	}
	
    preOrderTraversal(root);
	
    return 0;
}


int getKey(char *data){
    char dataKey[10];
    int i;
    for(i = 0;i < 10;i++){
        if(data[i] != '\n'){
            dataKey[i] = data[i];
        }
        else{
            break;
        }
    }
    return atoi(dataKey);
}


//--------------------------------------------------------------------------------------------------------------
struct BSTNode* createNode(char *data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    if (newNode == NULL) {
        return 0;
    }

    newNode->key = getKey(data);
    newNode->frequency = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}


//--------------------------------------------------------------------------------------------------------------
struct BSTNode* insert(struct BSTNode* root, char *data) {
    // If the tree is empty, return a new node
    if (root == NULL) {
        return createNode(data);
    }

    // Otherwise, recur down the tree
    if (getKey(data) < root->key) {
        root->left = insert(root->left, data);
    } else if (getKey(data) > root->key) {
        root->right = insert(root->right, data);
    }

    // Return the (unchanged) node pointer
    return root;
}

void preOrderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        printf("%d,%d ", root->key,root->frequency);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void find(struct BSTNode *p, int data)
{
    if (p != NULL)
    if (data < p->key){
        find(p->left , data);
    }
    else if ( data > p->key){ 
        find(p->right , data);
        
    }
    else if(p->key == data) {
        p->frequency += 1;
    }
}
// Right rotation is used for greater frequency values in left child. 
struct BSTNode* rotateRight(struct BSTNode* parentPtr){
	struct BSTNode* childPtr;
	
	childPtr = parentPtr->left;
	parentPtr->left = childPtr->right;
	childPtr->right = parentPtr;
	
	return childPtr;
	
}
//Left rotation is used for greater frequency values in right child.
struct BSTNode* rotateLeft(struct BSTNode* parentPtr){
	struct BSTNode* childPtr;
	
	childPtr = parentPtr->right;
	parentPtr->right = childPtr->left;
	childPtr->left = parentPtr;
	
	return childPtr;
}

struct BSTNode* rotation(struct BSTNode* root){
	
	if (root->right != NULL){
		if (root->frequency < root->right->frequency){
			return rotateLeft(root);
		}
		else 
			rotation(root->right);
	}
	
	if (root->left != NULL){
		if(root->frequency < root->left->frequency){
			return rotateRight(root);
		}
		else
			rotation(root->left);
	}
	
	return root;			
}

//Checking height for both right and left subtrees. At the end, it returns the maximum value.
int height(struct BSTNode* root) {
    int hLeft, hRight;
    
	if (root == NULL)
        return 0;
    
    if (root->right == NULL)
        hRight = 0;
    else
        hRight = height(root->right) + 1 ;
	
	if (root->left == NULL)
        hLeft = 0;
    else
        hLeft = height(root->left) + 1;
    
	if (hLeft > hRight)
        return (hLeft);
    return (hRight);
}





