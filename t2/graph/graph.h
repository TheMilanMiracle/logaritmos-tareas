#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct vertex Vertex;
typedef struct edge Edge;
typedef struct graph Graph;

typedef struct heap Heap;

struct vertex{
    std::vector<std::pair<struct vertex*, double>> edges;
};
struct{
    struct vertex* v1, v2;
    double w;
};
struct graph{
    std::vector<struct vertex*> *V;
    std::vector<struct edge*> *E;
};


struct heap{
    std::vector<std::pair<double, struct vertex*>> *A;
    std::map<struct vertex*, long unsigned int> *M;

    struct heap* (*Heapify)(std::vector<std::pair<double, struct vertex*>> *A) = heapify;
    std::pair<double, struct vertex*>  (*Extract)(struct heap *Heap) = heap_extract;
    void (*DecreaseKey)(struct heap *Heap, struct vertex* v, double d) = decreaseKey;
};

struct heap* heapify(std::vector<std::pair<double, struct vertex*>> *A);
std::pair<double, struct vertex*> heap_extract(struct heap *Heap);
void decreaseKey(struct heap *Heap, struct vertex *v, double d);


#endif