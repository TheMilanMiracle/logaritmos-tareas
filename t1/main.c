#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mtree/mtree.h"

List *point_list;

int main(){


    // Node *o1 = newNode(NULL, 0);
    Point *o1 = newPoint(-5.0, 0.0);

    // Node *o2 = newNode(NULL, 0);
    Point *o2 = newPoint(-2.0, 0.0);

    // Node *o3 = newNode(NULL, 0);
    Point *o3 = newPoint(-8.0, 0.0);

    // Node *o4 = newNode(NULL, 0);
    Point *o4 = newPoint(-12.0, 0.0);


    Entry *e3_entries[2] = {newEntry(o1, -1, NULL), newEntry(o2, -1, NULL)};
    Node *e3 = newNode(e3_entries, 2);
    Entry *e3_entry = newEntry(newPoint(-5.0, 0.0), 3, e3);

    Entry *e4_entries[2] = {newEntry(o3, -1, NULL), newEntry(o4, -1, NULL)};
    Node *e4 = newNode(e4_entries, 2);
    Entry *e4_entry = newEntry(newPoint(-8.0, 0.0), 4, e4);


    Entry *e1_entries[2] = {e3_entry, e4_entry};
    Node *e1 = newNode(e1_entries, 2);
    Entry *e1_entry = newEntry(newPoint(-6.0, 0.0), 10, e1); 


    MTree *tree = newMTree(e1, e1_entry);

    // init_search();

    List *puntos = searchTree(tree, newPoint(-2.0, 0.0), 0);

    printf("%d \n", puntos->len);

    // end_search();

}





#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

typedef struct point Point;
typedef struct entry Entry;
typedef struct node Node;
typedef struct mtree MTree;

struct point{
    double x, y;
};
struct node{
    int n;
    vector<Entry*> entries;
};
struct entry{
    Point *p;
    double c_r;
    Node *a;
};
struct mtree{
    Node *root;
    Entry *root_entry;
};


MTree *nMTree(Node *root, Entry *root_entry){
    void *memory = malloc(sizeof(MTree));

    MTree *new_tree = new (memory) MTree;

    new_tree->root = root;
    new_tree->root_entry = root_entry;

    return new_tree;
}

Point *newPoint(double x, double y){
    Point *new_point = (Point*) malloc(sizeof(Point));

    new_point->x = x;
    new_point->y = y;

    return new_point;
}

Entry *newEntry(Point *point, double c_r, Node *a){
    Entry *new_entry = (Entry*) malloc(sizeof(Entry));

    new_entry->p = point;
    new_entry->c_r = c_r;
    new_entry->a = a;

    return new_entry;
}

Node *newNode(vector<Entry*> entries, int n){
    Node *new_node = (Node*) malloc(sizeof(Node));

    new_node->entries = entries;
    new_node->n = n;

    return new_node;
}

double dist(Point *p1, Point *p2){
    
    return sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));

}


void searchTreeRec(MTree* t, Point *q, double r, vector<Point*> points){
    // printf("rec | %f\n", t->root_entry->c_r);
    cout << "searchTreeRec" << endl;

    Node *root = t->root; // nodo raiz de este subarbol

    // printf("post Node\n");

    // Entry *entry = t->root->entries[0];

    if(t->root->entries[0] == NULL){// t->root->a
        // printf("NULL\n");
        cout << "if" << endl;

        int n = root->n;

        for(int i = 0; i < n; i++){// O(n)

            // entry = root->entries[i];// O(1)

            Point *p = root->entries[i]->p;

            // printf("dist = %f | r = %f \n", dist(p, q), r);
            
            if(dist(p, q) <= r){

                // list_add(points, entry->p);
                points.push_back(p);

            }


        }

    }

    else{
        // printf("else\n");


        int n = root->n;

        // printf("%d\n", n);

        vector<Entry*> entries = root->entries;

        for(int i = 0; i < n; i++){// O(n)
            // printf("for\n");
            
            Entry *entry = entries[i];// O(1)

            if(dist(entry->p, q) <= r + entry->c_r){
                // printf("if\n");

                searchTreeRec(nMTree(entry->a, entry), q, r, points);

            }

        }

    }
}


vector<Point*> searchTree(MTree* t, Point*q, double r){

    vector<Point*> points; //vector *p -> p[0] = *(p + 0)

    Node *root = t->root;

    // if(dist(t->root_entry->p, q) <= r){

    //     list_add(points, t->root_entry->p);

    //     printf("add\n");

    // }
    
    searchTreeRec(t, q, r, points);

    return points;

}



int main(){


    // Node *o1 = newNode(NULL, 0);
    Point *o1 = newPoint(-5.0, 0.0);

    // Node *o2 = newNode(NULL, 0);
    Point *o2 = newPoint(-2.0, 0.0);

    // Node *o3 = newNode(NULL, 0);
    Point *o3 = newPoint(-8.0, 0.0);

    // Node *o4 = newNode(NULL, 0);
    Point *o4 = newPoint(-12.0, 0.0);


    vector<Entry*> e3_entries = {newEntry(o1, -1, NULL), newEntry(o2, -1, NULL)};
    Node *e3 = newNode(e3_entries, 2);
    Entry *e3_entry = newEntry(newPoint(-5.0, 0.0), 3, e3);

    vector<Entry*> e4_entries = {newEntry(o3, -1, NULL), newEntry(o4, -1, NULL)};
    Node *e4 = newNode(e4_entries, 2);
    Entry *e4_entry = newEntry(newPoint(-8.0, 0.0), 4, e4);


    vector<Entry*> e1_entries = {e3_entry, e4_entry};
    Node *e1 = newNode(e1_entries, 2);
    Entry *e1_entry = newEntry(newPoint(-6.0, 0.0), 10, e1); 


    MTree *tree = nMTree(e1, e1_entry);

    // init_search();

    vector<Point*> puntos = searchTree(tree, newPoint(-2.0, 0.0), 20);

    cout << puntos.size() << endl;

    // end_search();

}