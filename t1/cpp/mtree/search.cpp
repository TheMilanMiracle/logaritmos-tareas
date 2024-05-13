#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "./mtree.h"


long int simulated_reads; // variable para contar las lecturas simuladas de bloques de memoria


void searchTreeRec(struct mtree *t, struct point *q, double r, std::vector<struct point*> *points){

    simulated_reads++; // acceder a un nodo del árbol equivale a una lectura de bloque de memoria

    Node *root = t->entry->a;

    if((*t->entry->a->entries)[0]->a == NULL){ // si el nodo se trata de un nodo hoja

        int n = (*root->entries).size();

        for(int i = 0; i < n; i++){

            Point *p = (*root->entries)[i]->p;
            
            if(dist(p, q) <= r){

                points->push_back(p);

            }

        }

    }
    else{ // si se trata de un nodo externo

        int n = (*root->entries).size();

        std::vector<Entry*> entries = (*root->entries);

        for(int i = 0; i < n; i++){
            
            Entry *entry = entries[i];

            if(dist(entry->p, q) <= r + entry->c_r){

                searchTreeRec(newMTree(entry), q, r, points);

            }

        }

    }
}

std::vector<struct point*> *searchTree(struct mtree* t, struct point*q, double r){

    simulated_reads = 0; // se reinicia el contador de accesos a discos simulados

    std::vector<Point*> *points = new std::vector<Point*>; // vector para los puntos encontrados en la búsqueda

    searchTreeRec(t, q, r, points);

    return points;

}

long int get_simulated_reads(){

    return simulated_reads;

}
