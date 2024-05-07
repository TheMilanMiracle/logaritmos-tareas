#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <float.h>

#include "mtree.h"

#define B B
#define b b

Point* medoid(std::vector<Point*> cluster){// O(n*n)
    int med;
    
    if(cluster.size() == 1){

        return cluster[0];

    }
    else{

        double min = DBL_MAX, sum;

        for(int i = 0; i < cluster.size(); i++){

            sum = 0;

            for(int j = 0; j < cluster.size(); j++){

                if(i != j){

                    sum += dist(cluster[i], cluster[j]);

                }

                if(sum > min){break;}

            }

            if(sum < min){

                med = i;

            }

        }

        return cluster[med];

    }

}


std::vector<std::vector<Point*>> cluster(std::vector<Point*> C_in){

    std::vector<std::vector<Point*>> C_out, C(C_in.size());

    for(int i = 0; i < C_in.size(); i++){

        C[i][0] = C_in[i]; // C[i] = { C_in[i] }

    }


    while(C.size() > 1){
        double min = DBL_MAX, d;
        int c1, c2;

        for(int i = 0; C.size(); i++){ // encontrar los dos clusters más cercanos

            for(int j = 0; C.size(); j++){

                if(i != j){

                    d = dist(medoid(C[i]), medoid(C[j]));

                    if(d < min){

                        if(C[i].size() > C[j].size()){

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

        if(C[c1].size() + C[c2].size() <= B){ // si ambos juntos son mas pequeños que B se fusionan en un clusters

            for(int i = 0; i < C[c2].size(); i++){

                C[c1].push_back(C[c2][i]);

            }

            C.erase(C.begin() + c2 - 1);

        }
        else{

            C_out.push_back(C[c1]);

            C.erase(C.begin() + c1 - 1);

        }

    }

    std::vector<Point*> c_, c = C[0];

    if(C_out.size() > 0){

        double min = DBL_MAX;

        for(int i = 0; i < C_out.size(); i++){

            double d = dist(medoid(c), medoid(C_out[i]));

            if(d < min){

                min = d;
                c_ = C_out[i];

            }

        }


    }
    if(c.size() + c_.size() <= B){

        for(int i = 0; i < c_.size(); i++){

            c.push_back(c_[0]);

        }

        C_out.push_back(c);

    }
    else{
        for(int i = 0; i < c_.size(); i++){

            c.push_back(c_[0]);

        }




        std::vector<std::vector<Point*>> c1, c2;
        std::vector<double> d;


        for(int i = 0; i < c.size() + c_.size(); i++){

            for(int j = 0; j < c.size() + c_.size(); j++){

                std::vector<Point*> c_cpy(c.size());
                std::vector<Point*> c1_, c2_;


                for(int k = 0; k < c.size(); k++){

                    c_cpy[k] = c[k];

                }


                c1_.push_back(c_cpy[i]);
                c_cpy.erase(c_cpy.begin() + i -1);

                c2_.push_back(c_cpy[j]);
                c_cpy.erase(c_cpy.begin() + j -1);


                int k = 0;
                double min_c1, min_c2;
                while(c_cpy.size()){
                    k = (k+1)%2;

                    int idx;

                    if(k){
                        min_c1 = DBL_MAX;


                        for(int h = 0; h < c_cpy.size(); h++){

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

                        for(int h = 0; h < c_cpy.size(); h++){

                            double d = dist(c[j], c_cpy[h]);

                            if(d < min_c2){

                                min_c2 = d;
                                idx = h;

                            }

                        }

                        c2_.push_back(c_cpy[idx]);


                    }

                    c_cpy.erase(c_cpy.begin() + idx - 1);

                }

                d.push_back(min_c1 > min_c2 ? min_c1 : min_c2); 
                c1.push_back(c1_);
                c2.push_back(c2_);

            }

        }

        double min = d[0];
        int idx = 0;

        for(int i = 1; i < d.size(); i++){

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


Entry* LeafOutput(std::vector<Point*> C_in){//newNode(entries)

    Point* g = medoid(C_in);
    double r = 0;
    std::vector<Entry*> C(C_in.size());

    for(int i = 0; i < C_in.size(); i++){

        r = std::max(r, dist(g, C_in[i]));

        C[i] = newEntry(C_in[i], -1, NULL);

    }

    return newEntry(g, r, newNode(C));

}


Entry* Output(std::vector<Entry*> C_mra){

    std::vector<Point*> C_in(C_mra.size());

    for(int i = 0; i < C_mra.size(); i++){

        C_in[i] = C_mra[i]->p;

    }

    Point* G = medoid(C_in);
    double R = 0;
    std::vector<Entry*> C(C_mra.size());

    for(int i = 0; i < C_mra.size(); i++){

        C[i] = C_mra[i];

        R = std::max(R, dist(G, C_mra[i]->p) + C_mra[i]->c_r);

    }

    return newEntry(G, R, newNode(C));

}


struct mtree* sexton_swinbank(std::vector<struct point*> C_in){

    if(C_in.size() <= B){

        Entry* e = LeafOutput(C_in);

        return newMTree(e);

    }

    std::vector<std::vector<Point*>> C_out = cluster(C_in);
    std::vector<Entry*> C; 

    for(int i = 0; i < C_out.size(); i++){

        C.push_back(LeafOutput(C_out[i]));

    }

    while(C.size() > B){

        std::vector<Point*> Medoids(C.size());
        std::vector<std::vector<Point*>> Clusters;

        for(int i = 0; i < C.size(); i++){

            Medoids[i] = C[i]->p;

        }

        Clusters = cluster(Medoids);
        std::vector<std::vector<Entry*>> C_mra(Clusters.size());

        for(int i = 0; i < Clusters.size(); i++){// i == c

            std::vector<Entry*> current(Clusters[i].size());

            for(int j = 0; j < Clusters[i].size(); j++){

                for(int k = 0; k < C.size(); k++){

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

        for(int i = 0; i < C_mra.size(); i++){

            C.push_back(Output(C_mra[i]));

        }

    }

    Entry *ret = Output(C);


    return newMTree(ret);

} 