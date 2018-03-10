#include "partial_tree.h"

// counter to facilitate balancing using inorder traversal
int arrcount;

// function to declare new node
BSTnode* New(int x)
{
	BSTnode* temp = (BSTnode*)malloc(sizeof(BSTnode));

	// initialising all it's parameters
	temp->val=x;
	temp->left = temp->right = NULL;
	temp->count = 1;
	temp->markdel = false;

	return temp;
}

// function to insert a value in the BST
BSTnode* Insert(BSTnode* head, int x)
{
	if(head == NULL)
		return New(x);

	// left insertion
	if(x < head->val)
	{
		head->count++;
		head->left = Insert(head->left, x);

	// check if half-balance and rebuild if necessary
		if(head->left->count > (head->count)/2)
			head = Rebuild(head);
	}
	// right insertion
	else if(x > head->val)
	{
		head->count++;
		head->right = Insert(head->right, x);

	// check if half-balance and rebuild if necessary
		if(head->right->count > (head->count)/2)
			head = Rebuild(head);
	}

	return head;
}

// function to rebuild subtree at a node(including it) using inorder traversal
BSTnode* Rebuild(BSTnode* root)
{
	int* arr = (int*) malloc((root->count)*sizeof(int));

	arrcount = 0;
	// converted the passed subtree to an array in ascending order
	BSTtoSortedArray(root, arr);

	// construct a new BST from this array at the given root
	root = sortedArrayToBST(arr, 0, root->count - 1);

	return root;
}

// recursive function to convert any subtree to a sorted array
void BSTtoSortedArray(BSTnode* node, int* arr)
{
     if (node == NULL)
          return;
	
    // first recur on left child
    BSTtoSortedArray(node->left, arr);

	arr[arrcount++] = node->val;

    // now recur on right child 
    BSTtoSortedArray(node->right, arr);
}

// function that constructs Balanced Binary Search Tree from a sorted array
BSTnode* sortedArrayToBST(int arr[], int start, int end)
{
    // Base Case
    if (start > end)
      return NULL;
 
    // Get the middle element and make it root
    int mid = (start + end)/2;
    BSTnode* root = New(arr[mid]);

    // assign the number of elements below it
    root->count = (end-start)+1;
 
    // Recursively construct the left subtree and make it left child of root
    root->left =  sortedArrayToBST(arr, start, mid-1);

    //Recursively construct the right subtree and make it right child of root
    root->right = sortedArrayToBST(arr, mid+1, end);
 
    return root;
}

// function to rebuild the WHOLE BST if more than half nodes are deleted
BSTnode* Delete(BSTnode* root, int cnt_del)
{
	int* arr = (int*) malloc((root->count - cnt_del)*sizeof(int));

	arrcount = 0;
	// convert the BST to an array in ascending order
	BSTtoSortedArray_Del(root, arr);

	// Balanced BST constructed
	root = sortedArrayToBST(arr, 0, root->count - 1);

	return root;
}

// function to convert whole BST to array
void BSTtoSortedArray_Del(BSTnode* node, int* arr)
{
	if (node == NULL)
		return;
	
    // first recur on left child
    BSTtoSortedArray_Del(node->left, arr);

    if(node->markdel = false)
		arr[arrcount++] = node->val;

    // now recur on right child
    BSTtoSortedArray_Del(node->right, arr);
}

// function to do Level Order Traversal of the graph
void LevelOrder(BSTnode* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        PrintLevel(root, i);
}
 
// Print nodes at a given level
void PrintLevel(BSTnode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->val );
    else if (level > 1)
    {
        PrintLevel(root->left, level-1);
        PrintLevel(root->right, level-1);
    }
}
 
// Compute the height of a node
// length of longest path from the node to a leaf
int height(BSTnode* node)
{
    if (node == NULL)
        return 0;
    else
    {
        // compute the height of each subtree
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        // use the larger one
        if (lheight > rheight)
            return(lheight+1);
        else
        	return(rheight+1);
    }
}

// search recursively for a given value in the BST
BSTnode* Search(BSTnode* root, int data)
{
    if(root == NULL)
		return NULL;

    BSTnode* cursor = root;

    while(cursor != NULL)
    {
    	// check in left subtree
        if(data < cursor->val)
            cursor = cursor->left;

        	//check in right subtree
        else if(data > cursor->val)
        		cursor = cursor->right;

        	//exit on exact match
			else
        		return cursor;
    }

    return	cursor;
}


/*
RBTnode* RBINSERT( RBTnode* root, int data)
{
    RBTnode* z = New(data);
    RBTnode* y = NULL;
    RBTnode* x = root;

    while( x != NULL)
    {
        y = x;
        if( z->val < x->val)    
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if( y == NULL)
        root = z;
    else if( z->val < y->val )
            y->left = z;
        else 
            y->right = z;

    z->left = NULL;
    z->right = NULL;
    z->color = true;

    Rebuild_Insert(root, z);

    return root;
}
*/