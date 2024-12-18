#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <float.h>

#include "mtree.h"

#define B B
#define b b


std::vector<std::vector<Point*>> cluster(std::vector<Point*> C_in){

    std::vector<std::vector<Point*>> C_out, C(C_in.size());


    for(long unsigned int i = 0; i < C_in.size(); i++){

        C[i].push_back(C_in[i]); // C[i] = { C_in[i] }

    }

    while(C.size() > 1){
        double min = DBL_MAX, d;
        int c1, c2;

        for(long unsigned int i = 0; i < C.size(); i++){ // i: idx en C del primer cluster

            for(long unsigned int j = 0; j < C.size(); j++){ // j: idx en C del segundo cluster

                if(i != j){ // no deben ser el mismo

                    d = dist(medoid(C[i]), medoid(C[j])); // distacia entre los clusters i y j

                    if(d < min){ // si estan mas cerca que la mejor distancia guardada hasta el momento

                        if(C[i].size() >= C[j].size()){ // |c1| >= |c2|

                            c1 = i;
                            c2 = j;

                        }
                        else{

                            c1 = j;
                            c2 = i;

                        }

                    }

                }

            }

        }

        if(C[c1].size() + C[c2].size() <= B){ // si ambos clusters juntos no cabrian en un nodo

            for(long unsigned int i = 0; i < C[c2].size(); i++){ // c1 = c1 U c2i

                C[c1].push_back(C[c2][i]);

            }

            C.erase(C.begin() + c2);

        }
        else{ // caso contrario, se quita c1 de C y se agrega en C_out
            C_out.push_back(C[c1]);

            C.erase(C.begin() + c1);

        }

    }

    std::vector<Point*> c_, c = C[0]; // c se define como el ultimo cluster en C

    if(C_out.size() > 0){ // si |C_out| > 0

        double min = DBL_MAX;
        int idx;

        for(long unsigned int i = 0; i < C_out.size(); i++){ // se busca el cluster más cercano a c en C_out

            double d = dist(medoid(c), medoid(C_out[i]));

            if(d < min){

                min = d;
                idx = i;

            }

        }

        c_ = C_out[idx]; // c_ es el cluster mas cercano a c

        C_out.erase(C_out.begin() + idx); // se remueve c_ de C_out


    }// si |C_out| == 0, c = {}

    if(c.size() + c_.size() <= B){// si c y c_ caben juntos en un bloque

        for(long unsigned int i = 0; i < c_.size(); i++){ // c = c U c_

            c.push_back(c_[i]);

        }

        C_out.push_back(c); // agregamos c U c_ a C_out

    }
    else{ //sino, se divide c U c_ usando minmax split policy

        for(long unsigned int i = 0; i < c_.size(); i++){ // c = c U c_

            c.push_back(c_[i]);

        }

        std::vector<std::vector<double>> D((c.size(), c.size()));

        std::vector<std::vector<Point*>> c1, c2;
        std::vector<double> d;


        for(long unsigned int i = 0; i < c.size() - d.size(); i++){ // i: primer punto del par de puntos (i,j)

            for(long unsigned int j = 0; j < c.size() - d.size(); j++){ // j: segundo punto del par de puntos (i,j)

                if(i == j){

                    continue;

                }

                std::vector<Point*> c_cpy(c.size());
                std::vector<Point*> c1_, c2_;

                for(long unsigned int k = 0; k < c.size(); k++){ // c_cpy = c

                    c_cpy[k] = c[k];

                }

                c1_.push_back(c_cpy[i]); // c1_ = {c[i]}
                c_cpy.erase(c_cpy.begin() + i); // c = c / {c[i]}

                c2_.push_back(c_cpy[j]); // c2_ = {c[j]}
                c_cpy.erase(c_cpy.begin() + j); // c = c / {c[j]}

                int k = 0;
                double min_c1, min_c2;

                while(c_cpy.size()){

                    k = (k+1)%2; // se busca alternadamente

                    int idx;

                    if(k){
                        min_c1 = DBL_MAX;

                        for(long unsigned int h = 0; h < c_cpy.size(); h++){ // se busca el más cercano al centro
 
                            double d = dist(c[i], c_cpy[h]);

                            if(d < min_c1){

                                min_c1 = d;
                                idx = h;

                            }

                        }

                        c1_.push_back(c_cpy[idx]);

                    }
                    else{
                        min_c2 = DBL_MAX;

                        for(long unsigned int h = 0; h < c_cpy.size(); h++){  // se busca el más cercano al centro

                            double d = dist(c[j], c_cpy[h]);

                            if(d < min_c2){

                                min_c2 = d;
                                idx = h;

                            }

                        }

                        c2_.push_back(c_cpy[idx]);

                    }

                    c_cpy.erase(c_cpy.begin() + idx);

                }

                d.push_back(min_c1 > min_c2 ? min_c1 : min_c2); 
                c1.push_back(c1_);
                c2.push_back(c2_);

            }

        }

        double min = d[0];
        int idx = 0;

        for(long unsigned int i = 1; i < d.size() - 1; i++){

            if(min > d[i]){

                min = d[i];
                idx = i;

            }

        }

        C_out.push_back(c1[idx]);
        C_out.push_back(c2[idx]);
        
    }

    return C_out;

}

Entry* LeafOutput(std::vector<Point*> C_in){

    Point* g = medoid(C_in);
    double r = 0;
    std::vector<Entry*> *C = new std::vector<Entry*>[C_in.size()];

    for(long unsigned int i = 0; i < C_in.size(); i++){

        r = std::max(r, dist(g, C_in[i]));

        C->push_back(newEntry(C_in[i], -1, NULL));

    }

    return newEntry(g, r, newNode(C));

}

Entry* Output(std::vector<Entry*> C_mra){

    std::vector<Point*> C_in(C_mra.size());

    for(long unsigned int i = 0; i < C_mra.size(); i++){

        C_in[i] = C_mra[i]->p;

    }

    Point* G = medoid(C_in);
    double R = 0;

    std::vector<Entry*> *C = new std::vector<Entry*>[C_mra.size()];

    for(long unsigned int i = 0; i < C_mra.size(); i++){

        C->push_back(C_mra[i]);

        R = std::max(R, dist(G, C_mra[i]->p) + C_mra[i]->c_r);

    }

    return newEntry(G, R, newNode(C));

}

struct mtree* sexton_swinbank(std::vector<struct point*> C_in){

    if(C_in.size() <= B){ // si la cantidad de puntos con los que se llama a la función cabe en un nodo 

        Entry* e = LeafOutput(C_in);

        return newMTree(e);

    }

    std::vector<std::vector<Point*>> C_out = cluster(C_in);
    std::vector<Entry*> C; 


    for(long unsigned int i = 0; i < C_out.size(); i++){ // por cada c en C_out, se añade OutputHoja(a) a C

        C.push_back(LeafOutput(C_out[i]));

    }

    while(C.size() > B){

        std::vector<Point*> Medoids(C.size());
        std::vector<std::vector<Point*>> Clusters;

        for(long unsigned int i = 0; i < C.size(); i++){ // Medoids = {g|(g, r, a) en C}

            Medoids[i] = C[i]->p;

        }

        Clusters = cluster(Medoids); // C_out  = clusters(Medoids)
        std::vector<std::vector<Entry*>> C_mra(Clusters.size()); // C_mra = {}

        for(long unsigned int i = 0; i < Clusters.size(); i++){// i == c

            std::vector<Entry*> current(Clusters[i].size());

            for(long unsigned int j = 0; j < Clusters[i].size(); j++){

                for(long unsigned int k = 0; k < C.size(); k++){

                    if(C[k]->p == Clusters[i][j]){

                        current[j] = newEntry(C[k]->p, C[k]->c_r, C[k]->a);
                        break;

                    }

                }

            }


            C_mra[i] = current;

        }

        std::vector<Entry*> C2;

        C = C2;

        for(long unsigned int i = 0; i < C_mra.size(); i++){ // por cada s en C_mra se añade Output(s) a C

            C.push_back(Output(C_mra[i]));

        }

    }

    Entry *ret = Output(C); // sea Output(C) la entry (g, r, a)

    return newMTree(ret); // se retorna el árbol

} 