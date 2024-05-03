#include <stdio.h>

#include "mtree.h"
#include "utils.c"


List *point_list;

void searchTreeRec(MTree* t, Point *q, double r){

    Node *root = t->root; // nodo raiz de este subarbol

    Entry *entry = root->entries; // primera entrada de un nodo

    if(entry->a == NULL){

        int n = sizeof(root) / sizeof(Entry);

        Entry *entries = t->root;

        for(int i = 0; i < n; i++){
            
            
            if(dist(&entries->p, q) <= r){

                list_add(point_list, &entries->p);

            }

            entries += sizeof(Entry);

        }

    }

    else{

        int n = sizeof(root) / sizeof(Entry);

        Entry *entries = root;

        for(int i = 0; i < n; i++){
            
            
            if(dist(&entries->p, q) <= r + entries->c_r){

                search((MTree*){entries->a}, q, r);

            }

            entries += sizeof(Entry);

        }

    }
}


void searchTree(MTree* t, Point *q, double r){

    Entry *root = t->root;

    if(dist(root->p, q) <= r){

        list_add(point_list, root->p);

    }

    searchTreeRec(newMTree(t), q, r);

}

