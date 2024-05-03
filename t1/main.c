#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mtree/mtree.h"

List *point_list;

int main(){

    // Node *o1 = {NULL};
    // Entry *o1_entry = {o1, 0, (Point*){-5, 0}};

    Node *o1 = newNode(NULL, 0);
    Entry *o1_entry = newEntry(newPoint(-5.0, 0.0), 0, o1);

    // Node *o2 = {NULL};
    // Entry *o2_entry = {o2, 0, (Point*){-2, 0}};

    Node *o2 = newNode(NULL, 0);
    Entry *o2_entry = newEntry(newPoint(-2.0, 0.0), 0, o2);

    // Node *o3 = {NULL};
    // Entry *o3_entry = {NULL, 0, (Point*){-8, 0}};

    Node *o3 = newNode(NULL, 0);
    Entry *o3_entry = newEntry(newPoint(-8.0, 0.0), 0, o3);

    // Node *o4 = {NULL};
    // Entry *o4_entry = {o4, 0, (Point*){-12, 0}};

    Node *o4 = newNode(NULL, 0);
    Entry *o4_entry = newEntry(newPoint(-12.0, 0.0), 0, o4);

    // Node *e3 = {(Entry**){o1_entry, o2_entry}};
    // Entry *e3_entry = {e3, 3, (Point*){-5, 0}};

    Entry *e3_entries[2] = {o1_entry, o2_entry};
    Node *e3 = newNode(e3_entries, 2);
    Entry *e3_entry = newEntry(newPoint(-5.0, 0.0), 3, e3);

    // Node *e4 = {(Entry**){o3_entry, o4_entry}};
    // Entry *e4_entry = {e4, 3, (Point*){-8, 0}};

    Entry *e4_entries[2] = {o3_entry, o4_entry};
    Node *e4 = newNode(e4_entries, 2);
    Entry *e4_entry = newEntry(newPoint(-8.0, 0.0), 4, e4);

    // Node *e1 = {(Entry**){o3_entry, o4_entry}};
    // Entry *e1_entry = {e1, 10, (Point*){-6, 0}};

    Entry *e1_entries[2] = {e3_entry, e4_entry};
    Node *e1 = newNode(e1_entries, 2);
    Entry *e1_entry = newEntry(newPoint(-6.0, 0.0), 10, e1); 

    // MTree *tree = {e1_entry};

    MTree *tree = newMTree(e1, e1_entry);

    // init_search();

    List *puntos = searchTree(tree, newPoint(-2.0, 0.0), 20);

    printf("%d \n", puntos->len);

    // end_search();

}