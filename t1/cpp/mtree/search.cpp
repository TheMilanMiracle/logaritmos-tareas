#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "./mtree.h"


long int simulated_reads;


void searchTreeRec(struct mtree *t, struct point *q, double r, std::vector<struct point*> *points){

    simulated_reads++;

    Node *root = t->entry->a;

    std::cout << t->entry->c_r << std::endl;

    std::cout << t->entry->a->entries << std::endl;

    if((*t->entry->a->entries)[0]->a == NULL){
        std::cout << "if" << std::endl;


        int n = (*root->entries).size();

        for(int i = 0; i < n; i++){

            Point *p = (*root->entries)[i]->p;
            
            if(dist(p, q) <= r){

                points->push_back(p);

            }

        }

    }
    else{
        std::cout << "if" << std::endl;

        int n = (*root->entries).size();

        std::vector<Entry*> entries = (*root->entries);

        for(int i = 0; i < n; i++){
            
            Entry *entry = entries[i];

            if(dist(entry->p, q) <= r + entry->c_r){

                searchTreeRec(newMTree(entry), q, r, points);

            }

        }

    }
}


std::vector<struct point*> *searchTree(struct mtree* t, struct point*q, double r){

    simulated_reads = 0;

    std::cout << t->entry->a->entries->size() << std::endl;

    std::vector<Point*> *points = new std::vector<Point*>;

    searchTreeRec(t, q, r, points);

    return points;

}

long int get_simulated_reads(){

    return simulated_reads;

}
