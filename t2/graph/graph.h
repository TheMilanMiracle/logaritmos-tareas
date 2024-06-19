#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct vertex Vertex;
typedef struct graph Graph;

// Graphs
struct vertex{
    void* ptr;
    std::vector<std::pair<struct vertex*, double>> *edges;
};
struct graph{
    std::vector<struct vertex*> *V;
};

struct graph* makeGraph(int i, int j);
void destroyGraph(struct graph *G);


// Heaps
typedef struct heap Heap;

struct heap{
    int size;
    std::vector<std::pair<double, struct vertex*>> *A;
};

struct heap* heapify(std::vector<std::pair<double, struct vertex*>> *A);
std::pair<double, struct vertex*> heap_extract(struct heap *Heap);
void decreaseKey(struct heap *Heap, struct vertex *v, double d);


// Fibonacci Heaps
typedef struct fibHeap FibHeap;
typedef struct fibNode FibNode;

struct fibHeap{
    struct fibNode *min;
    unsigned long int n, roots;
};

struct fibNode{
    std::pair<double, struct vertex*> value;
    struct fibNode *parent, *child, *left, *right; 
    bool marked;
    unsigned long int degree;
};

struct fibHeap* fibHeap_heapify(std::vector<std::pair<double, struct vertex*>> *A);
std::pair<double, struct vertex*> fibHeap_extract(struct fibHeap *H);
void fibHeap_decrease_key(struct fibHeap *H, struct vertex* v, double w);


// Dijsktra

// std::pair<std::map<struct vertex*, struct vertex*>, std::map<struct vertex*, double>> DijsktraHeap(struct graph G, struct vertex* root);
void DijsktraHeap(struct graph G, struct vertex* root);
// std::pair<std::unordered_map<struct vertex*, struct vertex*>, std::unordered_map<struct vertex*, double>> DijsktraFibHeap(struct graph G, struct vertex* root);
void DijsktraFibHeap(struct graph G, struct vertex* root);

#endif