#include <bits/stdc++.h>
#include "./bloom/bloom.h"

std::chrono::time_point<std::chrono::system_clock> start;
long int N;
double P;

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

void main_in(int argc, char *argv[]){
    start = std::chrono::system_clock::now();

    if(argc < 3){
        std::fprintf(stderr, "Uso: make run N=\"{int}\" P=\"{double}\"\n");
        exit(-1);
    }

    N = std::atoi(argv[1]);

    P = std::atof(argv[2]);
}

void main_out(){
    std::cout << "> main exited after " << elapsed_time(start).first << std::endl;
}


int main(int argc, char *argv[]){

    main_in(argc, argv);

    std::vector<std::string> A = get_name_list(P, N);

    std::cout << "[";

    for(int i = 0; i < N; i++){
        if(i < N-1){std::cout << A[i] << ", ";}
        else{std::cout << A[i];}
        
    }

    std::cout << "]" << std::endl;

    std::cout << sec_search(A) << std::endl;

    main_out();

    return 0;
}