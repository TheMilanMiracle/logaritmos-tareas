#ifndef __MTREE_H__
#define __MTREE_H__

typedef struct point Point;
typedef struct entry Entry;
typedef struct node Node;
typedef struct mtree MTree;

struct point{
    double x, y;
};
struct node{
    std::vector<struct entry*> entries;
};
struct entry{
    struct point *p;
    double c_r;
    struct node *a;
};
struct mtree{
    struct node *root;
    int h;
};

struct mtree *newMTree(struct node *root, int h);
struct point *newPoint(double x, double y);
struct entry *newEntry(struct point *point, double c_r, struct node *a);
struct node *newNode(std::vector<struct entry*> entries);

double dist(struct point *p1, struct point *p2);

std::vector<struct point*> searchTree(struct mtree* t, struct point*q, double r);

const int B = 4096 / sizeof(struct entry);
const int b = B / 2;

#endif