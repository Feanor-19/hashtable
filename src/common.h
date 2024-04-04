#ifndef HASHTABLE_COMMON
#define HASHTABLE_COMMON

#include <stdint.h>
#include <stdio.h>

typedef uint64_t hash_t;
#define SPECF_HASH_T "%lu"


const uint64_t DEFAULT_HASH_TABLE_SIZE = 1119; // TODO поменять
const char const * DEFAULT_INP_FILE = "input.txt";
const char const * DEFAULT_OUT_DIR  = "out";


struct Settings
{
    const char *inp_file = DEFAULT_INP_FILE;
    const char *out_dir  = DEFAULT_OUT_DIR;
    uint64_t hash_table_size = DEFAULT_HASH_TABLE_SIZE;
};


#endif /* HASHTABLE_COMMON */