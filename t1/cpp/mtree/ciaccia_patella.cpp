#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <float.h>
#include "mtree.h"

#define B B
#define b b

struct mtree *ciaccia_patella(std::vector<struct point*> set){

    int set_size = set.size();

    if(set_size <= B){// paso 1

        MTree *sub;
        std::vector<Entry*> sub_entries(set_size);

        for(int i = 0; i < set_size; i++){

            sub_entries[i] = newEntry(set[i], -1, NULL); // entries para las hojas

        }

        sub = newMTree(newNode(sub_entries)); // subarbol con los puntos del input
        
        return sub;

    }

    std::vector<std::vector<Point*>> Sets;

    while(1){ // paso 2

        int k = std::min(B, (int) set.size()/B);// POSIBLE TECHO !!

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

        if(Forest[i]->h == h){

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

    MTree *new_T;

    for(int t = 0; t < T.size(); t++){

        // PENDIENTE: ARREGLEN LA CAGÁ DE ENUNCIAO

    }

    double max = DBL_MIN;

    for(int i = 0; i < T_sup->root->entries.size(); i++){

        // double d = dist(T_sup->root->entries[i]->p, );//distancia

        // if(d > max){

        //     max = d;

        // }

    }

    for(int i = 0; i < T_sup->root->entries.size(); i++){//PEndiente

        T_sup->root->entries[i]->c_r = max;

    }



    return new_T;
}
