#include <math.h>
#include "mtree.c"


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

    list->last = new;

    list->len++;

}