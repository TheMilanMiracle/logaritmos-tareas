#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "./mtree.h"

void searchTreeRec(struct mtree *t, struct point *q, double r, std::vector<struct point*> *points){

    Node *root = t->root;

    if(t->root->entries[0]->a == NULL){

        int n = root->entries.size();

        for(int i = 0; i < n; i++){

            Point *p = root->entries[i]->p;
            
            if(dist(p, q) <= r){

                points->push_back(p);

            }

        }

    }

    else{

        int n = root->entries.size();

        std::vector<Entry*> entries = root->entries;

        for(int i = 0; i < n; i++){
            
            Entry *entry = entries[i];

            if(dist(entry->p, q) <= r + entry->c_r){

                searchTreeRec(newMTree(entry->a, -1), q, r, points);

            }

        }

    }
}


std::vector<struct point*> searchTree(struct mtree* t, struct point*q, double r){

    std::vector<Point*> points;

    Node *root = t->root;
    
    searchTreeRec(t, q, r, &points);

    return points;

}
