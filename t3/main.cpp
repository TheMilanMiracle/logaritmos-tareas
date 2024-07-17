#include <bits/stdc++.h>
#include "./bloom/bloom.h"

int simpleHash(std::string str) {
    int hash = 0;
    for (char ch : str) {
        hash += ch;
    }
    return sqrt(pow(hash, 2));
}

int djb2Hash(std::string str) {
    int hash = 5381;
    for (char ch : str) {
        hash = ((hash << 5) + hash) + ch; // hash * 33 + ch
    }
    return sqrt(pow(hash, 2));
}

int fnv1aHash(std::string str) {
    int hash = 14695981039346656037ULL;
    for (char ch : str) {
        hash ^= static_cast<size_t>(ch);
        hash *= 1099511628211ULL;
    }
    return sqrt(pow(hash, 2));
}


void printBinary(unsigned int num) {
    int numBits = sizeof(u_int8_t) * 8;
    int mask = 1 << (numBits - 1);

    for (int i = 0; i < numBits; i++) {
        printf("%d", (num & mask) ? 1 : 0);
        num <<= 1;
    }
}

void printBits(BloomFilter *filter){
    for(int i = 0; i < filter->M / 8; i++){
        printBinary((filter->bits)[i]);
    }
    printf("\n");
}


std::chrono::time_point<std::chrono::system_clock> start, ref;
long int N, M;
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
        fprintf(stderr, "Uso: make run N=\"{int}\" P=\"{double}\"\n");
        exit(-1);
    }

    N = atoi(argv[1]);

    P = atof(argv[2]);

    M = atoi(argv[3]);
}

void main_out(){
    std::cout << "> main exited after " << elapsed_time(start).first << std::endl;
}


int main(int argc, char *argv[]){

    main_in(argc, argv);

    std::pair<std::vector<std::string>, std::vector<std::string>> pair = get_name_list(P, N);

    std::vector<std::string> Names = pair.first, Films = pair.second;

    int (*H[3])(std::string) = {simpleHash, djb2Hash, fnv1aHash};

    BloomFilter *filter = makeBloomFilter(M, 3, H);

    for(std::string s : Names){
        bloomInsert(filter, s);
    }

    ref = std::chrono::system_clock::now();
    for(std::string s : Names){
        sec_search(s);
    }
    for(std::string s : Films){
        sec_search(s);
    }
    
    std::cout << "Search without filter ended after " << elapsed_time(ref).first << std::endl;

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

    std::cout << "Search without filter ended after " << elapsed_time(ref).first << std::endl;
    std::cout << "\twith "<< fake_positives <<" fake positives (error=" << ((double)fake_positives/N) * 100.0<< "%)" << std::endl;

    main_out();

    return 0;
}