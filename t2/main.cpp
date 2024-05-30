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

    Graph* G = makeGraph(18, 22);

    std::cout << "> grafo construido en " << elapsed_time(ref) << std::endl;

    ref = std::chrono::system_clock::now();

    DijsktraHeap(*G, (*G->V)[0]);

    std::cout << "> dijsktra con heap " << elapsed_time(ref) << std::endl;

    // ref = std::chrono::system_clock::now();

    // DijsktraFibHeap(*G, (*G->V)[0]);

    // std::cout << "> dijsktra con fibonacci heap " << elapsed_time(ref) << std::endl;


    return 0;

}


