#include "rb_tree.h"

// utility function to declare new node
RBTnode* New(int data)
{
	RBTnode* x = (RBTnode*) malloc(1*sizeof(RBTnode));

	x->val = data;
	x->color = 1;	//color every new node red
	x->left = NULL;
	x->right = NULL;
	x->parent = NULL;

	return x;
}

// utility function to return 0 (for black color) for leaves (NULL ones)
bool Color(RBTnode* x)
{
	if( x == NULL)
		return false;
	else
		return x->color;
}

// utility function to perform left rotation about node "x"
void leftrotate(RBTnode* x)
{
	// reassign left child of y
	RBTnode* y = x->right;
	x->right = y->left;

	if(y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;

	// make y the child of x's parent
	if(x->parent != NULL)
	{
		if( x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	// assign x as y's child
	y->left = x;
	x->parent = y;
}

// utility function to perform right rotation about node "x"
void rightrotate(RBTnode* x)
{
	// reassign right child of y
	RBTnode* y = x->left;
	x->left = y->right;

	if(y->right != NULL)
		y->right->parent = x;

	y->parent = x->parent;

	// make y the child of x's parent
	if(x->parent != NULL)
	{
		if( x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}

	// assign x as y's child
	y->right = x;
	x->parent = y;
}

// utility function to facilitate insertion in BST way
RBTnode* BSTinsert(RBTnode* root, RBTnode* node)
{
    // If the tree is empty, return a new node
    if (root == NULL)
       return node;
 
    // else, go down the tree
    if (node->val < root->val)
    {
        root->left  = BSTinsert(root->left, node);
        root->left->parent = root;
    }
    else if (node->val > root->val)
    {
        root->right = BSTinsert(root->right, node);
        root->right->parent = root;
    }
 
    // return the unchanged root pointer
    return root;
}

// function to insert key of val = "data"
// insert in BST way, then rebuild the tree by reassigning and/or rotating
RBTnode* RB_Insert(RBTnode* root, int data)
{
	RBTnode* node = New(data);

	root = BSTinsert(root, node);

	RB_Insert_Rebuild(root, node);

	return root;
}

// function to rebuild and maintain properties of R-B Tree
void RB_Insert_Rebuild(RBTnode* root, RBTnode* x)
{
    RBTnode* p = NULL;
    RBTnode* p_p = NULL;
 	
 	// rebuilding is required only when P(x) is red (i.e. "true")
    if (x!=root && Color(x->parent) )
    {
    	p = x->parent;
        p_p = x->parent->parent;
 
        //  Case 1: P(x) is left child of P(P(x))
        if (p == p_p->left)
        {
        	RBTnode* y = p_p->right;
 
            // Case 1.1: Uncle of x is also red; Recoloring required
            if ( Color(y) == true)
            {
                p_p->color = true;
                p->color = false;
                y->color = false;
                x = p_p;
            }
            else
            {
            	// Case 1.2.1: x is right child of its parent
            	if (x == p->right)
            	{
            		leftrotate(p);
            		//swap x & p(x)
            		x = p;
            		p = x->parent;
            	}

				// Case 1.2.2: x is left child of its parent
				p->color = false;
				p_p->color = true;
				rightrotate(p_p);
				x = p;
			}
		}

		// Case 2: P(x) is right child of P(P(x))
		else
		{
			RBTnode* y = p_p->left;
			
			// Case 2.1: Uncle of x is also red; Recoloring required
			if (Color(y) == true)
			{
				p_p->color = true;
				p->color = false;
				y->color = false;
				x = p_p;
			}
			else
			{
				// Case 2.2.1: x is left child of its parent
				if (x == p->left)
				{
					rightrotate(p);
					x = p;
					p = x->parent;
				}
				
				// Case 2.2.2: x is left child of its parent
				p->color = false;
				p_p->color = true;
				leftrotate(p_p);
				x = p;
			}
		}
	}

	root->color = false;
}

// search recursively for a given value in the R-B Tree
RBTnode* Search(RBTnode* root, int data)
{
    if(root == NULL)
		return NULL;

    RBTnode* cursor = root;

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

// function to delete node "z"
void RB_Del(RBTnode* root, RBTnode* z)
{
	RBTnode* y = NULL;		// node which will replace z initially
	RBTnode* x = NULL;		// node which will replace z finally

	// checking it's number of children
	if(z->left == NULL || z->right == NULL)
		y = z;
	else
	{
		//inorder successor
		RBTnode* temp = z;
		while(temp->left != NULL)
			temp = temp->left;
		y = temp;
	}
	
	if(y->left != NULL)
		x = y->left;
	else
		x = y->right;

	// reassigning parent pointers
	x->parent = y->parent;

	if(y->parent == NULL)
		root = x;
	else	if(y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;

	// reassigning values
	if( y != z)
		z->val = y->val;

	// rebuild required only when father of erstwhile z is black in color
	if(Color(y) == false)
		RB_Del_Rebuild(root, x);
}

// function to rebuild at z's position is it's father is black
void RB_Del_Rebuild(RBTnode* root, RBTnode* x)
{
	// cousin of x
	RBTnode * w = NULL;

	while( x!=root && Color(x) == false)
	{
		// Case 1: x is the left child
		if(x == x->parent->left)
		{
			w = x->parent->right;

			// Case 1.1 : cousin of x is red
			if(Color(w) == true)
			{
				w->color = false;
				x->parent->color = true;
				leftrotate(x->parent);
				w = x->parent->right;
				// reduced to case 1.2 now
			}

			// Case 1.2 : cousin of x is black

			// Case 1.2.1 : both sons of cousin are black
			if(Color(w->left) == false && Color(w->right) == false)
			{
				w->color = true;
				x = x->parent;
			}
			else
			{
				// Case 1.2.2 : right son of cousin = black, left one = red	
				if(Color(w->right) == false)
				{
					w->left->color = false;
					w->color = true;
					rightrotate(w);
					w = x->parent->right;
				}

				// Case 1.2.3 : left son of cousin = black, right one = red
				w->color = x->parent->color;
				x->parent->color = false;
				w->right->color = false;
				leftrotate(x->parent);
				x = root;
			}
		}
		// Case 2: x is the right child
		else
		{
			w = x->parent->left;

			// Case 2.1 : cousin of x is red
			if(Color(w) == true)
			{
				w->color = false;
				x->parent->color = true;
				rightrotate(x->parent);
				w = x->parent->left;
				// reduced to case 2.2 now
			}

			// Case 2.2 : cousin of x is black

			// Case 2.2.1 : both sons of cousin are black
			if(Color(w->right) == false && Color(w->left) == false)
			{
				w->color = true;
				x = x->parent;
			}
			else
			{
				// Case 2.2.2 : right son of cousin = black, left one = red
				if(Color(w->left) == false)
				{
					w->right->color = false;
					w->color = true;
					leftrotate(w);
					w = x->parent->left;
				}

				// Case 2.2.3 : left son of cousin = black, right one = red
				w->color = x->parent->color;
				x->parent->color = false;
				w->left->color = false;
				rightrotate(x->parent);
				x = root;
			}
		}
	}
}

// function to do Level Order Traversal of the graph
void LevelOrder(RBTnode* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        PrintLevel(root, i);
}
 
// Print nodes at a given level
void PrintLevel(RBTnode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d\n", root->val );
    else if (level > 1)
    {
        PrintLevel(root->left, level-1);
        PrintLevel(root->right, level-1);
    }
}
 
// Compute the height of a node
// length of longest path from the node to a leaf
int height(RBTnode* node)
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
