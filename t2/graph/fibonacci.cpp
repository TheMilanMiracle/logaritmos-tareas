#include <bits/stdc++.h>

#include "graph.h"

typedef struct node Node;
typedef struct binomialTree BinomialTree;
typedef struct linkedNode LinkedNode;


struct node{
    std::pair<double, Vertex*> val;
};

Node* newNode(std::pair<double, Vertex*> val){
    Node* n = (Node*) malloc(sizeof(Node*));

    n->val = val;

    return n;
}

struct binomialTree{
    struct node *root;
};

struct linkedNode{
    struct node *next;
};

typedef struct{

    struct linkedNode *list_head, *list_back;
    struct binomialTree *min;

} FibonacciQ;

double find_min(FibonacciQ *F){

    return F->min->root->val.first;

}

void insert(FibonacciQ *F, std::pair<double, Vertex*> p){

    Node *_new = newNode(p);

    F->list_back->next = _new;

    // F->list_back = _new;

}

FibonacciQ *heapify(std::vector<double, Vertex*> *A){

    FibonacciQ *F = (FibonacciQ*) malloc(sizeof(FibonacciQ*));

    insert(F, (*A)[0]);

    for(long unsigned int i = 1; i < A->size(); i++){

        insert(F, (*A)[i]);

    }

}
