#include <bits/stdc++.h>

#include "graph.h"

std::pair<double, struct vertex*> heap_extract(struct heap *Heap){

    std::iter_swap(Heap->A->begin(), Heap->A->end() - 1);

    std::pair<double, Vertex*> ret = (*Heap->A)[Heap->A->size() - 1];

    Heap->A->erase(Heap->A->end() - 1);

    sink(Heap->A, 0);

    Heap->M->erase(ret.second);

    return ret;

}

void sink(std::vector<std::pair<double, Vertex*>> *A, int i){

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

void climb(std::vector<std::pair<double, Vertex*>> *A, int i){

    int p = (i-1)/2; 

    if((*A)[p].first < (*A)[i].first){

        std::iter_swap(A->begin() + i, A->begin() + p);

        climb(A, p);

    }

}

struct heap* heapify(std::vector<std::pair<double, Vertex*>> *A){

    Heap* heap = (Heap*) malloc(sizeof(Heap*));

    for(int i = (A->size() / 2); i >= 0; i--){

        sink(A, i);

    }

    heap->A = A;

    std::map<Vertex*, long unsigned int> map = (*heap->M); 

    for(long unsigned int i = 0; i < A->size(); i++){

        map[(*A)[i].second] = i;

    }

    return heap;

}

void decreaseKey(struct heap *Heap, struct vertex *v, double d){

    std::map<Vertex*, long unsigned int> m = *Heap->M;

    long unsigned int i = m[v];

    (*Heap->A)[i].first = d;

    climb(Heap->A, i);

}