#include <bits/stdc++.h>

#include "graph.h"

typedef struct{
    std::vector<double, Vertex*> *A;
    std::map<Vertex*, long unsigned int> *M;
} Heap;


double heap_extract(Heap *Heap){

    std::iter_swap(Heap->A->begin(), Heap->A->end() - 1);

    std::pair<double, Vertex*> ret = (*Heap->A)[Heap->A->size() - 1];

    Heap->A->erase(Heap->A->end() - 1);

    heapify_aux(Heap->A, 0);

    Heap->M->erase(ret.second);

    return ret.first;

}

void sink(std::vector<double, Vertex*> *A, int i){

    int l = 2*i; 
    int r = 2*i + 1; 

    int _max = i;

    if(l < A->size() && (*A)[l].first < (*A)[i].first){

        _max = l;

    }
    if(r < A->size() && (*A)[r].first < (*A)[_max].first){

        _max = r;

    }
    if(_max != i){

        std::iter_swap(A->begin() + i, A->begin() + _max);

        sink(A, _max);

    }

}

void climb(std::vector<double, Vertex*> *A, int i){

    int p = (i-1)/2; 

    int _max = i;

    if(l < A->size() && (*A)[p].first < (*A)[i].first){



    }

}

Heap* heapify(std::vector<double, Vertex*> *A){

    Heap* heap = (Heap*) malloc(sizeof(Heap*));

    for(int i = (A->size() / 2); i >= 0; i--){

        heapify_aux(A, i);

    }

    heap->A = A;

    for(int i = 0; i < A->size(); i++){

        heap->M[(*A)[i].second] = i;

    }

    return heap;

}

void decreaseKey(Heap *Heap, Vertex *v, double d){

    std::map<Vertex*, long unsigned int> m = *Heap->M;

    long unsigned int i = m[v];

    (*Heap->A)[i].first -= d;

    heapify_aux(Heap->A, i);

}