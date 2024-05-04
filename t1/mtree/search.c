#include <stdio.h>

#include "mtree.h"
#include "utils.c"
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

    new->next = NULL;

    if(list->len > 0){last->next = new;}

    list->last = new;

    list->len++;

}

List_element *list_peek(List* list, int i){

    List_element *le = list->last; 

    while(1){

        if(i == 0){
            
            return le;

        }

        le = le->prev;

        i--;
    }

}




List_element *list_get(List* list, int i){

    List_element *i_element = list_peek(list, i);

    if(list->len > 1 && i_element->prev){

        i_element->prev->next = i_element->next;


    }
    if(list->len > 1 && i_element->next){

        i_element->next->prev = i_element->prev;

    }
    else{

        if(list->len == 0) list->last = i_element->prev;

    }

    list->len--; 
}


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

        int n = root->n;

        for(int i = 0; i < n; i++){

            entry = list_peek(root->entries, i);
            
            if(dist(entry->p, q) <= r){

                list_add(point_list, entry->p);

            }


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

