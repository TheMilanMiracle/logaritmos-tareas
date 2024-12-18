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


std::ofstream results_file("./results.txt"); // archivo de salida para los resultados

std::vector<double> S; // vector para las cantidades puntos
MTree* (*F)(std::vector<Point*>); // puntero a una función de construcción de un MTree

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

void main_in(int argc, char *argv[]){

    if(argc < 3){

        std::cout << "insuficientes argumentos" << std::endl;

        std::fprintf(stderr, "Uso: make run method=\"{ss/cp}\" test=\"{1 2 3 ...}\"\n");
        std::exit(1);

    }

    if(strcmp(argv[1], "cp") == 0){

        F = &ciaccia_patella;

    }
    else if(strcmp(argv[1],"ss") == 0){

        F = &sexton_swinbank;

    }
    else{

        std::cout << "método de construcción desconocido" << std::endl;

        std::fprintf(stderr, "Uso: make run method=\"{ss/cp}\" test=\"{1 2 3 ...}\"\n");
        std::exit(1);

    }

    for(int i = 2; i < argc; i++){

        S.push_back(std::pow(2, atoi(argv[i])));

    }

    start = std::chrono::system_clock::now();

}

void main_out(){

    results_file << "> main finished after " << elapsed_time(start) << std::endl; 

    std::cout << "> main finished after " << elapsed_time(start) << std::endl; 

    results_file.close();
    
}

int main(int argc, char *argv[]){

    main_in(argc, argv);

    for(unsigned long int i = 0; i < S.size(); i++){

        results_file << "=====================================================================\n";

        results_file << "testing with " << (int)S[i] <<" points.\n\n";

        // generación de puntos aleatorios para la construcción de un M Tree
        ref = std::chrono::system_clock::now();
        std::vector<Point*> P = generate_points(S[i]);
        results_file << "> created " << (int)S[i] << " random points in " << elapsed_time(ref) << ".\n";

        // construcción de un M Tree
        ref = std::chrono::system_clock::now();
        MTree* A = F(P);
        results_file << "> created a mtree with " << (int)S[i] << " random points ";
        results_file << "in " << elapsed_time(ref) << " with height " << std::to_string((int)get_heigthRec(A)) << ".\n";

        // generación de puntos para las consultas al M Tree construido
        std::vector<Point*> Q = generate_points(100);
        double r = 0.02;

        long int sum = 0;
        long int io = 0;

        // se hacen las consultas
        for(int j = 0; j < 100; j++){

            ref = std::chrono::system_clock::now();
            std::vector<Point*> * R = searchTree(A, Q[j], r); // búsqueda en el M Tree
            
            results_file << "> found " << R->size() << "/" << (int)S[i];
            results_file << " points with Q:(" << Q[j]->x << ", "<< Q[j]->y <<") and r=" << r;
            results_file << " | I/O = " << get_simulated_reads() <<" | ";
            results_file << "in " << elapsed_time(ref) << ".\n";

            io += get_simulated_reads(); // simulated reads retorna la cantidad de accesos a bloques de memoria simulados de esta búsqueda
            sum += R->size();

        }

        results_file << "\navg percentage of points found: "<< (double) sum / P.size() <<"% | avg I/O: "<< (double) io / 100 << "\n\n\n";

    }

    main_out();

    return 0;

}