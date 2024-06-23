#include <bits/stdc++.h>

#include "graph.h"

void sink(std::vector<std::pair<double, Vertex*>> *A, int i){ //log(n)

    if(A->size() == 0){return;}

    int l = 2*i + 1; 
    int r = 2*i + 2; 

    int _max = i;

    if(l < A->size()-1 && (*A)[l].first < (*A)[i].first){

        _max = l;

    }
    if(r < A->size()-1 && (*A)[r].first < (*A)[_max].first){

        _max = r;

    }
    if(_max != i){

        std::iter_swap(A->begin() + i, A->begin() + _max);

        int* aux = (int*) (*A)[i].second->ptr;

        (*A)[i].second->ptr = (*A)[_max].second->ptr;

        (*A)[_max].second ->ptr = aux;

        sink(A, _max);

    }

}

void climb(std::vector<std::pair<double, Vertex*>> *A, int i){//log(n)

    int p = (i-1)/2; 

    if((*A)[p].first < (*A)[i].first){

        std::iter_swap(A->begin() + i, A->begin() + p);

        int* aux = (int*)(*A)[i].second->ptr;

        (*A)[i].second->ptr = (*A)[p].second->ptr;

        (*A)[p].second ->ptr = aux;
        
        climb(A, p);

    }

}

std::pair<double, struct vertex*> heap_extract(struct heap *Heap){

    std::iter_swap(Heap->A->begin(), Heap->A->end() - 1);

    int* aux =(int*) (*Heap->A)[0].second->ptr;

    (*Heap->A)[0].second->ptr = (*Heap->A)[Heap->A->size() - 1].second->ptr;

    (*Heap->A)[Heap->A->size() - 1].second->ptr = aux;

    std::pair<double, Vertex*> ret = (*Heap->A)[Heap->A->size() - 1];

    Heap->size--;

    sink(Heap->A, 0);

    return ret;

}

struct heap* heapify(std::vector<std::pair<double, Vertex*>> *A){

    Heap* heap = (Heap*) malloc(sizeof(Heap*));

    heap->size = A->size();

    for(int i = 0; i < A->size(); i++){

        int *idx = (int*) malloc(sizeof(int*));
        *idx = i;
        (*A)[i].second->ptr = idx;

    }

    for(int i = (A->size() / 2);i >= 0; i--){

        sink(A, i);

    }

    heap->A = A;

    return heap;

}

void decreaseKey(struct heap *Heap, struct vertex *v, double d){

    int *idx = (int*)v->ptr;

    (*Heap->A)[*idx].first = d;

    climb(Heap->A, *idx);

}