#include <bits/stdc++.h>
#include <float.h>

#include "graph.h"


void DijsktraHeap(struct graph G, struct vertex* root){

    std::map<Vertex*, double> *dists = new std::map<Vertex*, double>;
    std::map<Vertex*, Vertex*> *prevs = new std::map<Vertex*, Vertex*>;

    (*dists)[root] = 0.0;
    (*prevs)[root] = NULL;

    std::vector<std::pair<double, Vertex*>> Q;

    std::pair<double, Vertex*> root_p = {0.0, root};

    Q.push_back(root_p);

    for(long unsigned int i = 0; i < G.V->size(); i++){

        if((*G.V)[i] != root){

            (*dists)[(*G.V)[i]] = DBL_MAX;
            (*prevs)[(*G.V)[i]] = NULL;

            std::pair<double, Vertex*> p = {DBL_MAX, (*G.V)[i]};

            Q.push_back(p);

        }

    }

    Heap* PQ = heapify(&Q);

    while(PQ->size){

        std::pair<double, Vertex*> p = heap_extract(PQ);

        for(int i = 0; i < p.second->edges->size(); i++){

            Vertex* v = p.second;
            Vertex* u = (*v->edges)[i].first;
            double w = (*v->edges)[i].second;

            if((*dists)[u] > (*dists)[v] + w){

                (*dists)[u] = (*dists)[v] + w;
                (*prevs)[u] = v;

                decreaseKey(PQ, u, (*dists)[v] + w);

            };

        }

    }

}


void DijsktraFibHeap(struct graph G, struct vertex* root){

    std::unordered_map<Vertex*, double> *dists = new std::unordered_map<Vertex*, double>;
    std::unordered_map<Vertex*, Vertex*> *prevs = new std::unordered_map<Vertex*, Vertex*>;

    (*dists)[root] = 0.0;
    (*prevs)[root] = NULL;

    std::vector<std::pair<double, Vertex*>> Q;

    std::pair<double, Vertex*> root_p = {0.0, root};

    Q.push_back(root_p);

    for(long unsigned int i = 0; i < G.V->size(); i++){

        if((*G.V)[i] != root){

            (*dists)[(*G.V)[i]] = DBL_MAX;
            (*prevs)[(*G.V)[i]] = NULL;

            std::pair<double, Vertex*> p = {DBL_MAX, (*G.V)[i]};

            Q.push_back(p);

        }

    }

    FibHeap* PQ = fibHeap_heapify(&Q);

    while(PQ->n){

        std::pair<double, Vertex*> p = fibHeap_extract(PQ);

        for(long unsigned int i = 0; i < p.second->edges->size(); i++){

            Vertex* v = p.second;
            Vertex* u = (*v->edges)[i].first;
            double w = (*v->edges)[i].second;

            if((*dists)[u] > (*dists)[v] + w){

                (*dists)[u] = (*dists)[v] + w;
                (*prevs)[u] = v;

                fibHeap_decrease_key(PQ, u, (*dists)[v] + w);

            };

        }

    }

}