#include <bits/stdc++.h>

#include "./graph/graph.h"

std::chrono::time_point<std::chrono::system_clock> start, ref;
std::string elapsed_time(std::chrono::time_point<std::chrono::system_clock> from){

    std::chrono::duration<double> time = std::chrono::system_clock::now() - from;

    double s, m, h;
    if((int) time.count()/60 >= 1){

        if((int) ((int) time.count()/60) / 60 >= 1){

            s = time.count();
            m = (double) s/60;
            h = (double) m/60;

            return std::to_string(h) + " hours | (" + std::to_string(m) + " minutes)";

        }
        else{

            s = time.count();
            m = (double) s/60;


            return std::to_string(m) + " minutes | (" + std::to_string(s) + " seconds)"; 
            

        }

    }
    else{

        s = time.count();

        return std::to_string(s) + " seconds"; 

    }

}


int main(){

    ref = std::chrono::system_clock::now();

    unsigned long int v = 14;
    unsigned long int e = 20;

    Graph* G = makeGraph(v, e);

    std::cout << "> grafo construido en " << elapsed_time(ref) << std::endl;

    std::cout << "e*log(v) = " << (double) e * std::log2(v) << std::endl;
    std::cout << "e+vlog(v) = " << (double) e + (double) v * std::log2(v) << std::endl;
 
    ref = std::chrono::system_clock::now();

    DijsktraHeap(*G, (*G->V)[0]);

    std::cout << "> dijsktra con heap " << elapsed_time(ref) << std::endl;


    ref = std::chrono::system_clock::now();

    DijsktraFibHeap(*G, (*G->V)[0]);

    std::cout << "> dijsktra con fibonacci heap " << elapsed_time(ref) << std::endl;


    return 0;

}


