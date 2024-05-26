#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct vertex Vertex;
typedef struct edge Edge;
typedef struct graph Graph;

struct vertex{};
struct{
    struct vertex* v1, v2;
    double w;
};
struct graph{
    std::vector<struct vertex*> *V;
    std::vector<struct edge*> *E;
};

#endif