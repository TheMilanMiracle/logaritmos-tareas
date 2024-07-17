#include <bits/stdc++.h>
#include "./bloom.h"

BloomFilter *makeBloomFilter(long int M, int k, int (**H)(std::string)){
    BloomFilter *bfilter = (BloomFilter*) malloc(sizeof(BloomFilter)); 
    
    size_t bytes = M / 8 + (M % 8 != 0);
    u_int8_t *bits = (u_int8_t*) malloc(bytes);
    memset(bits, 0, bytes);

    bfilter->M = M;
    bfilter->bits = bits;
    bfilter->k = k;
    bfilter->H = H;

    return bfilter;
}

void bloomInsert(BloomFilter *filter, std::string x){
    for(int h = 0; h < filter->k; h++){
        int idx = (filter->H)[h](x) % filter->M;

        (filter->bits)[(int)idx/8] |= (1 << (7 - idx%8));
        // cout << idx << "(" << idx/8 << ", " << idx%8 << ")\t";
    }
    // cout << endl;
}

bool bloomLook(BloomFilter *filter, std::string x){
    for(int h = 0; h < filter->k; h++){
        int idx = filter->H[h](x) % filter->M;

        if( !(filter->bits[(int)idx/8] & (1 << (7 - idx%8))) ){
            // cout << idx << "(" << idx/8 << ", " << idx%8 << ")\t";
            return false;
        }
        // cout << endl;
        
    }

    return true;
}

void destroyBloomFilter(BloomFilter *filter){
    free(filter->bits);
    free(filter);
}