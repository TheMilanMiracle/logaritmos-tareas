#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <float.h>
#include <cstdint>

#include "./mtree.h"


struct mtree *newMTree(struct entry *entry){
    struct mtree *new_tree = (struct mtree*) std::malloc(sizeof(struct mtree));

    new_tree->entry = entry;

    return new_tree;
}

struct point *newPoint(double x, double y){
    struct point *new_point = (struct point*) std::malloc(sizeof(struct point));

    new_point->x = x;
    new_point->y = y;

    return new_point;
}

struct entry *newEntry(struct point *point, double c_r, struct node *a){
    struct entry *new_entry = (struct entry*) std::malloc(sizeof(struct entry));

    new_entry->p = point;
    new_entry->c_r = c_r;
    new_entry->a = a;

    return new_entry;
}

struct node *newNode(std::vector<struct entry*> *entries){
    struct node *new_node = (struct node*) std::malloc(sizeof(struct node));

    new_node->entries = entries;

    return new_node;
}

double dist(struct point *p1, struct point *p2){
    
    return std::sqrt(std::pow(p1->x - p2->x, 2.0) + std::pow(p1->y - p2->y, 2.0));

}

int get_heigthRec(MTree* t, int n){

    if((*t->entry->a->entries)[0]->a == NULL){

        return 1;

    }
    else{

        int h = INT16_MIN;

        for(unsigned long int i = 0; i < t->entry->a->entries->size(); i++){

            int h_ = get_heigthRec(newMTree((*t->entry->a->entries)[i]), n) + 1;

            if(h_ > h){

                h = h_;

            }

        }

        return h;

    }

}

int get_heigth(struct mtree *t){

    return get_heigthRec(t, 0);

}

struct point *medoid(std::vector<struct point*> cluster){
    int med;
    
    if(cluster.size() == 1){

        return cluster[0];

    }
    else{

        double min = DBL_MAX, sum;

        for(long unsigned int i = 0; i < cluster.size(); i++){

            sum = 0;

            for(long unsigned int j = 0; j < cluster.size(); j++){

                if(i != j){

                    sum += dist(cluster[i], cluster[j]);

                }

                if(sum > min){break;}

            }

            if(sum < min){

                med = i;

            }

        }

        return cluster[med];

    }

}
