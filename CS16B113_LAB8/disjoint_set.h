#include <stdio.h>
#include <stdlib.h>

int Set[400000][2];        
// non-negative value in Set[x][1] means that x exists in some set
// Set[x][1] is the value of the element to which "x" points in the set
// Set[x][0] is the rank of "x" in the set

// function makes set whick stores key "x"
void Make_set(int x);

// utility funciton which does the union of 2 sets
void Union(int x, int y);

// function which tells the leader of set containing "x"
int Find_set(int x);

// function which links 2 leaders
void Link(int x, int y);