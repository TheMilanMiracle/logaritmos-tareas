#include <stdlib.h>
#include <stdio.h>
#include "mtree.h"
#include <math.h>

List *list_create(){
    List *list = malloc(sizeof(List));

    return list;
}

void list_add(List* list, void* element){

    List_element *last = list->last;

    List_element *new = malloc(sizeof(List_element));

    new->element = element;
    new->prev = last;

    list->last = new;

    list->len++;

}

double dist(Point *p1, Point *p2){
    
    return sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));

}

MTree *newMTree(Node *root, Entry *root_entry){
    MTree *new = malloc(sizeof(MTree));

    new->root = root;
    new->root_entry = root_entry;

    return new;
}

void freeMTree(MTree *mtree){

    free(mtree);

}


Node *newNode(Entry **entries, int n){
    Node *new = malloc(sizeof(Node));

    new->entries = entries;
    new->n = n;

    return new;
}

void freeNode(Node *node){

    free(node);

}


Entry *newEntry(Point *point, double c_r, Node *a){
    Entry *new = malloc(sizeof(Entry));

    new->p = point;
    new->c_r = c_r;
    new->a = a;

    return new;
}

void freeEntry(Entry *entry){

    free(entry);

}


Point *newPoint(double x, double y){
    Point *new = malloc(sizeof(Point));

    new->x = x;
    new->y = y;

    return new;
}

void freePoint(Point *point){

    free(point);

}

void init_search(){

    //point_list = list_create();

}

void end_search(){

    //printf("len = %d\n", point_list->len);

}



void searchTreeRec(MTree* t, Point *q, double r, List *points){
    printf("rec | %f\n", t->root_entry->c_r);

    Node *root = t->root; // nodo raiz de este subarbol

    printf("post Node\n");

    Entry *entry = t->root->entries[0];

    if(entry->a == NULL){
        printf("NULL\n");

        int n = root->n;

        for(int i = 0; i < n; i++){// O(n)

            entry = root->entries[i];// O(1)

            printf("dist = %f | r = %f \n", dist(entry->p, q), r);
            
            if(dist(entry->p, q) <= r){

                list_add(points, entry->p);

            }


        }

    }

    else{
        printf("else\n");


        int n = root->n;

        printf("%d\n", n);

        Entry **entries = root->entries;

        for(int i = 0; i < n; i++){// O(n)
            printf("for\n");
            
            entry = entries[i];// O(1)
            if(dist(entry->p, q) <= r + entry->c_r){
                printf("if\n");

                searchTreeRec(newMTree(entry->a, entry), q, r, points);

            }

        }

    }
}


List *searchTree(MTree* t, Point*q, double r){

    List *points = list_create();

    Node *root = t->root;

    // if(dist(t->root_entry->p, q) <= r){

    //     list_add(points, t->root_entry->p);

    //     printf("add\n");

    // }
    
    searchTreeRec(t, q, r, points);


    return points;

}



