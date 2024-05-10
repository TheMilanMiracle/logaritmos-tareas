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




struct mtree *ciaccia_patella(std::vector<struct point*> set){


    unsigned long int set_size = set.size();
    std::cout << ">>rec ("<< set_size <<")<<" << std::endl;


    if(set_size <= B){// paso 1
        std::cout << ">>caso base " << set_size << "<<" << std::endl;


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

        std::cout << "before" <<F.size() << std::endl;

        std::cout << "[";

        for(int p = 0; p < F.size(); p++){

            std::cout << F[p].size() - 1 << ", ";

        }

        std::cout << "]" << std::endl;


        for(unsigned long int i = 0; i < F.size(); i++){// paso 4: redistribucion 

            std::cout << "lap = " <<i <<" | size = " << F.size() << std::endl;

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

                //     std::cout << F[p].size() - 1 << ", ";

                // }
                // std::cout << "]" << std::endl;

                // std::cout << "f[i]" << F[i].size() - 1 << std::endl;
                // std::cout << "f size" << F.size() << std::endl;

                F.erase(F.begin() + i);

                // std::cout << "f[i]" << F[i].size() - 1 << std::endl;
                // std::cout << "f size" << F.size() << std::endl;

                // std::cout << "[";
                // for(int p = 0; p < F.size(); p++){

                //     std::cout << F[p].size() - 1 << ", ";

                // }
                // std::cout << "]" << std::endl;

                i--;

            }

            // std::cout << "f[i] size" << F[i].size() << std::endl;

        }

        std::cout << "[";

        for(int p = 0; p < F.size(); p++){

            std::cout << F[p].size() - 1 << ", ";

        }

        std::cout << "]" << std::endl;

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

    std::cout << "[";

    for(int p = 0; p < Sets.size(); p++){

        std::cout << Sets[p].size() - 1 << ", ";

    }

    std::cout << "]" << std::endl;
    
    std::cout << "[";
    for(long unsigned int i = 0; i < Sets.size(); i++){ // paso 6, se construyen los subarboles

        std::cout << "-------"<<Sets[i].size() - 1 << "-------";
        Samples[i] = Sets[i][0];

        Sets[i].erase(Sets[i].begin());

        // std::cout << "|SETS[I]| = " << Sets[i].size() << std::endl;

        Forest[i] = ciaccia_patella(Sets[i]);

        // std::cout << "FOREST[I].SIZE = "<<Forest[i]->entry->a->entries->size() << std::endl;

    }
    std::cout << "]" << std::endl;

    std::vector<MTree*> Forest_;

    for(long unsigned int i = 0; i < Forest.size(); i++){ // paso 7, borrar arboles muy pequeños

        // std::cout << "for paso 7 | " << (*Forest[i]->entry->a->entries)[0]->a << std::endl;//0x0

        if(Forest[i]->entry->a->entries->size() < b){ // raiz tamaño menor a b

            for(int p = 0; p < Sets.size(); p++){

                std::cout << Forest[i]->entry->a->entries[p].size() << ", ";

            }


            // std::cout << "split" << std::endl;

            MTree *tree = Forest[i];

            Forest.erase(Forest.begin() + i); // se borra la raiz

            i--;

            for(long unsigned int j = 0; j < tree->entry->a->entries->size(); j++){ // agregar los subarboles

                Entry *subtree_root = (*tree->entry->a->entries)[j];


                std::cout << "paso 7 | " << subtree_root->a << std::endl;//0x0
                std::cout << "paso 7 | " << subtree_root->a->entries->size() << std::endl;//0x0



                Samples.push_back(subtree_root->p);

                Forest_.push_back(newMTree(subtree_root));

            }

        }

    }

    for(unsigned long int i = 0; i < Forest_.size(); i++){

        Forest.push_back(Forest_[i]);

    }

    // std::cout << "|FOREST| = " << Forest.size() << std::endl;

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

            std::cout << "paso 9 | if  | " << Forest[i]->entry->a << std::endl;//0x0

        }
        else{

            // Samples.erase(Samples.begin() + i);
            

            for(long unsigned int j = 0; j < Forest[i]->entry->a->entries->size(); j++){

                int h_ = get_heigth(Forest[j]);

                std::cout << "paso 9 | " << Forest[j]->entry->a << std::endl;//0x0


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
    std::cout << "despuesdelarecursionreql" << std::endl;

    for(long unsigned int t = 0; t < T.size(); t++){

        (*T_sup->entry->a->entries)[t]->a = T[t]->entry->a; //NULL

        (*T_sup->entry->a->entries)[t]->p = T[t]->entry->p;

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

    std::cout << ">>return<<" << std::endl;

    return T_sup;
}
