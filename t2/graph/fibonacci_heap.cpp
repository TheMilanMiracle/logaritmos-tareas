#include <bits/stdc++.h>

#include "graph.h"

void printList(FibNode *head){

    FibNode *node = head->right;

    printf("(%lu)->", (((long unsigned int)head<<48)>>48));

    while(node!=head){
        printf("(%lu)->", (((long unsigned int)node<<48)>>48));
        node = node->right;
    }

    printf("\n");

}

void printDegrees(FibNode *A[], int n){

    printf("[");
    for(int i = 0; i < n; i++){
        if(A[i]){printf("%lu, ", A[i]->degree);}
        else{printf("NULL, ");}
    }
    printf("]\n");

}




void addNode(FibNode **head_ptr, FibNode *new_node){

    FibNode *head = *head_ptr;

    if(head == NULL){

        new_node->left = new_node;
        new_node->right = new_node;

        *head_ptr = new_node;

    }
    else{

        new_node->left = head;
        new_node->right = head->right;

        head->right->left = new_node;
        head->right = new_node;

    }

}

void removeNode(FibNode **head_ptr, FibNode *node, long unsigned int nodes){

    FibNode *head = *head_ptr;

    if(nodes == 1){

        head_ptr = NULL;

    }
    else{

        if(head == node){

            *head_ptr = node->right;

        }

        node->left->right = node->right;
        node->right->left = node->left;

    }

    node->right = NULL;
    node->left = NULL;

}


void insert(FibHeap *H, double w, Vertex *v){

    std::pair<double, Vertex*> p = std::make_pair(w, v);

    FibNode *new_node = (FibNode*)malloc(sizeof(FibNode));

    v->ptr = new_node;

    new_node->child = NULL;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->degree = 0;
    new_node->marked = false;
    new_node->value = p;

    addNode(&H->min, new_node);
    H->roots++;

    if(w < H->min->value.first){

        H->min = new_node;

    }

    H->n++;

}

struct fibHeap* fibHeap_heapify(std::vector<std::pair<double, struct vertex*>> *A){
    FibHeap *heap = (FibHeap*)malloc(sizeof(FibHeap));

    heap->min = NULL;
    heap->n = 0;

    for(long unsigned int i = 0; i < A->size(); i++){

        insert(heap, (*A)[i].first, (*A)[i].second);

    }

    return heap;

}


void link(FibHeap *H, FibNode *y, FibNode *x){
    addNode(&(x->child), y);

    x->degree++;

    y->marked = false;

    y->parent = x;

}

void consolidate(FibHeap *H){

    int D = std::log2(H->n) + 1;

    FibNode *A[D];

    for(int i = 0; i < D; i++){

        A[i] = NULL;

    }

    FibNode *w = H->min, *x, *y, *next = w->right;

    for(int i = 0; i < H->roots; i++){
        x = w;
        unsigned long int d = w->degree;

        w->right = NULL;
        w->left = NULL;

        while(A[d] != NULL){

            y = A[d];

            if (x->value.first > y->value.first) {

                std::swap(x, y);

            }

            link(H, y, x);

            A[d] = NULL;
            d++;

        }

        A[d] = x;

        w = next;
        if(w){next = w->right;}

    }

    H->roots = 0;
    H->min = NULL;

    for(int i = 0; i < D; i++){

        if(A[i]){

            addNode(&H->min, A[i]);
            H->roots++;

            if(A[i]->value.first < H->min->value.first){

                H->min = A[i];

            }

        }

    }

}

std::pair<double, struct vertex*> fibHeap_extract(struct fibHeap *H){

    std::pair<double, Vertex*> p = {0, NULL};

    FibNode *z = H->min;

    if(z){

        FibNode *child = z->child, *node = child;

        for(int i = 0; i < z->degree; i++){

            FibNode *next = node->right;

            removeNode(&z->child, node, z->degree);

            addNode(&H->min, node);
            H->roots++;

            node->parent = NULL;

            node = next;

        }

        FibNode *right = z->right;

        removeNode(&H->min, z, H->roots);
        H->roots--;

        if(z == right){

            H->min = NULL;

        }
        else{

            H->min = right;
            consolidate(H);

        }

        p = z->value;

        // free(z);

        H->n--;

    }

    return p;

}


void cut(FibHeap *H, FibNode *x, FibNode *y){

    removeNode(&y->child, x, y->degree);
    y->degree--;

    addNode(&H->min, x);
    H->roots++;

    x->parent = NULL;
    x->marked = false;

}

void cascading_cut(FibHeap *H, FibNode *y){

    FibNode* z = y->parent;

    if(z){

        if(y->marked == false){

            y->marked = true;

        }
        else{

            cut(H, y, z);
            cascading_cut(H, z);

        }

    }

}

void fibHeap_decrease_key(struct fibHeap *H, struct vertex *v, double w){

    FibNode *x = (FibNode*)v->ptr, *y;

    x->value.first = w;

    if(y && w < y->value.first){

        cut(H, x, y);
        cascading_cut(H, y);

    }

    if(w < H->min->value.first){

        H->min = x;

    }

}