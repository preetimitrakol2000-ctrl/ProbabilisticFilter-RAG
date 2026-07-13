#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT_ARRAY_SIZE 1024

typedef struct {
    unsigned char bits[BIT_ARRAY_SIZE];
} BloomFilter;

unsigned int hash_alpha(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % (BIT_ARRAY_SIZE * 8);
}

unsigned int hash_beta(const char* str) {
    unsigned int hash = 0;
    int c;
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash % (BIT_ARRAY_SIZE * 8);
}

#ifdef _WIN32
    __declspec(dllexport) BloomFilter* init_bloom_filter();
    __declspec(dllexport) void insert_metadata_key(BloomFilter* filter, const char* key);
    __declspec(dllexport) int test_metadata_key(BloomFilter* filter, const char* key);
#endif

BloomFilter* init_bloom_filter() {
    BloomFilter* filter = (BloomFilter*)malloc(sizeof(BloomFilter));
    memset(filter->bits, 0, BIT_ARRAY_SIZE);
    return filter;
}

void insert_metadata_key(BloomFilter* filter, const char* key) {
    unsigned int bit_a = hash_alpha(key);
    unsigned int bit_b = hash_beta(key);
    
    filter->bits[bit_a / 8] |= (1 << (bit_a % 8));
    filter->bits[bit_b / 8] |= (1 << (bit_b % 8));
}

int test_metadata_key(BloomFilter* filter, const char* key) {
    unsigned int bit_a = hash_alpha(key);
    unsigned int bit_b = hash_beta(key);
    
    int check_a = filter->bits[bit_a / 8] & (1 << (bit_a % 8));
    int check_b = filter->bits[bit_b / 8] & (1 << (bit_b % 8));
    
    return (check_a && check_b) ? 1 : 0;
}
