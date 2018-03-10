#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct BSTNode
{
	int val;
	bool markdel = false;
	struct BSTNode* left, *right, *parent;
} BSTnode;

BSTnode* New(int x)
{
	BSTnode* temp = (BSTnode*)malloc(sizeof(BSTnode));
	temp->val=x;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;
	return temp;
}

BSTnode* Insert(BSTnode* head, int x)
{
	if(head == NULL)
		return New(x);

	if(x < head->val)
	{
		head->left = Insert(head->left, x);
		head->left->parent = head;
	}
	else if(x > head->val)
	{
		head->right = Insert(head->right, x);
		head->right->parent = head;
	}

	return head;
}

BSTnode* Search(BSTnode *root, int data)
{
    if(root == NULL)
		return NULL;

    BSTnode* cursor = root;

    while(cursor != NULL)
    {
        if(data < cursor->data)
            cursor = cursor->left;

        else if(data > cursor->data)
        	cursor = cursor->right;

        else
        	return cursor;
    }
    return	cursor;
}

BSTnode* delete_node(BSTnode* root, int data)
{
    if(root == NULL)
        return NULL;
 
    BSTnode *cursor;
    if (root->left == NULL)
	{
		cursor = root->right;
		free(root);
		root = cursor;
	}
	else if (root->right == NULL)
		{
			cursor = root->left;
			free(root);
			root = cursor;
		}
		else    //2 children
		{
			cursor = root->right;
			BSTnode *parent = NULL;
			
			while(cursor->left != NULL)
			{
				parent = cursor;
				cursor = cursor->left;
			}

			root->data = cursor->data;

			if (parent != NULL)
				parent->left = delete_node(parent->left, parent->left->data);
	
			else
				root->right = delete_node(root->right, root->right->data);
		}
    return root;
}

int main()
{
	srand(time(NULL));
	clock_t start, end;

	int NUM_POINTS = 6;
	double xvals[NUM_POINTS], yvals[NUM_POINTS];

	int cnt = 0, i;
	int dirn;
	int cnt_ins = 0, cnt_del = 0;
	int n;

	for(n=1024; cnt < NUM_POINTS; n*=2)
	{
		xvals[cnt] = n;
		cnt_ins = cnt_del = 0;

		start = clock();

		for(i=0; i<n; i++)
		{
			dirn = rand()%3;

			switch(dirn)
			{
				case 0:
					cnt_insert++;

					BSTnode* root = NULL;
					root = Insert(root, gen);
					break;

				case 1:
					BSTnode* temp = Search(gen);
					break;

				case 2:
					BSTnode* mark = Search(gen);
					if(mark)
						cnt_del++;
					else
						break;

					if(cnt_del < cnt_insert/2)
					{
						mark->markdel = true;
					}
					else
						;
						//function for del
					break;

				default: break;
			}
		}

		end = clock();

		yvals[cnt++] = (start-end);

	}


	char* commandsForGnuplot[] = {"set title \"PLOT_LAB_6\" ", "plot 'DataLab6.temp'"};
	FILE* temp = fopen("DataLab6.temp", "w");

	for(i=0; i<NUM_POINTS; i++)
		fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);


	return 0;
}