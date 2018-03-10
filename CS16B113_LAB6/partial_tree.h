#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>

typedef struct BSTNode
{
	int val;
	int count;
	bool markdel;
	struct BSTNode* left, *right;
} BSTnode;

// counter to facilitate balancing using inorder traversal
int arrcount;

// function to declare new node
BSTnode* New(int x);

// function to insert a value in the BST
BSTnode* Insert(BSTnode* head, int x);

// function to rebuild the WHOLE BST if more than half nodes are deleted
BSTnode* Delete(BSTnode* root, int cnt_del);

// function to convert whole BST to array
void BSTtoSortedArray_Del(BSTnode* node, int* arr);

// function to rebuild subtree at a node(including it) using inorder traversal
BSTnode* Rebuild(BSTnode* root);

// recursive function to convert any subtree to a sorted array
void BSTtoSortedArray(BSTnode* node, int* arr);

// function that constructs Balanced Binary Search Tree from a sorted array
BSTnode* sortedArrayToBST(int arr[], int start, int end);

// function to do Level Order Traversal of the graph
void LevelOrder(BSTnode* root);
 
// Print nodes at a given level
void PrintLevel(BSTnode* root, int level);
 
// Compute the height of a node
// length of longest path from the node to a leaf
int height(BSTnode* node);

// search recursively for a given value in the BST
BSTnode* Search(BSTnode* root, int data);