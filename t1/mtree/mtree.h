#ifndef __MTREE_H__
#define __MTREE_H__

typedef struct point{
    double x, y;
} Point;
typedef struct node{
    int n;
    struct entry **entries;
} Node;
typedef struct entry{
    Point *p;
    double c_r;
    Node *a;
} Entry;
typedef struct mtree{
    Node *root;
    Entry *root_entry;
} MTree;

typedef struct list_element{
    Point* element;
    struct list_element *prev, *next;
}List_element;
typedef struct list{
    List_element* last;
    int len;
} List;



Point *newPoint(double x, double y);
void freePoint(Point* point);

Entry *newEntry(Point* p, double c_r, Node* a);
void freeEntry(Entry* entry);

Node *newNode(Entry **entries, int n);
void freeNode(Node* node);

MTree *newMTree(Node *root, Entry *root_entry);
void freeMTree(MTree* mtree);


void init_search();
void end_search();
List *searchTree(MTree* t, Point*q, double r);

#endif