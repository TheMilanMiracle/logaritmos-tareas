#include <bits/stdc++.h>

#include "graph.h"

void sink(std::vector<std::pair<double, Vertex*>> *A, int i){

    int l = 2*i; 
    int r = 2*i + 1; 

    int _max = i;

    std::cout << A->size()<< " | " << l<< " | "<< r << std::endl;

    std::cout << A->size() << std::endl;
    std::cout << (*A)[l].first << std::endl;
    std::cout << (*A)[i].first << std::endl;

    if(l < A->size()-1 && (*A)[l].first < (*A)[i].first){

        _max = l;

    }
    if(r < A->size()-1 && (*A)[r].first < (*A)[_max].first){

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

std::pair<double, struct vertex*> heap_extract(struct heap *Heap){

    std::iter_swap(Heap->A->begin(), Heap->A->end() - 1);

    std::pair<double, Vertex*> ret = (*Heap->A)[Heap->A->size() - 1];

    Heap->A->erase(Heap->A->end() - 1);

    sink(Heap->A, 0);

    Heap->M->erase(ret.second);

    return ret;

}

struct heap* heapify(std::vector<std::pair<double, Vertex*>> *A){

    Heap* heap = (Heap*) malloc(sizeof(Heap*));

    for(long unsigned int i = (A->size() / 2)-1; i >= 0; i--){

        sink(A, i);

    }

    heap->A = A;

    std::unordered_map<Vertex*, long unsigned int> *M = new std::unordered_map<Vertex*, long unsigned int>; 

    for(long unsigned int i = 0; i < A->size(); i++){

        (*M)[(*A)[i].second] = i;

    }

    heap->M = M;

    return heap;

}

void decreaseKey(struct heap *Heap, struct vertex *v, double d){

    std::unordered_map<Vertex*, long unsigned int> m = *Heap->M;

    long unsigned int i = m[v];

    (*Heap->A)[i].first = d;

    climb(Heap->A, i);

}