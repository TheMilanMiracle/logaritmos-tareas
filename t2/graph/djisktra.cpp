#include <bits/stdc++.h>
#include <float.h>

#include "graph.h"


std::pair<std::map<Vertex*, Vertex*>, std::map<Vertex*, double>> Djisktra(Graph G, Vertex* root, Heap *H){

    std::map<Vertex*, double> dists;
    std::map<Vertex*, Vertex*> prevs;

    dists[root] = 0.0;
    prevs[root] = NULL;

    std::vector<std::pair<double, Vertex*>> Q;

    std::pair<double, Vertex*> root_p = {0.0, root};

    Q.push_back(root_p);

    for(long unsigned int i = 0; i < G.V->size(); i++){

        if((*G.V)[i] != root){

            dists[(*G.V)[i]] = DBL_MAX;
            prevs[(*G.V)[i]] = NULL;

            std::pair<double, Vertex*> p = {DBL_MAX, (*G.V)[i]};

            Q.push_back(p);

        }

    }

    Heap* PQ = H->Heapify(&Q);

    while(PQ->A->size()){

        std::pair<double, Vertex*> p = H->Extract(PQ);

        for(long unsigned int i = 0; i < p.second->edges.size(); i++){

            Vertex* v = p.second;
            Vertex* u = v->edges[i].first;
            double w = v->edges[i].second;

            if(dists[u] > dists[v] + w){

                dists[u] = dists[v] + w;
                prevs[u] = v;

                H->DecreaseKey(PQ, u, dists[v] + w);

            };

        }

    }

    std::pair<std::map<Vertex*, Vertex*>, std::map<Vertex*, double>> ret = {prevs, dists};

    return ret;
}