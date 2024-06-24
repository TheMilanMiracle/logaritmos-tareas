#include <bits/stdc++.h>

#include "graph.h"


struct graph* makeGraph(int i, int j){

    Graph* new_graph = (Graph*) malloc(sizeof(Graph*));

    std::vector<Vertex*> *V = new std::vector<Vertex*>;

    new_graph->V = V;

    int v = std::pow(2, i);
    long int e = std::pow(2, j);

    for(long unsigned int k = 0; k < v; k++){ // crear los nodos

        Vertex* new_vertex = (Vertex*) malloc(sizeof(Vertex*));

        std::vector<std::pair<struct vertex*, double>> *new_edges = new std::vector<std::pair<struct vertex*, double>>;

        new_vertex->edges = new_edges;

        new_graph->V->push_back(new_vertex);

    }

    std::srand((unsigned) std::time(NULL));

    int count = 0;

    for(long unsigned int k = 1; k <= v-1; k++){ // asegurar el grafo conexo

        int r = std::rand() % k; //r = [0...k-1]

        Vertex* v1 = (*new_graph->V)[k];
        Vertex* v2 = (*new_graph->V)[r];

        double w = (double) std::rand() / RAND_MAX;

        std::pair<struct vertex*, double> p1 = std::make_pair(v2, w);
        std::pair<struct vertex*, double> p2 = std::make_pair(v1, w);

        v1->edges->push_back(p1);
        v2->edges->push_back(p2);

        count++;

    }


    while(e > v-1){ // el resto de aristas

        int i1 = std::rand() % v;
        int i2 = std::rand() % v;

        Vertex* v1 = (*new_graph->V)[i1], *v2;
        if(i1!=i2){v2 = (*new_graph->V)[i2];}
        

        double w = (double) std::rand() / RAND_MAX;

        std::pair<struct vertex*, double> p1 = std::make_pair(v2, w), p2;
        if(i1!=i2){p2 = std::make_pair(v1, w);}

        v1->edges->push_back(p1);
        if(i1!=i2){v2->edges->push_back(p2);}

        count++;

        e--;
    }

    return new_graph;

}


void destroyGraph(struct graph *G){

    for(int i = 0; i < G->V->size(); i++){

        free((*G->V)[i]);

    }

    free(G);

}