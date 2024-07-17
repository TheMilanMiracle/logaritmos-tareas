#ifndef __BLOOM_H__
#define __BLOOM_H__

// sample construction
std::pair<std::vector<std::string>, std::vector<std::string>> get_name_list(double p, long int N);


// bloom filter
typedef struct {
    long int M;
    u_int8_t *bits;
    int k, (**H)(std::string);
} BloomFilter;

BloomFilter *makeBloomFilter(long int M, int k, int (**H)(std::string));
void bloomInsert(BloomFilter *filter, std::string x);
bool bloomLook(BloomFilter *filter, std::string x);
void destroyBloomFilter(BloomFilter *filter);


// search
long int sec_search(std::string str);

#endif