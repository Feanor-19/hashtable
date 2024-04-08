#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "common.h"


enum HashtableStatus
{
    HT_STATUS_OK,
    HT_STATUS_ERROR_MEM_ALLOC,
    HT_STATUS_ERROR_ATTEMPT_TO_CTOR_NON_EMPTY,
    HT_STATUS_ERROR_DEDLIST_INTERNAL_ERROR,
};


struct Hashtable
{
    Dedlist *table  = NULL;
    size_t size     = 0;

    hash_func_t hash_func = NULL;
};

HashtableStatus hashtable_ctor( Hashtable *ht, size_t ht_size, hash_func_t hash_func );

HashtableStatus hashtable_dtor( Hashtable *ht );

HashtableStatus hashtable_insert( Hashtable *ht, const char *word );

//! @brief Fills given array 'distr' (which must have size equal to hashtable's size)
//! with lenghts of corresponding lists.
HashtableStatus hashtable_get_distribution( Hashtable *ht, size_t *distr );

#endif /* HASHTABLE */