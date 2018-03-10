#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct RBTNode
{
	int val;
	bool color;								// "false" for black, "true" for red
	struct RBTNode * right, *left, *parent;
} RBTnode;

// utility function to declare new node
RBTnode* New(int data);

// utility function to return 0 (for black color) for leaves (NULL ones)
bool Color(RBTnode* x);

// utility function to perform right rotation about node "x"
void rightrotate(RBTnode* x);

// utility function to perform left rotation about node "x"
void leftrotate(RBTnode* x);

// utility function to facilitate insertion in BST way
RBTnode* BSTinsert(RBTnode* root, RBTnode* node);

// function to insert key of val = "data"
// insert in BST way, then rebuild the tree by reassigning and/or rotating
RBTnode* RB_Insert(RBTnode* root, int data);

// function to rebuild and maintain properties of R-B Tree
void RB_Insert_Rebuild(RBTnode* root, RBTnode* x);

// search recursively for a given value in the R-B Tree
RBTnode* Search(RBTnode* root, int data);

// function to delete node "z"
void RB_Del( RBTnode* root, RBTnode* z);

// function to rebuild at z's position is it's father is black
void RB_Del_Rebuild(RBTnode* root, RBTnode* x);

// function to do Level Order Traversal of the graph
void LevelOrder(RBTnode* root);

// Print nodes at a given level
void PrintLevel(RBTnode* root, int level);

// Compute the height of a node
// length of longest path from the node to a leaf
int height(RBTnode* node);