#ifndef HASHTABLE_COMMON
#define HASHTABLE_COMMON

#include "defines.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t hash_t;
typedef hash_t (*hash_func_t)(const uint8_t *data, size_t data_size);
#define SPECF_HASH_T "%lu"


const uint64_t DEFAULT_HASH_TABLE_SIZE  = 10271; // NOTE - for Les Miserables Vol 1
const char * const DEFAULT_INP_FILE     = "texts/input.txt";
const char * const DEFAULT_SEARCH_FILE  = "texts/search.txt";
const char * const DEFAULT_OUT_DIR      = "out";

const size_t DEFAULT_DEDLIST_SIZE = 15;

struct Settings
{
    const char *inp_file    = DEFAULT_INP_FILE;
    const char *search_file = DEFAULT_SEARCH_FILE;
    const char *out_dir     = DEFAULT_OUT_DIR;
    uint64_t hash_table_size = DEFAULT_HASH_TABLE_SIZE;

    bool test_search = false;
};


#endif /* HASHTABLE_COMMON */