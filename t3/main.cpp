#include <bits/stdc++.h>
#include "./bloom/bloom.h"


std::chrono::time_point<std::chrono::system_clock> start, ref;
long int N, M, K;
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
        fprintf(stderr, "Uso: make run N=\"{int}\" P=\"{double}\" M=\"{int}\" K=\"{int}\"\n");
        exit(-1);
    }

    N = std::pow(2, atoi(argv[1]));

    M = std::pow(2, atoi(argv[2]));

    K = atoi(argv[3]);
}

void main_out(){
    std::cout << "> main exited after " << elapsed_time(start).first << std::endl;
}

std::ofstream results_file("./results.txt");

int main(int argc, char *argv[]){

    std::vector<float> P = {0.0, 1.0/4.0, 1.0/2.0, 3.0/4.0, 1.0};

    main_in(argc, argv);

    for(float p : P){
        results_file << "=========================================================================================\n\n";
        results_file << "\tN = "<< N << "\tp = "<< p << "\tM = " << M << "\tk = "<< K << "\n\n"; 

        std::pair<std::vector<std::string>, std::vector<std::string>> pair = get_name_list(p, N);

        std::vector<std::string> Names = pair.first, Films = pair.second;

        BloomFilter *filter = makeBloomFilter(M, K);

        for(std::string s : Names){
            bloomInsert(filter, s);
        }

        int loops = 1;

        double total_time = 0.0; 
        for(int i = 0; i < loops; i++){
            ref = std::chrono::system_clock::now();
            
            for(std::string s : Names){
                sec_search(s);
            }
            for(std::string s : Films){
                sec_search(s);
            }

            total_time += elapsed_time(ref).second;
        }
        
        results_file << "Time for search without filter = " << (double) total_time / loops << "\n\n";
        
        total_time = 0.0; 
        int total_fp = 0;
        for(int i = 0; i < loops; i++){
            long int fake_positives = 0;
            ref = std::chrono::system_clock::now();

            for(std::string s : Names){
                if(bloomLook(filter, s)){sec_search(s);}
            }
            for(std::string s : Films){
                if(bloomLook(filter, s)){
                    sec_search(s);
                    fake_positives++;
                }
            }

            total_fp += fake_positives;
            total_time += elapsed_time(ref).second;
        }

        results_file << "Time for search with filter = " << (double) total_time / loops << "\n";
        results_file << "Fake positives = " << (double) total_fp / loops << "\n";
        results_file << "Error = " << ((double) ((double) total_fp / loops) / N) * 100.0 << "%\n\n";

        destroyBloomFilter(filter);
    }

    results_file << "=========================================================================================";

    main_out();

    return 0;
}