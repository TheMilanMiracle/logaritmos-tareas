#include <bits/stdc++.h>

#include "graph.h"

void sink(std::vector<std::pair<double, Vertex*>> *A, std::unordered_map<Vertex*, int> *M,  int i){

    if(A->size() == 0){return;}

    int l = 2*i + 1; 
    int r = 2*i + 2; 

    int _max = i;

    // std::cout << "sink: "<< A->size() << " | " << i << " | "<< l << " | "<< r<<std::endl;


    if(l < A->size()-1 && (*A)[l].first < (*A)[i].first){

        _max = l;

    }
    if(r < A->size()-1 && (*A)[r].first < (*A)[_max].first){

        _max = r;

    }
    if(_max != i){

        std::iter_swap(A->begin() + i, A->begin() + _max);

        int aux = (*M)[(*A)[i].second];

        (*M)[(*A)[i].second] = (*M)[(*A)[_max].second];

        (*M)[(*A)[_max].second] = aux;

        sink(A, M, _max);

    }

}

void climb(std::vector<std::pair<double, Vertex*>> *A, std::unordered_map<Vertex*, int> *M, int i){

    int p = (i-1)/2; 

    // std::cout << "climb | "<< A->size()<< " | "<< i << " | " << p<< std::endl;

    if((*A)[p].first < (*A)[i].first){

        std::iter_swap(A->begin() + i, A->begin() + p);

        int aux = (*M)[(*A)[i].second];

        (*M)[(*A)[i].second] = (*M)[(*A)[p].second];

        (*M)[(*A)[p].second] = aux;
        

        climb(A, M, p);

    }

}

std::pair<double, struct vertex*> heap_extract(struct heap *Heap){

    std::iter_swap(Heap->A->begin(), Heap->A->end() - 1);

    int aux = (*Heap->M)[(*Heap->A)[0].second];

    (*Heap->M)[(*Heap->A)[0].second] = (*Heap->M)[(*Heap->A)[Heap->A->size() - 1].second];

    (*Heap->M)[(*Heap->A)[Heap->A->size() - 1].second] = aux;

    std::pair<double, Vertex*> ret = (*Heap->A)[Heap->A->size() - 1];

    Heap->A->erase(Heap->A->end() - 1);

    sink(Heap->A, Heap->M, 0);

    Heap->M->erase(ret.second);

    return ret;

}

struct heap* heapify(std::vector<std::pair<double, Vertex*>> *A){

    Heap* heap = (Heap*) malloc(sizeof(Heap*));

    std::unordered_map<Vertex*, int> *M = new std::unordered_map<Vertex*, int>; 

    for(int i = 0; i < A->size(); i++){

        (*M)[(*A)[i].second] = i;

    }

    heap->M = M;

    for(int i = (A->size() / 2);i >= 0; i--){

        sink(A, M, i);

    }

    heap->A = A;

    return heap;

}

void decreaseKey(struct heap *Heap, struct vertex *v, double d){

    std::unordered_map<Vertex*, int> m = *Heap->M;

    int i = m[v];

    // std::cout << i << ", " << Heap->A->size()<< std::endl;

    (*Heap->A)[i].first = d;

    climb(Heap->A, Heap->M, i);

}