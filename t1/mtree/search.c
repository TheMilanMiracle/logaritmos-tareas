#include <stdio.h>

#include "mtree.h"
#include "utils.c"
#include <math.h>


List *point_list;


void init_search(){

    point_list = list_create();

}

void end_search(){

    printf("len = %d\n", point_list->len);

}



void searchTreeRec(MTree* t, Point *q, double r){

    Node *root = t->root; // nodo raiz de este subarbol

    Entry *entry = *(root->entries); // primera entrada de un nodo

    if(entry->a == NULL){

        int n = sizeof(root) / sizeof(Entry);

        Entry **entries = t->root->entries;
        entry = *entries;

        for(int i = 0; i < n; i++){
            
            
            if(dist(entry->p, q) <= r){

                list_add(point_list, entry->p);

            }

            entries += sizeof(Entry);
            entry = *(t->root->entries);

        }

    }

    else{

        int n = sizeof(root) / sizeof(Entry);

        Entry **entries = root->entries;
        entry = *entries;

        for(int i = 0; i < n; i++){
            
            
            if(dist(entry->p, q) <= r + entry->c_r){

                searchTreeRec(newMTree(entry->a, entry), q, r, point);

            }

            entries += sizeof(Entry);
            entry = *entries;

        }

    }
}


void searchTree(MTree* t, Point*q, double r){

    Node *root = t->root;

    if(dist(t->root_entry->p, q) <= r){

        list_add(point_list, t->root_entry->p);

    }

    searchTreeRec(t, q, r);

}

