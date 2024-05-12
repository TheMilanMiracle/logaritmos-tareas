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



void lookForRec(MTree *t, int h, std::vector<Point*> *samples, std::vector<MTree*> *forest){

    if((*t->entry->a->entries)[0]->a == NULL){// si este nodo es un nodo externo

        if(h == 1){

            forest->push_back(t); // se agrega el subárbol al vector de subárboles

            samples->push_back(t->entry->p); // se agrega el nuevo sample   

        }

        return;

    }

    if(get_heigth(t) == h){ // si la altura de este subárbol es h, se agrega a forest

        forest->push_back(t); // se agrega el subárbol al vector de subárboles

        samples->push_back(t->entry->p); // se agrega el nuevo sample

    }
    else{ // sino, se sigue buscando recursivamente-

        for(unsigned long int i = 0; i < t->entry->a->entries->size(); i++){//-en cada subárbol

            lookForRec(newMTree((*t->entry->a->entries)[i]), h, samples, forest);

        }

    }


}


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

    if(set_size <= B){// paso 1 (caso base del algoritmo)

        // vector para las entries que almacenará este nodo
        std::vector<Entry*> *sub_entries = new std::vector<Entry*>[set_size];

        for(unsigned long int i = 0; i < set_size; i++){ // se añaden todos los puntos-

            sub_entries->push_back(newEntry(set[i], -1, NULL)); //-como entries

        }

        double max = DBL_MIN;
        Point* med = medoid(set); // punto que representará este nodo

        for(long unsigned int i = 0; i < set_size; i++){ // se calcula el radio de este nodo

            double d = dist(med, set[i]);

            if(d > max){

                max = d;

            }

        }

        MTree *sub = newMTree(newEntry(med, max, newNode(sub_entries))); // subarbol con este nodo como raiz
        
        return sub;

    }

    std::vector<std::vector<Point*>> Sets; // vector para guardar los conjuntos de asignaciones

    while(1){ // paso 2

        int k = std::min(B, (int) std::ceil((double) set.size()/B));

        std::vector<std::vector<Point*>> F(k); // F[i][0]: punto del sample | F[i][1:]: puntos asignados al sample F[0]

        for(int i = 0; i < k; i++){ // O(k) se llenan los F[i][0]:

            std::srand((unsigned)std::time(NULL)); // seed para el random

            int random_k = rand() % set.size(); // get random k \in [0, set.size()]

            F[i].push_back(set[random_k]); // agregar sample a F[i]

            set.erase(set.begin() + random_k); // erase set[k]

        }

        for(int i = 0; i < k; i++){set.push_back(F[i][0]);} // llenar nuevamente el set

        while(set.size()){ // paso 3, para los n puntos se les busca su sample más cercano F[i][1:]:
        
            Point *current = set[set.size()-1]; // actual punto al que se le asignará un sample

            set.pop_back();

            int closer;

            double min = DBL_MAX;

            for(int i = 0; i < k; i++){ // se busca entre los samples generados en el paso anterior

                double d = dist(current, F[i][0]); // distancia entre current y el sample i

                if(d == 0){ // caso sample es el current
                    
                    closer = i;
                    break;

                }
                if(d < min){ // caso se encuentra una mejor distancia

                    closer = i;
                    min = d;

                }


            }

            F[closer].push_back(current); // se agrega current a la asignación correspondiente a su sample más cercano
        
        }

        for(unsigned long int i = 0; i < F.size(); i++){// paso 4: redistribucion 

            if(F[i].size() - 1 < b){ // no se cuenta el punto que represeanta la asignacion

                F[i].erase(F[i].begin()); // se borrar el sample i por ser muy pequeño

                for(unsigned long int j = 0; j < F[i].size(); j++){ // a todos los puntos de la asignacion se les busca una nueva

                    Point* current = F[i][j]; // punto al que se le busca un nuevo sample

                    double min = DBL_MAX;
                    int closer;

                    for(unsigned long int h = 0; h < F.size(); h++){ // se busca el sample más cercano

                        if(h != i){ // no debe ser el mismo sample

                            double d = dist(current, F[h][0]); // distancia entre current y el sample i

                            if(d < min){ // caso se encuentra un sample más cercano

                                min = d;
                                closer = h;

                            }

                        }

                    }

                    F[closer].push_back(current); // se agrega current a su nueva asignación con sample más cercano

                }

                F.erase(F.begin() + i); // se borra el sample demasiado pequeño de la lista

                i--; // ajuste de índice

            }

        }

        if(F.size() == 1){ // si se terminó con sólo un sample, se debe volver al paso 2

            F[0].erase(F[0].begin());

            set = F[0]; // el unico que no fue eliminado

        }
        else{ // se continua con el paso 6

            Sets = F;

            break;
        }
    }

    std::vector<MTree*> Forest(Sets.size()); // vector para los subarboles
    std::vector<Point*> Samples(Sets.size()); // vector para los samples

    for(long unsigned int i = 0; i < Sets.size(); i++){ // paso 6, se construyen los subarboles

        Samples[i] = Sets[i][0]; // se extraen los samples de los vectores originales

        Sets[i].erase(Sets[i].begin()); // se borra el sample (si no se borra, el punto se encuentra repetido en Sets[i])

        Forest[i] = ciaccia_patella(Sets[i]); // se crea el i-ésimo árbol

    }

    std::vector<MTree*> Forest_; // vector auxiliar para subarboles

    for(long unsigned int i = 0; i < Forest.size(); i++){ // paso 7, borrar arboles muy pequeños

        if(Forest[i]->entry->a->entries->size() < b){ // raíz de tamaño menor a b

            MTree *tree = Forest[i];

            for(long unsigned int j = 0; j < tree->entry->a->entries->size(); j++){ // se agregan los subárboles

                Entry *subtree_root = (*tree->entry->a->entries)[j]; // entry del subárbol

                Samples.push_back(subtree_root->p); // se agrega la raíz del subárbol a los samples

                Forest_.push_back(newMTree(subtree_root)); // se agrega el subárbol al vector auxiliar

            }

            Forest.erase(Forest.begin() + i); // se borra la raiz

            Samples.erase(Samples.begin() + i); // se borra su respectivo sample

            i--; // ajuste de índice

        }

    }

    for(unsigned long int i = 0; i < Forest_.size(); i++){ // se agregan los nuevo subárboles

        Forest.push_back(Forest_[i]);

    }

    //paso 8

    int min = INT16_MAX;

    for(long unsigned int i = 0; i < Forest.size(); i++){ // se busca la menor altura en los árboles dentro de Forest

        int h_ = get_heigth(Forest[i]); // altura del i-ésimo árbol

        if(h_ < min){ // caso se encuentra un menor h

            min = h_;

        }

    }

    int h = min; // h es la menor altura entre los arboles
    std::vector<MTree*> T; // T empieza como un conjunto vacío
    std::vector<long unsigned int> idxs;; // vector auxiliar para los indices que se deben

    for(long unsigned int i = 0; i < Forest.size(); i++){

        if(get_heigth(Forest[i]) == h){ // si el árbol es de altura h

            T.push_back(Forest[i]); // se agrega a T

        }
        else{

            lookForRec(Forest[i], h, &Samples, &T); // se busca exhaustivamente todos los subarboles de altura h

            Samples.erase(Samples.begin() + i); // se borra el i-ésimo sample

        }

    }


    MTree *T_sup = ciaccia_patella(Samples);

    for(long unsigned int t = 0; t < T.size(); t++){

        if((*T_sup->entry->a->entries)[t]->a == NULL){//nodo externo

            (*T_sup->entry->a->entries)[t]->a = Forest[t]->entry->a;

            (*T_sup->entry->a->entries)[t]->p = Forest[t]->entry->p;

        }
        else{//nodo interno

            std::vector<Entry*> *tree = listMTree(T_sup); // entries en T_sup
            
            for(unsigned long int i = 0; i < tree->size(); i++){// por cada entry en T_sup

                Entry *current = (*tree)[i];// la actual entry de T_sup

                for(unsigned long int j = 0; j < Forest.size(); j++){// se busca su asignación en Forest

                    if(searchTree(Forest[j], current->p, 0)->size() > 0){ // si es que la actual entry se encuentra en el arbol

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

    return T_sup;
}
