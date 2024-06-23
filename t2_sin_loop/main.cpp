#include <bits/stdc++.h>

#include "./graph/graph.h"

std::chrono::time_point<std::chrono::system_clock> start, ref1, ref2, ref;
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

std::ofstream results_file("./results_heap/v10e16.txt");

int main(){

    start = std::chrono::system_clock::now();

    std::vector<int> V = {10};
    std::vector<int> E = {18};

    for(int i = 0; i < V.size(); i++){

        for(int j = 0; j < E.size(); j++){

            // printf("(i, j) = (%d, %d)\n", i, j);



            // std::cout << "> grafo construido en " << elapsed_time(ref) << std::endl;

            // std::cout << "e*log(v) = " << (double) E[j] * std::log2(V[i]) << std::endl;
            // std::cout << "e+vlog(v) = " << (double) E[j] + (double) V[i] * std::log2(V[i]) << std::endl;

            // results_file << "=========================================================================================\n\n";
            // results_file << "V = " << V[i] << ", E = "<< E[j] << "\n";
        
            // for(int k = 0; k < 1; k++){

            //     ref = std::chrono::system_clock::now();

            //     Graph* G = makeGraph(V[i], E[j]);
            
            //     ref1 = std::chrono::system_clock::now();

            //     DijsktraHeap(*G, (*G->V)[0]);

            //     // std::cout << "> dijsktra con heap " << elapsed_time(ref1) << std::endl;
            //     results_file << elapsed_time(ref1) << "; ";

            //     if(k % 5 == 4){results_file << "\n";}

            //     destroyGraph(G);
            
            // }

            // results_file << "\n=========================================================================================";

            for(int k = 0; k < 1; k++){

                Graph* G = makeGraph(V[i], E[j]);  

                ref2 = std::chrono::system_clock::now();

                DijsktraFibHeap(*G, (*G->V)[0]);

                std::cout << "> dijsktra con fibonacci heap " << elapsed_time(ref2) << std::endl;

                destroyGraph(G);
            }


        }
    }

    std::cout << "> main finished in " << elapsed_time(start) << std::endl;


    return 0;

}


