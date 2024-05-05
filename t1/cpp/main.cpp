#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include <float.h>
// using namespace std;

#define B 4096 / sizeof(Entry) // B = 4096 / sizeof(Entry) = 512
#define b B/2

typedef struct point Point;
typedef struct entry Entry;
typedef struct node Node;
typedef struct mtree MTree;

struct point{
    double x, y;
};
struct node{
    std::vector<Entry*> entries;
};
struct entry{
    Point *p;
    double c_r;
    Node *a;
};
struct mtree{
    Node *root;
    int h;
};

MTree *newMTree(Node *root, int h){ //, Entry *root_entry
    void *memory = malloc(sizeof(MTree));

    MTree *new_tree = new (memory) MTree;

    new_tree->root = root;
    new_tree->h = h;
    // new_tree->root_entry = root_entry;

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

Node *newNode(std::vector<Entry*> entries, int n){
    Node *new_node = (Node*) malloc(sizeof(Node));

    new_node->entries = entries;
    new_node->n = n;

    return new_node;
}

double dist(Point *p1, Point *p2){
    
    return sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));

}


void searchTreeRec(MTree* t, Point *q, double r, std::vector<Point*> *points){
    // printf("rec | %f\n", t->root_entry->c_r);
    // std::cout << "searchTreeRec ("<<t->root_entry->p->x<<")" << std::endl;

    Node *root = t->root; // nodo raiz de este subarbol

    // printf("post Node\n");

    // Entry *entry = t->root->entries[0];


    if(t->root->entries[0]->a == NULL){// t->root->a
        // printf("NULL\n");
        std::cout << "if" << std::endl;

        int n = root->n;

        for(int i = 0; i < n; i++){// O(n)

            // entry = root->entries[i];// O(1)

            Point *p = root->entries[i]->p;

            // printf("dist = %f | r = %f \n", dist(p, q), r);

            std::cout << dist(p, q) << " | " << r << std::endl;
            
            if(dist(p, q) <= r){

                // list_add(points, entry->p);

                points->push_back(p); // a->b == *().b

            }


        }

    }

    else{
        // printf("else\n");


        int n = root->n;

        // printf("%d\n", n);

        std::vector<Entry*> entries = root->entries;

        for(int i = 0; i < n; i++){// O(n)
            // printf("for\n");
            
            Entry *entry = entries[i];// O(1)

            if(dist(entry->p, q) <= r + entry->c_r){
                // printf("if\n");

                searchTreeRec(newMTree(entry->a), q, r, points); //, entry)

            }

        }

    }
}


std::vector<Point*> searchTree(MTree* t, Point*q, double r){

    std::vector<Point*> points; //vector *p -> p[0] = *(p + 0)

    Node *root = t->root;

    // if(dist(t->root_entry->p, q) <= r){

    //     list_add(points, t->root_entry->p);

    //     printf("add\n");

    // }
    
    searchTreeRec(t, q, r, &points);

    return points;

}

MTree *ciaccia_patella(std::vector<Point*> set){

    int set_size = set.size();

    if(set_size <= B){// paso 1

        MTree *sub;
        std::vector<Entry*> sub_entries(set_size);

        for(int i = 0; i < set_size; i++){

            sub_entries[i] = newEntry(set[i], -1, NULL); // entries para las hojas

        }

        sub = newMTree(newNode(sub_entries, set_size), 1); // subarbol con los puntos del input
        
        return sub;

    }

    std::vector<std::vector<Point*>> Sets;

    while(1){ // paso 2

        int k = std::min(B, set.size()/B);// POSIBLE TECHO !!

        std::vector<std::vector<Point*>> F(k); // F[i][0]: punto del sample | F[i][1:]: puntos asignados al sample F[0]

        //std::vector<Point*> set_cpy(set.size());

        for(int i = 0; i < k; i++){ // O(k) se llenan los F[i][0]:

            std::srand((unsigned)std::time(NULL)); // seed para el random

            int random_k = rand() % set.size(); // get random k \in [0, set.size()]

            F[i].push_back(set[random_k]); // agregar sample a F[i]

            set.erase(set.begin() + k - 1); // erase set[k]

        }

        for(int i = 0; i < k; i++){set.push_back(F[i][0]);} //llenar nuevamente el set

        while(set.size()){ // paso 3, para los n-k puntos restantes se les busca su sample más cercano F[i][1:]:
        
            Point *current = set[set.size()-1];

            set.pop_back();

            int closer;

            double min = DBL_MAX;

            for(int i = 0; i < k; i++){

                double d = dist(current, F[i][0]);

                if(d < min){

                    closer = i;
                    min = d;

                }

            }

            F[closer].push_back(current);
        
        }

        for(int i = 0; i < k; i++){// paso 4: redistribucion 

            if(F[i].size() - 1 < b){ // no se cuenta el punto que represeanta la asignacion

                Point *current = F[i][0]; // sample i

                int closer;

                double min = DBL_MAX;

                for(int j = 0; j < k; j++){ // se busca el sample mas cercano

                    if(i != j){ // que no sea si mismo

                        double d = dist(current, F[i][0]); // distancia al sample

                        if(d < min){ // nuevo minimo

                            closer = j;
                            min = d;

                        }

                    }

                }

                int len = F[i].size(); // cantidad de puntos asignados al sample y el sample

                while(len--){ // mientras aun no se vacie la asignacion

                    Point *p = F[i][len-1];

                    F[closer].push_back(p); // se agrega el punto a la nueva asignacion

                    F[i].erase(F[i].begin() + len - 1); // se elimina de la primera asignacion

                }

                F.erase(F.begin() + i - 1); // eliminar F[i]

            }

        }
        if(F.size() == 1){ // se debe volver al paso 2
            
            set = F[0]; // el unico que no fue eliminado

        }
        else{ // se continua con el paso 6

            Sets = F;

            break;
        }
    }

    std::vector<MTree*> Forest(Sets.size());
    std::vector<Point*> Samples(Sets.size());

    for(int i = 0; i < Sets.size(); i++){ // paso 6, se construyen los subarboles

        Samples[i] = Sets[i][0];

        Sets[i].erase(Sets[i].begin());

        Forest[i] = ciaccia_patella(Sets[i]);

    }

    for(int i = 0; i < Forest.size(); i++){ // paso 7, borrar arboles muy pequeños

        if(Forest[i]->root->entries.size() < b){ // raiz tamaño menor a b

            MTree *tree = Forest[i];

            Forest.erase(Forest.begin() + i - 1); // se borra la raiz

            for(int j = 0; j < tree->root->entries.size(); j++){ // agregar los subarboles

                Node *subtree_root = tree->root->entries[j]->a;

                Forest.push_back(newMTree(subtree_root, tree->h - 1));

            }


            //PENDIENTE: ELIMINAR EL ARBOL CON TAMAÑO < b (asumamos que ahora esta bien)
        }

    }
    //paso 8

    int min = INT16_MAX;

    for(int i = 0; i < Forest.size(); i++){

        if(Forest[i]->h){

            min = Forest[i]->h;

        }

    }

    int h = min;
    std::vector<MTree*> T;


    for(int i = 0; i < Forest.size(); i++){// O(N)

        if(Forest[i]->h = h){

            T.push_back(Forest[i]);

        }
        else{

            Samples.erase(Samples.begin() + i - 1);

            for(int j = 0; j < Forest[i]->root->entries.size(); j++){

                if(Forest[j]->h){

                    T.push_back(Forest[j]);

                    Samples.push_back(Forest[i]->root->entries[j]->p);

                }

            }

        }

    }

    MTree *T_sup = ciaccia_patella(Samples);

    MTree new_T;

    for(int t = 0; t < T.size(); t++){

        // PENDIENTE: ARREGLEN LA CAGÁ DE ENUNCIAO

    }

    double max = DBL_MIN;

    for(int i = 0; i < T_sup->root->entries.size(); i++){

        double d = dist(T_sup->root->entries[i]->p, );//distancia

        if(d > max){

            max = d;

        }

    }

    for(int i = 0; i < T_sup->root->entries.size(); i++){//PEndiente

        T_sup->root->entries[i]->c_r = max;

    }



    return new_T;
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


    std::vector<Entry*> e3_entries = {newEntry(o1, -1, NULL), newEntry(o2, -1, NULL)};
    Node *e3 = newNode(e3_entries, 2);
    Entry *e3_entry = newEntry(newPoint(-5.0, 0.0), 3, e3);

    std::vector<Entry*> e4_entries = {newEntry(o3, -1, NULL), newEntry(o4, -1, NULL)};
    Node *e4 = newNode(e4_entries, 2);
    Entry *e4_entry = newEntry(newPoint(-8.0, 0.0), 4, e4);


    std::vector<Entry*> e1_entries = {e3_entry, e4_entry};
    Node *e1 = newNode(e1_entries, 2);
    Entry *e1_entry = newEntry(newPoint(-6.0, 0.0), 10, e1); 


    // MTree *tree = newMtree(e1);//e1_entry

    // init_search();

    std::vector<Point*> puntos = searchTree(tree, newPoint(-2.0, 0.0), 20);

    std::cout << puntos.size() << std::endl;

    // end_search();


    std::srand((unsigned) std::time(NULL));
    
    std::cout << std::rand() << std::endl;


    // std::vector<int> myvector;

    // // set some values (from 1 to 10)
    // for (int i=1; i<=10; i++) myvector.push_back(i);

    // // erase the 6th element
    // myvector.erase (myvector.begin()+5);

    // // erase the first 3 elements:
    // myvector.erase (myvector.begin(),myvector.begin()+3);

    // std::cout << "myvector contains:";
    // for (unsigned i=0; i<myvector.size(); ++i)
    //     std::cout << ' ' << myvector[i];
    // std::cout << '\n';

}