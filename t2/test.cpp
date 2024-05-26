#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

typedef struct{} Node;

typedef struct{

    int _1;
    void* _2;

} Pair;

void printv(std::vector<Pair*> v){

    std::cout << "[";

    for(int i = 0; i < v.size(); i++){

        std::cout << v[i]->_1 << ", ";

    }

    std::cout << "]\n";

}


Pair *newPair(int f, void* s){

    Pair* pair = (Pair*) malloc(sizeof(Pair));

    pair->_1 = f;
    pair->_2 = s;

    return pair;

}

void heap_decreaseKey(std::vector<Pair*> *A, Node* n, int d){

    //

}

void heapify_aux(std::vector<Pair*> *A, int i, int mult){

    int l = 2*i; 
    int r = 2*i + 1; 

    int _max = i;

    if(l < A->size() && (*A)[l]->_1 * mult < (*A)[i]->_1 * mult){

        _max = l;

    }

    //r <= A->size() && (*A)[r] > (*A)[_max]
    if(r < A->size() && (*A)[r]->_1 * mult < (*A)[_max]->_1 * mult){

        _max = r;

    }

    if(_max != i){

        std::iter_swap(A->begin() + i, A->begin() + _max);

        heapify_aux(A, _max, mult);

    }

}

Pair* heap_get(std::vector<Pair*> *A){

    std::iter_swap(A->begin(), A->end() - 1);

    Pair *ret = (*A)[A->size() - 1];

    A->erase(A->end() - 1);

    heapify_aux(A, 0, 1);

    return ret;

}

void heapify(std::vector<Pair*> *A, int mult){

    for(int i = (A->size() / 2); i >= 0; i--){

        heapify_aux(A, i, mult);

    }

}




int main(){

    Node *n1, *n2, *n3;

    Pair *p1 = newPair(1, n1), *p2 = newPair(2, n2), *p3 = newPair(3, n3);

    std::vector<Pair*> v = {
        p1, p2, newPair(5, NULL),
        newPair(6, NULL), newPair(10, NULL), newPair(9, NULL), 
        newPair(8, NULL), newPair(11, NULL), p3,
        newPair(4, NULL), newPair(5, NULL), newPair(0, NULL),
        newPair(7, NULL), newPair(15, NULL), newPair(14, NULL), 
        newPair(12, NULL)
    };

    printv(v);

    heapify(&v, 1);

    printv(v);

    std::vector<Pair*> s;

    while(v.size())
        s.push_back(heap_get(&v));


    printv(v);
    printv(s);

}