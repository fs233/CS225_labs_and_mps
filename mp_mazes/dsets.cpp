/* Your code here! */
#include "dsets.h"
#include <iostream>
#include <vector>
using namespace std;

void DisjointSets::addelements(int num){
    for(int i = 0; i<num; i++){
        up_tree.push_back(-1);
    }
}	

int DisjointSets::find(int elem){//finding the index of the root of the tree
    if(up_tree[elem]<0){
        return elem;
    }else{
        int root = find(up_tree[elem]);
        up_tree[elem]=root;
        return root;
    }
}	


void DisjointSets::setunion	(int a, int b){
    if(find(a)==find(b)){
        return;
    }
    int roota = up_tree[find(a)];//size of set a
    int rootb = up_tree[find(b)];//size of set b
    int newSize = roota+rootb;
    if(roota > rootb){//a is samller than b
        up_tree[find(a)] = find(b);
        up_tree[find(b)] = newSize;
    }else{
        up_tree[find(b)] = find(a);
        up_tree[find(a)] = newSize;
    }
}		


int DisjointSets::size	(int elem){
    int index = find(elem);
    return -up_tree[index];
}	



