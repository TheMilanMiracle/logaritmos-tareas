#include <bits/stdc++.h>

#include "./graph/graph.h"

std::vector<int> V; // vector para la cantidades de vertices
std::vector<int> E; // vector para las cantidades de aristas
int N; // numero de experimentos

void (*D)(Graph, Vertex*); // puntero a la función de dijsktra de la respectiva estructura

std::chrono::time_point<std::chrono::system_clock> start, ref1;
std::pair<std::string, double> elapsed_time(std::chrono::time_point<std::chrono::system_clock> from){

    std::chrono::duration<double> time = std::chrono::system_clock::now() - from;

    double s, m, h;
    if((int) time.count()/60 >= 1){

        if((int) ((int) time.count()/60) / 60 >= 1){

            s = time.count();
            m = (double) s/60;
            h = (double) m/60;

            return {std::to_string(h) + " hours | (" + std::to_string(m) + " minutes)", s};

        }
        else{

            s = time.count();
            m = (double) s/60;


            return {std::to_string(m) + " minutes | (" + std::to_string(s) + " seconds)", s}; 
            

        }

    }
    else{

        s = time.count();

        return {std::to_string(s) + " seconds", s}; 

    }

}

std::ofstream results_file("./results.txt");
void main_in(int argc, char *argv[]){
    if(!*argv[1] || !*argv[2] || !*argv[3] || !*argv[4]){
        std::cout << "insuficientes argumentos" << std::endl;
        std::fprintf(stderr, "Uso: make run structure=\"{heap/fib}\" v=\"{10 12 14 ...}\" e=\"{16 17 18 ...}\" n=\"{int}\"\n");
        std::exit(1);
    }

    std::string argv1(argv[1]);
    if(argv1 == "heap"){D = &DijsktraFibHeap;}
    else if(argv1 == "fib"){D = &DijsktraFibHeap;}
    else{
        std::cout << "estructura inválida" << std::endl;
        std::fprintf(stderr, "Uso: make run structure=\"{heap/fib}\" v=\"{10 12 14 ...}\" e=\"{16 17 18 ...}\" n=\"{int}\"\n");
        std::exit(1);
    }

    int i = 0, j = 0;
    std::string argv2(argv[2]);
    for(char c : argv2){
        if(c == ' '){
            V.push_back(std::stoi(argv2.substr(j, i)));
            j += i;
            i = 1;
        }
        else{
            i++;
        }
    }
    V.push_back(std::stoi(argv2.substr(j, i)));

    i = 0; j = 0;
    std::string argv3(argv[3]);
    for(char c : argv3){
        if(c == ' '){
            E.push_back(std::stoi(argv3.substr(j, i)));
            j += i;
            i = 1;
        }
        else{
            i++;
        }
    }
    E.push_back(std::stoi(argv3.substr(j, i)));

    std::string argv4(argv[4]);
    N = std::stoi(argv4);
    
}

int main(int argc, char *argv[]){

    start = std::chrono::system_clock::now();

    main_in(argc, argv);

    for(int i = 0; i < V.size(); i++){
        for(int j = 0; j < E.size(); j++){
            double total_time = 0.0;

            results_file << "=========================================================================================\n\n";
            results_file << "===\t\t\tV = " << V[i] << ", E = "<< E[j] << "\t\t\t===\n\n";
        
            for(int k = 0; k < N; k++){
                Graph *G = makeGraph(V[i], E[j]); // se construye el grafo para el experimento k
            
                ref1 = std::chrono::system_clock::now(); //tiempo antes de ijsktra

                D(*G, (*G->V)[0]);

                std::pair<std::string, double> time = elapsed_time(ref1);  //tiempo después de Dijsktra

                total_time += time.second;

                results_file << time.first << "; ";

                if(k % 5 == 4){results_file << "\n";}

                destroyGraph(G); // de destruye el grafo
            }

            results_file << "\n===\t\tavg time = "<< (double) total_time / N << "\t\t===\n";
            results_file << "\n=========================================================================================\n";
        }
    }

    std::cout << "> main finished in " << elapsed_time(start).first << std::endl;

    results_file.close();

    return 0;

}


