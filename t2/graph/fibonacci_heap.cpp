#include <bits/stdc++.h>

#include "graph.h"

FibNode *newNode(double w, Vertex *v){
    FibNode *node = (FibNode*) malloc(sizeof(FibNode));

    node->w = w;
    node->v = v;

    node->left = node;
    node->right = node;
    node->parent = NULL;
    node->child = NULL;

    node->degree = 0;
    node->marked = false;

    return node;
}

void addNode(FibNode **ptr, FibNode *node){
    if(*ptr == NULL){
        *ptr = node;
    }
    else{
        node->left = *ptr;
        node->right = (*ptr)->right;

        (*ptr)->right->left = node;
        (*ptr)->right = node;

        if(node->w < node->w){
            *ptr = node;
        }
    }
}

void removeNode(FibNode **ptr, FibNode *node){
    node->left->right = node->right;
    node->right->left = node->left;

    if(*ptr == node){
        *ptr = node->right;
    }
}


void insert(FibHeap* H, double w, Vertex* v){
    FibNode *new_node = newNode(w, v);
    v->ptr = new_node;

    addNode(&H->min, new_node);
    H->n++;
}

struct fibHeap *fibHeap_heapify(std::vector<std::pair<double, struct vertex*>> *A){
    FibHeap *heap = (FibHeap*) malloc(sizeof(FibHeap));

    heap->min = NULL;
    heap->n = 0;

    for(long unsigned int i = 0; i < A->size(); i++){
        insert(heap, (*A)[i].first, (*A)[i].second);
    }

    return heap;
}


void link(FibHeap *H, FibNode *y, FibNode *x){
    removeNode(&H->min, y);  
    y->left = y;
    y->right = y;    
    if(x->child == NULL){
        x->child = y;
    }
    else{
        y->right = x->child;
        y->left = x->child->left;

        x->child->left->right = y;
        x->child->left = y;
    }
    
    y->parent = x;
    x->degree++;
    y->marked = false;
}

void consolidate(FibHeap *H){
    int D = std::log2(H->n) + 2;
    FibNode *A[D];

    std::vector<FibNode*> Nodes;

    for(int i = 0; i < D; i++){
        A[i] = NULL;
    }

    Nodes.push_back(H->min);
    FibNode *w = H->min->right;
    int aux = 0;
    while(w != Nodes[0]){
        for (int r = Nodes.size()-1; r >= 0; r--){
            if (w == Nodes[r]){
                aux = 1;
                break;
            }
        }
        if (aux){
            break;            
        }

        Nodes.push_back(w);    
        w = w->right;
    }

    for(int i = 0; i < Nodes.size(); i++){
        FibNode *x = Nodes[i];
        long unsigned int d = x->degree;

        while(A[d] != NULL){
            FibNode *y = A[d];

            if(x->w > y->w){
                std::swap(x, y);
            }
            
            link(H, y, x);
            

            A[d] = NULL;
            d++;
        }

        A[d] = x;
    }
    
    H->min = NULL;
    for(int i = 0; i < D; i++){
        if(A[i] != NULL){
            if(H->min == NULL){
                A[i]->left = A[i];
                A[i]->right = A[i];
            }

            addNode(&H->min, A[i]);
        }
    }
}

std::pair<double, struct vertex*> fibHeap_extract(struct fibHeap *H){
    if(H->min != NULL){
        
        FibNode *z = H->min;
        
        if(z->child != NULL){
            
            std::vector<FibNode*> Childs;
            Childs.push_back(z->child);
            FibNode *c = z->child->right;
            int aux = 0;
            while(c != Childs[0]){
                for (int r = Childs.size()-1; r >= 0; r--){
                    if (c == Childs[r]){
                        aux = 1;
                        break;
                    }
                }
                if (aux){
                    break;            
                }
                Childs.push_back(c);
                c = c->right;
            }
            for(unsigned long int i = 0; i < Childs.size(); i++){
                Childs[i]->parent = NULL;
                addNode(&H->min, Childs[i]);
            }
            
        }
        
        removeNode(&H->min, z);
        
        if(H->n == 1){
            H->min = NULL;
        } 
        else{
            H->min = z->right;
            
            consolidate(H);   
                
        }
          
        H->n--;
        std::pair<double, Vertex*> r = {z->w, z->v};
        
        return r;
        
    }
    else{
        return {DBL_MAX, NULL};
    }
    
}


void cut(FibHeap *H, FibNode *x, FibNode *y){
    if(x == x->right){
        y->child = NULL;
    }
    else{
        x->right->left = x->left;
        x->left->right = x->right;

        if(y->child == x){
            y->child = x->right;
        }
    }
    y->degree--;

    addNode(&H->min, x);
    x->parent = NULL;
    x->marked = false;
}

void cascading_cut(FibHeap *H, FibNode *y){
    FibNode *z = y->parent;

    if(z != NULL){
        if(!y->marked){
            y->marked = true;
        }
        else{
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}

void fibHeap_decrease_key(struct fibHeap *H, struct vertex* v, double w){
    FibNode *x = (FibNode*) v->ptr;

    if(x->w < w){return;}

    x->w = w;

    FibNode* y = x->parent;

    if(y && x->w < y->w){
        cut(H, x, y);
        cascading_cut(H, y);
    }

    if(x->w < H->min->w){
        H->min = x;
    }

}