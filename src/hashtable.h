#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "common.h"


enum HashtableStatus
{
    HT_STATUS_OK,
    HT_STATUS_ERROR_MEM_ALLOC,
    HT_STATUS_ERROR_ATTEMPT_TO_CTOR_NON_EMPTY,
    HT_STATUS_ERROR_HT_ELEM_LIST_IS_FULL,
};

//! @attention MUST BE BIGGER THAN MAX LOAD FACTOR FOR SPECIFIC INPUT!
const uint8_t HT_ELEM_ARRAY_LEN = 16;

struct HashtableElem
{
    __m256i    words[HT_ELEM_ARRAY_LEN] = {};
    uint32_t repeats[HT_ELEM_ARRAY_LEN] = {};
};

struct Hashtable
{
    HashtableElem *table  = NULL;
    size_t size           = 0;

    hash_func_t hash_func = NULL;
};

HashtableStatus hashtable_ctor( Hashtable *ht, size_t ht_size, hash_func_t hash_func );

HashtableStatus hashtable_dtor( Hashtable *ht );

HashtableStatus hashtable_insert( Hashtable *ht, const __m256i *word );

//! @brief Finds given word in the hashtable and returns its number of repeats.
//! If the word isn't found in the hashtable, 0 is returned.
uint64_t hashtable_find( Hashtable *ht, const __m256i *word );

//! @brief Fills given array 'distr' (which must have size equal to hashtable's size)
//! with lenghts of corresponding lists.
HashtableStatus hashtable_get_distribution( Hashtable *ht, size_t *distr );

#endif /* HASHTABLE */