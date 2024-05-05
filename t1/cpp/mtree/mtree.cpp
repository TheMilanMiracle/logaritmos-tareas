#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "./mtree.h"

struct mtree *newMTree(struct node *root, int h){
    struct mtree *new_tree = (struct mtree*) std::malloc(sizeof(struct mtree));

    new_tree->root = root;
    new_tree->h = h;

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

struct node *newNode(std::vector<struct entry*> entries){
    struct node *new_node = (struct node*) std::malloc(sizeof(struct node));

    new_node->entries = entries;

    return new_node;
}

double dist(struct point *p1, struct point *p2){
    
    return std::sqrt(std::pow(p1->x - p2->x, 2.0) + std::pow(p1->y - p2->y, 2.0));

}