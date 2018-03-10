#include "disjoint_set.h"

// function makes set whick stores key "x"
void Make_set(int x)
{
    Set[x][1]=x;    //the parent of x is x itself
    Set[x][0]=0;    //the rank of x is set to be 0
}

// utility funciton which does the union of 2 sets
void Union(int x, int y)
{
    Link(Find_set(x), Find_set(y));
    //arguments to Link will always be leader of sets
}

// function which tells the leader of set containing "x"
int Find_set(int x)
{
    if(x != Set[x][1])									// if x not already the leader
        Set[x][1] = Find_set(Set[x][1]);				// recursive call to Find_Set with argument as "parent of x";

    return Set[x][1];
}

// function which links 2 leaders
void Link(int x, int y)
{
    if(Set[x][0] > Set[y][0])              //element with lower rank will point to element with higher rank 
        Set[y][1] = x;
    else
        Set[x][1] = y;

    if(Set[x][0] == Set[y][0])              //rank is updated in case if both elements have same rank
        Set[y][0]++;
}
  