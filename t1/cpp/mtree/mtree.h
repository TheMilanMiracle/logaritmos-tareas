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
    std::vector<struct entry*> *entries;
};
struct entry{
    struct point *p;
    double c_r;
    struct node *a;
};
struct mtree{
    struct entry *entry;
};

struct mtree *newMTree(struct entry *entry);
struct point *newPoint(double x, double y);
struct entry *newEntry(struct point *point, double c_r, struct node *a);
struct node *newNode(std::vector<struct entry*> *entries);

double dist(struct point *p1, struct point *p2);
int get_heigthRec(struct mtree *t);
struct point *medoid(std::vector<struct point*> cluster);

std::vector<struct point*> *searchTree(struct mtree* t, struct point*q, double r);
long int get_simulated_reads();

const int B = 4096 / sizeof(struct entry);
const int b = B / 2;

struct mtree *ciaccia_patella(std::vector<struct point*> set);

struct mtree *sexton_swinbank(std::vector<struct point*> C_in);

std::vector<struct point*> generate_points(double n);

#endif