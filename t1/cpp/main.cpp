#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <chrono>
#include <unistd.h>    
#include "./mtree/mtree.h"

std::ofstream results_file("./cp_results/results.txt");

std::chrono::time_point<std::chrono::system_clock> start, ref;

std::vector<double> S = {std::pow(2, 9)};

std::string elapsed_time(std::chrono::time_point<std::chrono::system_clock> from){

    std::chrono::duration<double> time = std::chrono::system_clock::now() - start;

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

void main_in(){

    start = std::chrono::system_clock::now();

}

void main_out(){

    results_file << "> main finished after " << elapsed_time(start) << std::endl; 

    std::cout << "> main finished after " << elapsed_time(start) << std::endl; 
    
}


int main(){
    main_in();


    for(unsigned long int i = 0; i < S.size(); i++){
    
        results_file << "=====================================================================\n";

        results_file << "testing with " << (int)S[i] <<" points.\n\n";


        ref = std::chrono::system_clock::now();
        std::vector<Point*> P = generate_points(S[i]);
        results_file << "> created " << (int)S[i] << " random points in " << elapsed_time(ref) << ".\n";


        ref = std::chrono::system_clock::now();
        // MTree* A = sexton_swinbank(P);
        MTree* A = ciaccia_patella(P);
        results_file << "> created a mtree with " << (int)S[i] << " random points in " << elapsed_time(ref) << ".\n";

        std::vector<Point*> Q = generate_points(100);
        double r = 0.02;

        long int sum = 0;
        long int io = 0;

        for(int j = 0; j < 100; j++){

            ref = std::chrono::system_clock::now();
            std::vector<Point*> * R = searchTree(A, Q[j], r);
            
            results_file << "> found " << R->size() << "/" << (int)S[i];
            results_file << " points with Q:(" << Q[j]->x << ", "<< Q[j]->y <<") and r=" << r;
            results_file << " | I/O = " << get_simulated_reads() <<".\n";

            io += get_simulated_reads();
            sum += R->size();

        }

        results_file << "\npercentage of foundness "<< (double) sum / P.size() <<"% | avg I/O: "<< (double) io / 100 << "\n\n";

        results_file << "\n\n";
    }

    results_file.close();


    main_out();
}

