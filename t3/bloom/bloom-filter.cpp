#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>
#include "./bloom.h"


BloomFilter *makeBloomFilter(long int M, int k){
    BloomFilter *bfilter = (BloomFilter*) malloc(sizeof(BloomFilter)); 
    
    bfilter->M = M;
    bfilter->k = k;

    size_t bytes = M / 8 + (M % 8 != 0);
    u_int8_t *bits = (u_int8_t*) malloc(bytes);
    memset(bits, 0, bytes);
    bfilter->bits = bits;

    std::srand((unsigned int)(std::time(NULL)));
    bfilter->H = new std::function<std::size_t(std::string)>[k];
    for(int i = 0; i < k; i++){

        std::size_t seed = std::rand();
        bfilter->H[i] = [seed](std::string x){
            std::size_t hash = boost::hash<std::string>{}(x);
            boost::hash_combine(hash, seed);
            return hash;
        };
    }
    
    return bfilter;
}

void bloomInsert(BloomFilter *filter, std::string x){
    for(int h = 0; h < filter->k; h++){
        int idx = (filter->H)[h](x) % filter->M;

        (filter->bits)[(int)idx/8] |= (1 << (7 - idx%8));
        // std::cout << idx << "(" << idx/8 << ", " << idx%8 << ")\t";
    }
    // std::cout << std::endl;
}

bool bloomLook(BloomFilter *filter, std::string x){
    for(int h = 0; h < filter->k; h++){
        int idx = filter->H[h](x) % filter->M;

        if( !(filter->bits[(int)idx/8] & (1 << (7 - idx%8))) ){
            // std::cout << idx << "(" << idx/8 << ", " << idx%8 << ")\t";
            return false;
        }
        // std::cout << std::endl;
        
    }

    return true;
}

void destroyBloomFilter(BloomFilter *filter){
    free(filter->bits);
    free(filter);
}