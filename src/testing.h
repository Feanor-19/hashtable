#ifndef TESTING_H
#define TESTING_H

#include "common.h"
#include "input.h"
#include "hashfuncs.h"

#include <sys/types.h>
#include <sys/stat.h>


enum TestingStatus
{
    TESTING_STATUS_OK,
    TESTING_STATUS_ERR_MEM_ALLOC,
    TESTING_STATUS_ERR_HASHTABLE_INTERNAL_ERR,
    TESTING_STATUS_ERR_CANT_CREATE_OUT_FILE,
    TESTING_STATUS_ERR_CANT_OPEN_DIR,
};

struct Distribution
{
    size_t *distr = NULL;
    size_t size   = 0;
};


const mode_t DEFAULT_FILE_MODE = 0777;
const size_t FILENAME_LEN      = 100;

const hash_func_t PERF_TEST_HASH_FUNC = hash_murmur3;
const size_t DEFAULT_NUM_OF_ITERS     = 150;  


//! @brief Loads given 'input' into a hashtable of given 'ht_size', which uses 
//! specified 'hash_func', and then returns the resulting distribution (in 'out_distr').
//! @attention 'out_distr' must be an already allocated array of size 'ht_size'! 
TestingStatus run_hash_func_test( hash_func_t hash_func, WordsList input, 
                                  Distribution *out_distr, size_t ht_size );

//! @brief Runs tests for all hash funcs, writing resulting distriburions in files
//! in the specified directory 'out_dir'.
TestingStatus run_all_hash_func_tests( WordsList words_list, const char *out_dir, size_t ht_size );

TestingStatus Distribution_ctor( Distribution *distr, size_t distr_size );

void Distribution_dtor( Distribution *distr );

//! @brief Inserts all words from 'words_list' into a hashtable of size 'ht_size', and then patiently 
//! searches for every word from 'search_list' in it.
TestingStatus run_search_perf_test( WordsList words_list, WordsList search_list, size_t ht_size );

#endif /* TESTING_H */