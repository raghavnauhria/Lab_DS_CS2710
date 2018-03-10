/*
CS2710
Lab 5

Task: Implementing Quick Sort and Merge Sort

-> decide the course with a select signal given by user

-> sort in ascending order

*/
#include <stdio.h>
#include <stdlib.h>

//functions to implement Quick Sort

//split based on the last element as the pivot
int Split (int a[], int beg, int end)
{
    int pivot = a[end];			//choosing the last element as pivot
    int i = (beg - 1);
 	int temp;					//used for swapping
 	
 	int j;
	for (j=beg; j<end; j++)
    {
        if (a[j] <= pivot)		//"<" to sort in ascending order
        {
            i++;				//increment index of smaller element
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    
    temp = a[i+1];
    a[i+1] = a[end];
    a[end] = temp;

    return (i + 1);
}

void QuickSort(int a[], int beg, int end)
{
    if (beg < end)
    {
        //spl is splitting index, a[spl] is now at right place
        int spl = Split(a, beg, end);
 
        //Separately sort elements before and after partition
        QuickSort(a, beg, spl - 1);
        QuickSort(a, spl + 1, end);
    }
}

//functions to implement Merge Sort

//merge 2 sub arrays while sorting
void Merge(int a[], int beg, int mid, int end)
{
	//succintly storing lengths for sub arrays
    int len_l = mid - beg + 1;
    int len_r =  end - mid;
 
    // creating temp arrays for left and right segments and copying data
    int* Left = (int*) malloc(sizeof(int)*len_l);
    int* Right = (int*) malloc(sizeof(int)*len_r);

	int i;

    for (i = 0; i < len_l; i++)
        Left[i] = a[beg + i];

    for (i = 0; i < len_r; i++)
        Right[i] = a[mid + 1 + i];
 
    int j;
    int k; // Initial index of merged subarray

    // Merge the temp arrays back into a[beg..end]
    for(i=0, j=0, k=beg; i<len_l && j<len_r; k++)
    {
        if (Left[i] <= Right[j])	//"<" to sort in ascending order
        	a[k] = Left[i++];
        else
            a[k] = Right[j++];
    }
 
    //Copy the remaining elements
    while (i < len_l)
        a[k++] = Left[i++];
 
    while (j < len_r)
    	a[k++] = Right[j++];
}

void MergeSort(int a[], int beg, int end)
{
    if (beg < end)
    {
        int mid = beg+(end-beg)/2;
 
        // Recursively sort first and second halves
        MergeSort(a, beg, mid);
        MergeSort(a, mid+1, end);
 
 		//merge the halves while sorting
        Merge(a, beg, mid, end);
    }
}

//function to print the sorted array irrespective of the algo
void PrintArray(int a[], int n)
{
    int i;
    for (i=0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
	int signal, n;

	scanf("%d %d", &signal, &n);

	int * a = (int*) malloc(sizeof(int)*n);

	int i;
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);

	if(signal)
		QuickSort(a, 0, n-1);
	else
		MergeSort(a, 0, n-1);

	PrintArray(a, n);

	return 0;
}
