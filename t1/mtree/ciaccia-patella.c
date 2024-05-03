#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "mtree.h"

#define B 4096
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

List_element *list_remove(List* list, int n){

    List_element *le = list->last; 

    while(1){

        if(n == 0){
            if(list->len > 1 && le->prev){

                le->prev->next = le->next;



            }
            if(list->len > 1 && le->next){

                le->next->prev = le->prev;

            }
            else{

                if(list->len > 1)list->last = le->prev;

            }

            list->len--;
            return le;

        }

        le = le->prev;

        n = n-1;
    }

}


MTree *ciaccia_patella(List *set){

    List *copy = set;


    if(set->len <= B){return;}

    int k = min(B, set->len/B), temp = k;

    Point F[k];
    List *sample_sets[k];

    while(temp--){

        F[temp-k] = *(list_remove(set, rand() % set->len)->element);

    }

    while(set->len){

        Point *current = list_remove(set, 0)->element;

        int closer = 0;

        double min = dist(closer, current);

        for(int i = 1; i < k; i++){
            
            double d = dist(&F[i], current);

            if(d < min){

                closer = i;
                min = d;

            }

        }

        list_add(sample_sets[closer], current);

    }

    int len = k;

    for(int i = 0; i < k; i++){

        if(sample_sets[i]->len < b){

            len--;

            while(sample_sets[i]->len){

                Point *current = list_remove(sample_sets[i], 0);

                int closer = 0;

                double min = dist(closer, current);

                for(int j = 1; j < k; j++){
            
                    double d = dist(&F[j], current);

                    if(i != j && sample_sets[j]->len > 0 && d < min){

                        closer = j;
                        min = d;

                    }
                }

                list_add(sample_sets[closer], current);
            }

            Point *sample = &F[i];

            int closer = 0 ? i!=0 : 1;

            double min = DBL_MAX;

            for(int j = 0; j < k; j++){
            
                double d = dist(&F[j], sample);

                if(i != j && sample_sets[j]->len > 0 && d < min){

                    closer = j;
                    min = d;

                }
            }

            list_add(sample_sets[closer], sample);

        }

    }

    if(len == 1){

        for(int i = 0; i < k; i++){

            if(sample_sets[i]->len != 0){

                list_add(sample_sets[i], &F[i]);
                return ciaccia_patella(&sample_sets[i]);

            }

        }

    }
    else{

        List *forest = list_create();
        List *new_samples = list_create();

        for(int i = 0; i < k; i++){

            if(sample_sets[i]->len != 0){


                MTree *tree = ciaccia_patella(sample_sets[i]);

                if(tree->root->n < b){

                    for(int j = 0; j < tree->root->n; j++){

                        list_add(forest, )

                    }

                }

            }

        }





    }

}




