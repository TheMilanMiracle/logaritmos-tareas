#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <float.h>
#include "mtree.h"

#include <iostream>

#define B B
#define b b


void listMTreeRec(MTree *t, std::vector<Entry*> *Entries){

    Node *root = t->entry->a;

    if((*t->entry->a->entries)[0]->a == NULL){
        // std::cout << "if" << std::endl;

        int n = (*root->entries).size();

        // std::cout << "if -- "<<n << std::endl;


        for(int i = 0; i < n; i++){

            Entries->push_back((*t->entry->a->entries)[i]);

        }

        // std::cout << Entries->size() << std::endl;

    }
    else{
        // std::cout << "else" << std::endl;


        int n = (*root->entries).size();

        std::vector<Entry*> entries = (*root->entries);

        for(int i = 0; i < n; i++){
            
            Entry *entry = entries[i];

            listMTreeRec(newMTree(entry), Entries);

        }

    }
}

std::vector<Entry*> *listMTree(MTree *t){

    std::vector<Entry*> *ret = new std::vector<Entry*>;

    listMTreeRec(t, ret);

    // std::cout << "antes de salrir" << ret->size() << std::endl;
 
    return ret;

}

struct mtree *ciaccia_patella(std::vector<struct point*> set){

    unsigned long int set_size = set.size();
    // std::cout << ">>rec ("<< set_size <<")<<" << std::endl;

    if(set_size <= B){// paso 1
        // std::cout << ">>caso base " << set_size << "<<" << std::endl;


        MTree *sub;
        std::vector<Entry*> *sub_entries = new std::vector<Entry*>[set_size];

        for(unsigned long int i = 0; i < set_size; i++){

            sub_entries->push_back(newEntry(set[i], -1, NULL)); // entries para las hojas

        }

        double max = DBL_MIN;
        Point* med = medoid(set);

        for(long unsigned int i = 0; i < set_size; i++){

            double d = dist(med, set[i]);

            if(d > max){

                max = d;

            }

        }

        sub = newMTree(newEntry(med, max, newNode(sub_entries))); // subarbol con los puntos del input
        
        return sub;

    }

    std::vector<std::vector<Point*>> Sets;

    while(1){ // paso 2

        std::cout << ">> while <<" << std::endl;


        int k = std::min(B, (int) std::ceil((double) set.size()/B));

        std::vector<std::vector<Point*>> F(k); // F[i][0]: punto del sample | F[i][1:]: puntos asignados al sample F[0]

        //std::vector<Point*> set_cpy(set.size());

        for(int i = 0; i < k; i++){ // O(k) se llenan los F[i][0]:

            std::srand((unsigned)std::time(NULL)); // seed para el random

            int random_k = rand() % set.size(); // get random k \in [0, set.size()]

            F[i].push_back(set[random_k]); // agregar sample a F[i]

            set.erase(set.begin() + random_k); // erase set[k]

        }

        for(int i = 0; i < k; i++){set.push_back(F[i][0]);} //llenar nuevamente el set

        while(set.size()){ // paso 3, para los n puntos se les busca su sample más cercano F[i][1:]:
        
            Point *current = set[set.size()-1];

            set.pop_back();

            int closer;

            double min = DBL_MAX;

            for(int i = 0; i < k; i++){

                double d = dist(current, F[i][0]);

                if(d == 0){
                    
                    closer = i;
                    break;

                }
                if(d < min){

                    closer = i;
                    min = d;

                }


            }

            F[closer].push_back(current);
        
        }

        // std::cout << "before" <<F.size() << std::endl;

        // std::cout << "[";

        // for(int p = 0; p < F.size(); p++){

            // std::cout << F[p].size() - 1 << ", ";

        // }

        // std::cout << "]" << std::endl;


        for(unsigned long int i = 0; i < F.size(); i++){// paso 4: redistribucion 

            // std::cout << "lap = " <<i <<" | size = " << F.size() << std::endl;

            if(F[i].size() - 1 < b){ // no se cuenta el punto que represeanta la asignacion


            
                F[i].erase(F[i].begin()); // borrar el sample i

                for(unsigned long int j = 0; j < F[i].size(); j++){ // se busca el sample mas cercano

                    Point* current = F[i][j];

                    double min = DBL_MAX;
                    int closer;

                    for(unsigned long int h = 0; h < F.size(); h++){

                        if(h != i){

                            double d = dist(current, F[h][0]);

                            if(d < min){

                                min = d;
                                closer = h;

                            }

                        }

                    }

                    F[closer].push_back(current);

                }


                // std::cout << "[";
                // for(int p = 0; p < F.size(); p++){

                    // std::cout << F[p].size() - 1 << ", ";

                // }
                // std::cout << "]" << std::endl;

                // std::cout << "f[i]" << F[i].size() - 1 << std::endl;
                // std::cout << "f size" << F.size() << std::endl;

                F.erase(F.begin() + i);

                // std::cout << "f[i]" << F[i].size() - 1 << std::endl;
                // std::cout << "f size" << F.size() << std::endl;

                // std::cout << "[";
                // for(int p = 0; p < F.size(); p++){

                    // std::cout << F[p].size() - 1 << ", ";

                // }
                // std::cout << "]" << std::endl;

                i--;

            }

            // std::cout << "f[i] size" << F[i].size() << std::endl;

        }

        // std::cout << "[";

        // for(int p = 0; p < F.size(); p++){

            // std::cout << F[p].size() - 1 << ", ";

        // }

        // std::cout << "]" << std::endl;

        if(F.size() == 1){ // se debe volver al paso 2

            F[0].erase(F[0].begin());

            set = F[0]; // el unico que no fue eliminado

        }
        else{ // se continua con el paso 6

            Sets = F;

            break;
        }
    }

    std::vector<MTree*> Forest(Sets.size());
    std::vector<Point*> Samples(Sets.size());

    // std::cout << "[";

    // for(int p = 0; p < Sets.size(); p++){

        // std::cout << Sets[p].size() - 1 << ", ";

    // }

    // std::cout << "]" << std::endl;
    
    // std::cout << "[";
    for(long unsigned int i = 0; i < Sets.size(); i++){ // paso 6, se construyen los subarboles

        // std::cout << "-------"<<Sets[i].size() - 1 << "-------";
        Samples[i] = Sets[i][0];

        Sets[i].erase(Sets[i].begin());

        // std::cout << "|SETS[I]| = " << Sets[i].size() << std::endl;

        Forest[i] = ciaccia_patella(Sets[i]);

        // std::cout << "FOREST[I].SIZE = "<<Forest[i]->entry->a->entries->size() << std::endl;

    }
    // std::cout << "]" << std::endl;

    std::vector<MTree*> Forest_;

    for(long unsigned int i = 0; i < Forest.size(); i++){ // paso 7, borrar arboles muy pequeños

        // std::cout << "for paso 7 | " << (*Forest[i]->entry->a->entries)[0]->a << std::endl;//0x0

        if(Forest[i]->entry->a->entries->size() < b){ // raiz tamaño menor a b

            // std::cout << "[";

            // for(int p = 0; p < Sets.size(); p++){

                // std::cout << Forest[i]->entry->a->entries[p].size() << ", ";

            // }
            // std::cout << "]" << std::endl;


            // std::cout << "split" << std::endl;

            MTree *tree = Forest[i];

            for(long unsigned int j = 0; j < tree->entry->a->entries->size(); j++){ // agregar los subarboles

                Entry *subtree_root = (*tree->entry->a->entries)[j];


                // std::cout << "paso 7 | " << subtree_root->a << std::endl;//0x0
                // std::cout << "paso 7 | " << subtree_root->a->entries->size() << std::endl;//0x0



                Samples.push_back(subtree_root->p);

                Forest_.push_back(newMTree(subtree_root));

            }

            Forest.erase(Forest.begin() + i); // se borra la raiz

            Samples.erase(Samples.begin() + i); // se borra el sample

            i--;

        }

    }

    for(unsigned long int i = 0; i < Forest_.size(); i++){

        Forest.push_back(Forest_[i]);

    }

    // std::cout << "|FOREST| = " << Forest.size() << std::endl;

    // std::cout << "(Samples, Forest) = ( "<< Samples.size() <<", " << Forest.size() <<")" << std::endl;

    //paso 8

    int min = INT16_MAX;

    for(long unsigned int i = 0; i < Forest.size(); i++){

        int h = get_heigth(Forest[i]);

        if(h < min){

            min = h;

        }

    }

    int h = min;
    std::vector<MTree*> T;
    std::vector<Point*> Samples_;
    std::vector<long unsigned int> idxs;;

    for(long unsigned int i = 0; i < Forest.size(); i++){// O(N)

        if(get_heigth(Forest[i]) == h){

            T.push_back(Forest[i]);

            // std::cout << "paso 9 | if  | " << Forest[i]->entry->a << std::endl;//0x0

        }
        else{

            // Samples.erase(Samples.begin() + i);
            

            for(long unsigned int j = 0; j < Forest[i]->entry->a->entries->size(); j++){

                int h_ = get_heigth(Forest[j]);

                // std::cout << "paso 9 | " << Forest[j]->entry->a << std::endl;//0x0


                if(h == h_){



                    T.push_back(Forest[j]);

                    // Samples.push_back(Forest[i]->entry->p);
                    Samples_.push_back(Forest[i]->entry->p);

                }

            }

        }

    }

    

    for(unsigned long int i = 0; i < idxs.size(); i++){

        Samples.erase(Samples.begin() + idxs[i]);

    }
    for(unsigned long int i = 0; i < Samples_.size(); i++){

        Samples.push_back(Samples_[i]);

    }


    MTree *T_sup = ciaccia_patella(Samples);
    // std::cout << "despuesdelarecursionreql" << std::endl;


    // std::cout << "forest size "<< Forest.size() << std::endl;
    // std::cout << "samples size "<< Samples.size() << std::endl;
    for(long unsigned int t = 0; t < T.size(); t++){

        // std::cout << "tsup entries"<<(*T_sup->entry->a->entries).size() << std::endl;
        // std::cout << "t entries"<<(T).size() << std::endl;

        // std::cout << "ants" << (*T_sup->entry->a->entries)[t]->a << std::endl;

        if((*T_sup->entry->a->entries)[t]->a == NULL){//nodo externo

            (*T_sup->entry->a->entries)[t]->a = Forest[t]->entry->a;

            (*T_sup->entry->a->entries)[t]->p = Forest[t]->entry->p;

        }
        else{//nodo interno

            // std::cout << "MATENMECTM (ELSE)" << std::endl;

            std::vector<Entry*> *tree = listMTree(T_sup); // entries en T_sup
            
            // std::cout << "listree " << tree->size() << std::endl;


            for(unsigned long int i = 0; i < tree->size(); i++){// por cada entry en T_sup
                // std::cout << "(ELSE) for" << std::endl;

                Entry *current = (*tree)[i];// la actual entry de T_sup

                for(unsigned long int j = 0; j < Forest.size(); j++){// se busca su asignación en Forest

                    // std::cout << "search " << searchTree(Forest[j], current->p, 0)->size() << std::endl;

                    if(searchTree(Forest[j], current->p, 0)->size() > 0){ // si es que la actual entry se encuentra en el arbol

                        for(int h = 0; h < Forest[j]->entry->a->entries->size(); h++){

                            // std::cout << "(" << (*Forest[j]->entry->a->entries)[h]->p->x<<"," << (*Forest[j]->entry->a->entries)[h]->p->y<<"), ";

                        }
                        // std::cout << std::endl;

                        // std::cout << "found " << (*searchTree(Forest[j], current->p, 0))[0]->x << ","<< (*searchTree(Forest[j], current->p, 0))[0]->y<< std::endl;
                        // std::cout << "found " << current->p->x << ","<< current->p->y << std::endl;

                        current->a = Forest[j]->entry->a; // se conecta

                        current->c_r = Forest[j]->entry->c_r; // se conecta

                        current->p = Forest[j]->entry->p; // se conecta

                        Forest.erase(Forest.begin() + j); // se elimina

                        break;

                    }

                }

            }

            break;

        }



    }

    double max = DBL_MIN;
    Point* med = medoid(Samples);

    for(long unsigned int i = 0; i < T_sup->entry->a->entries->size(); i++){

        double d = dist(med, (*T_sup->entry->a->entries)[i]->p);

        if(d > max){

            max = d;

        }

    }

    for(long unsigned int i = 0; i < T_sup->entry->a->entries->size(); i++){

        (*T_sup->entry->a->entries)[i]->c_r = max;

    }

    // std::cout << ">>return<<" << std::endl;

    return T_sup;
}
