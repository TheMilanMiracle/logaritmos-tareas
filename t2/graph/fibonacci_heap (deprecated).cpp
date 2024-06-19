// #include <bits/stdc++.h>

// void add_to(FibNode* l, FibNode* x){

//     if(l == NULL){

//         l = x;
//         x->left = x;
//         x->right = x;

//     }
//     else{

//         FibNode* r = l->right;
//         l->right = x;
//         r->left = x;

//         x->left = l;
//         x->right = r;

//     }

// }

// void remove_from(FibNode* l, FibNode* x){

//     if(l->left == l && l->right == l){

//         l = NULL;

//     }
//     else{

//         if(x->left && x->right){
//             x->left->right = x->right;
//             x->right->left = x->left;
//         }

//     }

//     x->left = NULL;
//     x->right = NULL;

// }


// void insert(FibHeap *H, double w, Vertex *v){

//     std::pair<double, Vertex*> p = std::make_pair(w, v);

//     FibNode *node = (FibNode*) malloc(sizeof(FibNode));

//     v->ptr = node;

//     node->value = p;
//     node->parent = NULL;
//     node->child = NULL;
//     node->marked = false;
//     node->degree = 0;

//     H->roots_amount++;

//     if(H->n == 0){

//         H->roots = node;
//         H->min = node;

//         node->left = node;
//         node->right = node;

//     }
//     else{

//         if(node->value.first < H->min->value.first){

//             H->min = node;

//         }

//         add_to(H->roots, node);

//         H->roots = node;

//     }

//     H->n++;

// } 

// struct fibHeap* fibHeap_heapify(std::vector<std::pair<double, struct vertex*>> *A){

//     FibHeap* heap = (FibHeap*) malloc(sizeof(FibHeap));

//     heap->min = NULL;
//     heap->roots = NULL;
//     heap->n = 0;
//     heap->roots_amount = 0;

//     for(long unsigned int i = 0; i < A->size(); i++){

//         insert(heap, (*A)[i].first, (*A)[i].second);

//     }

//     return heap;

// }


// void link(FibHeap *H, FibNode *y, FibNode *x){

//     remove_from(H->roots, y);
    
//     add_to(x->child, y);

//     x->degree++;

//     y->marked = false;

// }

// void consolidate(FibHeap *H){


//     std::vector<FibNode*> A, nodes(H->roots_amount-1);
    
//     FibNode *node = H->roots->right;

//     for(long unsigned int i = 0; i < H->roots_amount-1; i++){

//         FibNode *next;

//         next = node->right;
//         nodes[i] = node;

//         printf("%ld | %lu\n", (long int)nodes[i], i);

//         node = next;

//     }


//     for(long unsigned int i = 0; i < H->roots_amount; i++){

//         // FibNode* new_node = (FibNode*) malloc(sizeof(FibNode));

//         // new_node->value = node->value;
//         // new_node->child = node->child;
//         // new_node->degree = node->degree;
//         // new_node->left = NULL;
//         // new_node->right = NULL;
//         // new_node->marked = node->marked;
//         // new_node->parent = NULL;

//         // FibNode* x = new_node;

//         FibNode* x = nodes[i];

//         x->left = NULL;
//         x->right = NULL;
//         x->parent = NULL;

//         int d = x->degree;

//         if(A.size() < d+1){A.resize(d+1, NULL);}

//         while(A[d] != NULL){

//             FibNode* y = A[d];

//             if(x->value.first > y->value.first){

//                 FibNode* aux = x;
//                 x = y;
//                 y = aux;

//             }
            
//             link(H, y, x);
            
//             A[d] = NULL;

//             d++;

//             if(A.size() < d+1){A.resize(d+1, NULL);}

//         }

//         A[d] = x;

//     }

//     H->roots_amount = A.size();

//     H->min = NULL;

//     for(int i = 0; i < A.size(); i++){

//         if(A[i] != NULL){

//             if(H->min == NULL){

//                 H->roots = A[i];
//                 H->min = A[i];

//                 A[i]->right = A[i];
//                 A[i]->left = A[i];

//             }
//             else{

//                 add_to(H->roots, A[i]);

//                 H->roots = A[i];

//                 if(A[i]->value.first < H->min->value.first){

//                     H->min = A[i];

//                 }

//             }

//         }

//     }

// }



// std::pair<double, struct vertex*> fibHeap_extract(struct fibHeap *H){

//     FibNode *min_node = H->min;

//     if(min_node != NULL){

//         std::pair<double, Vertex*> min = min_node->value;

//         FibNode *first = min_node->child, *child = first;

//         if(first){// se agregan los hijos a la lista de raices

//             do{

//                 add_to(H->roots, child);

//                 child->parent = NULL;

//                 child = child->right;

//             }while(child != first);

//         }

//         // se elimina el nodo del minimo del fibHeap
//         FibNode* r = min_node->right;
//         remove_from(H->roots, min_node);

//         if(min_node == min_node->right){// si era el ultimo nodo en el fibHeap

//             H->roots = NULL;

//         }
//         else{

//             H->min = r;

//             consolidate(H);
//         }

//         H->n--;

//         free(min_node);

//         return min;

//     }
//     else{

        
//         std::pair<double, Vertex*> *p = new std::pair<double, Vertex*>;
//         return *p;

//     }

// }


// void cut(FibHeap *H, FibNode *x, FibNode *y){

//     remove_from(y->child, x);

//     y->degree--;

//     add_to(H->roots, x);

//     x->parent = NULL;

//     x->marked = false;

// }

// void cascading_cut(FibHeap *H, FibNode *y){

//     FibNode *z = y->parent;

//     if(z != NULL){

//         if(y->marked == false){

//             y->marked = true;

//         }
//         else{

//             cut(H, y, z);
//             cascading_cut(H, z);

//         }

//     }
// }

// void fibHeap_decrease_key(struct fibHeap *H, struct vertex* v, double w){
//     // FibNode *x = (*H->M)[v];
//     FibNode *x = (FibNode*) v->ptr;

//     x->value.first = w;

//     FibNode *y = x->parent;

//     if(y != NULL && x->value.first < y->value.first){

//         cut(H, x, y);
//         cascading_cut(H, y);

//     }

//     if(x->value.first < H->min->value.first){

//         H->min = x;

//     }

// }


