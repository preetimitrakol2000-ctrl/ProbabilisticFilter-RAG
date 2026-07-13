#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

typedef struct BloomFilter BloomFilter;
BloomFilter* init_bloom_filter();
void insert_metadata_key(BloomFilter* filter, const char* key);
int test_metadata_key(BloomFilter* filter, const char* key);

#endif
