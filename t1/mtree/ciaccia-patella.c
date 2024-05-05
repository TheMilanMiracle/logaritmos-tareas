#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "mtree.h"

#define B 4096 / sizeof(Entry) // B = 4096 / sizeof(Entry) = 512
#define b B/2

double dist(Point *p1, Point *p2){
    
    return sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));

}

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

    return i_element;
}

typedef struct tuple{
    void *_1, *_2;
} Tuple;

Tuple *tuple(void* f, void *s){
    Tuple *new = malloc(sizeof(Tuple));

    new->_1 = f;
    new->_2 = s;

    return new;
}


MTree *ciaccia_patella(List *set){
    List *F = list_create();

    if(set->len <= B){return;}//paso 1

    while(1){
        int k = min(B, set->len/B), temp = k;

        List *sample_sets[k];

        while(temp--){// paso 2, se extran k puntos aleatorios de S

            list_add(F, tuple(list_get(set, rand() % set->len)->element, list_create()));

        }

        while(set->len){// paso 3, para los n-k puntos restantes se les busca su sample más cercano

            Point *current = list_get(set, 0)->element;

            int closer = 0;

            double min = dist(closer, current);

            for(int i = 1; i < k; i++){// se busca el sample más cercano 
                
                double d = dist(list_peek(F, i)->element, current);

                if(d < min){

                    closer = i;
                    min = d;

                }

            }

            list_add();

        }


        for(int i = 0; i < k; i++){

            if(sample_sets[i]->len < b){

                while(sample_sets[i]->len){

                    Point *current = list_get(sample_sets[i], 0);

                    int closer = 0;

                    double min = dist(closer, current);

                    for(int j = 1; j < k; j++){
                
                        double d = dist(list_peek(F, i)->element, current);

                        if(i != j && sample_sets[j]->len > 0 && d < min){

                            closer = j;
                            min = d;

                        }
                    }

                    list_add(sample_sets[closer], current);
                }

                Point *sample = list_peek(F, i)->element;

                int closer = 0 ? i!=0 : 1;

                double min = DBL_MAX;

                for(int j = 0; j < k; j++){
                
                    double d = dist(list_peek(F, i)->element, sample);

                    if(i != j && sample_sets[j]->len > 0 && d < min){

                        closer = j;
                        min = d;

                    }
                }

                list_add(sample_sets[closer], sample);

            }

        }

        if(F->len == 1){

            list_add(set, list_get(F, 0));

        }
        else{break;}
    }

    List *forest = list_create();
    List *new_samples = list_create();

    for(int i = 0; i < F->len; i++){

        if(sample_sets[i]->len != 0){


            MTree *tree = ciaccia_patella(sample_sets[i]);

            if(tree->root->n < b){

                for(int j = 0; j < tree->root->n; j++){

                    // list_add(forest, )

                }

            }

        }
    }


        // List forest = {... arboles ...};

        // ENTRY *entries[n] = malloc(sizeof(ENTRY)*n)

        // for(i in range(n)) entries[n] = list_peek(forest, i)

        // NODE->entries = entries





    }

}




