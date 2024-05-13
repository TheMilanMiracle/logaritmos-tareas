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


#define CP ciaccia_patella
#define SS sexton_swinbank

std::vector<int> S = {13};

std::ofstream results_file("./results_ss/results_"+std::to_string((int) S[0])+".txt");
// std::ofstream results_file("./results_.txt");

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

void main_in(){

    start = std::chrono::system_clock::now();

}

void main_out(){

    results_file << "> main finished after " << elapsed_time(start) << std::endl; 

    std::cout << "> main finished after " << elapsed_time(start) << std::endl; 

    results_file.close();
    
}


int main(){
    main_in();

    for(unsigned long int i = 0; i < S.size(); i++){
    
        results_file << "=====================================================================\n";

        results_file << "testing with " << (int)pow(2, S[i]) <<" points.\n\n";


        ref = std::chrono::system_clock::now();
        std::vector<Point*> P = generate_points(std::pow(2,S[i]));
        results_file << "> created " << (int)pow(2, S[i]) << " random points in " << elapsed_time(ref) << ".\n";


        ref = std::chrono::system_clock::now();
        MTree* A = SS(P);
        // MTree* A = CP(P);

        //std::cout << "H = "<< get_heigth(A) << std::endl;

        results_file << "> created a mtree with " << (int)pow(2, S[i]) << " random points ";
        results_file << "in " << elapsed_time(ref) << " with height " << std::to_string((int)get_heigthRec(A)) << ".\n";

        std::vector<Point*> Q = generate_points(100);
        double r = 0.02;
        // double r = 5;

        long int sum = 0;
        long int io = 0;

        for(int j = 0; j < 100; j++){

            ref = std::chrono::system_clock::now();
            std::vector<Point*> * R = searchTree(A, Q[j], r);
            
            results_file << "> found " << R->size() << "/" << (int)pow(2, S[i]);
            results_file << " points with Q:(" << Q[j]->x << ", "<< Q[j]->y <<") and r=" << r;
            results_file << " | I/O = " << get_simulated_reads() <<" | ";
            results_file << "in " << elapsed_time(ref) << ".\n";

            io += get_simulated_reads();
            sum += R->size();

        }

        results_file << "\npercentage of foundness "<< (double) sum / P.size() <<"% | avg I/O: "<< (double) io / 100 << "\n\n";

        results_file << "\n\n";
    }

    main_out();
}

