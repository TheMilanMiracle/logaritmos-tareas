#include <bits/stdc++.h>

#include "graph.h"

void add_to(FibNode* l, FibNode* x){

    l->left->right = x;
    x->left = l->left;

    l->right->left = x;
    x->right = l->right;

}

void remove_from(FibNode* l, FibNode* x){

    l->left->right = x->right;
    l->right->left = x->left;

}


void insert(FibHeap *H, double w, Vertex *v){

    std::pair<double, Vertex*> *p = new std::pair<double, Vertex*>;

    p->first = w;
    p->second = v;

    FibNode *node = (FibNode*) malloc(sizeof(FibNode *));

    (*H->M)[v] = node;

    node->value = *p;
    node->parent = NULL;
    node->child = NULL;
    node->marked = false;
    node->degree = 0;

    if(H->min == NULL){

        H->roots = node;
        H->min = node;

        node->left = node;
        node->right = node;

    }
    else{

        if(node->value.first < H->min->value.first){

            H->min = node;

        }

        add_to(H->roots, node);

        H->roots = node;

    }

    H->n++;

} 

struct fibHeap* fibHeap_heapify(std::vector<std::pair<double, struct vertex*>> *A){

    FibHeap* heap = (FibHeap*) malloc(sizeof(FibHeap*));

    heap->n = 0;

    std::unordered_map<Vertex*, long unsigned int> *M = new std::unordered_map<Vertex*, long unsigned int>; 

    for(long unsigned int i = 0; i < 0; i){

        insert(heap, (*A)[i].first, (*A)[i].second);

    }

    return heap;

}


void link(FibHeap *H, FibNode *y, FibNode *x){

    remove_from(H->roots, y);
    
    add_to(x->child, y);

    x->degree++;

    y->marked = false;

}

void consolidate(FibHeap *H){

    std::vector<FibNode*> A;
    
    FibNode *first = H->roots, *node = first;

    do{

        FibNode* x = node;
        int d = x->degree;

        A.resize(d, NULL);

        while(A[d] != NULL){

            FibNode* y = A[d];

            if(x->value.first > y->value.first){

                FibNode* aux = x;
                x = y;
                y = aux;

            }
            
            link(H, y, x);
            
            A[d] = NULL;

            d++;

        }

        A[d] = x;

        node = node->right;

    }while(first != node);

    H->min = NULL;

    for(long unsigned int i = 0; i < A.size(); i++){

        if(A[i] != NULL){

            if(H->min == NULL){

                H->roots = A[i];
                H->min = A[i];

                A[i]->right = A[i];
                A[i]->left = A[i];

            }
            else{

                add_to(H->roots, A[i]);

                H->roots = A[i];

                if(A[i]->value.first < H->min->value.first){

                    H->min = A[i];

                }

            }

        }

    }

}

std::pair<double, struct vertex*> fibHeap_extract(struct fibHeap *H){

    FibNode *min_node = H->min;

    if(min_node != NULL){

        std::pair<double, Vertex*> min = min_node->value;

        FibNode *first = min_node->child, *child = first;

        if(first){// se agregan los hijos a la lista de raices

            do{

                add_to(H->roots, child);

                child->parent = NULL;

                child = child->right;

            }while(child != first);

        }

        // se elimina el nodo del minimo del fibHeap
        remove_from(H->roots, min_node);

        if(min_node == min_node->right){// si era el ultimo nodo en el fibHeap

            H->roots = NULL;

        }
        else{

            H->min = min_node->right;
            consolidate(H);
        }

        H->n--;

        return min;

    }
    else{

        std::cout << "else" << std::endl;
        
        std::pair<double, Vertex*> *p = new std::pair<double, Vertex*>;
        return *p;

    }

}


void cut(FibHeap *H, FibNode *x, FibNode *y){

    remove_from(y->child, x);

    y->degree--;

}

void cascading_cut(FibHeap *H, FibNode *y){

    FibNode *z = y->parent;

    if(z != NULL){

        if(y->marked == false){

            y->marked = true;

        }
        else{

            cut(H, y, z);
            cascading_cut(H, z);

        }

    }
}

void fibHeap_decrease_key(struct fibHeap *H, struct vertex* v, double w){

    FibNode *x = (*H->M)[v];

    x->value.first = w;

    FibNode *y = x->parent;

    if(y != NULL && x->value.first < x->value.first){

        cut(H, x, y);
        cascading_cut(H, y);

    }

    if(x->value.first < H->min->value.first){

        H->min = x;

    }

}



