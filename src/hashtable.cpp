#include "hashtable.h"

#include <assert.h>
#include <string.h>

HashtableStatus hashtable_ctor( Hashtable *ht, size_t ht_size, hash_func_t hash_func )
{
    assert(ht);
    assert(hash_func);
    assert(ht_size > 0);

    if (ht->table || ht->size || ht->hash_func)
        return HT_STATUS_ERROR_ATTEMPT_TO_CTOR_NON_EMPTY;

    ht->table = (Dedlist *) calloc( ht_size, sizeof(Dedlist) );
    if (!ht->table)
        return HT_STATUS_ERROR_MEM_ALLOC;

    ht->size        = ht_size;
    ht->hash_func   = hash_func;

    DedlistStatusCode ded_code = DEDLIST_STATUS_OK;
    for (hash_t i = 0; i < ht_size; i++)
    {
        ded_code = dedlist_ctor( &ht->table[i], DEFAULT_DEDLIST_SIZE );
        if (ded_code != DEDLIST_STATUS_OK)
            break;
    }    

    if (ded_code != DEDLIST_STATUS_OK)
    {
        for (hash_t i = 0; i < ht_size; i++)  
            dedlist_dtor( &ht->table[i] );
        
        return HT_STATUS_ERROR_DEDLIST_INTERNAL_ERROR;
    }

    return HT_STATUS_OK;
}

HashtableStatus hashtable_dtor( Hashtable *ht )
{
    assert(ht);

    if (ht->table)
    {
        for (hash_t i = 0; i < ht->size; i++)  
            dedlist_dtor( &ht->table[i] );
    }

    free(ht->table);
    ht->size = 0;
    ht->hash_func = NULL;

    return HT_STATUS_OK;
}

//! @brief Returns index (anchor) of wordcount with given 'word',
//! or -1 if such a wordcount is not found in the 'dedlist'
inline int find_wordcount( Dedlist *dedlist, const char *word )
{
    size_t list_size = 0;
    dedlist_get_size( dedlist, &list_size );
    if ( list_size == 0 )
        return -1;

    size_t curr = dedlist_get_head_ind( dedlist );

    do
    {
        WordCount wc = {};
        dedlist_get_by_anchor(dedlist, curr, &wc);

        if ( strcmp( word, wc.word ) == 0 )
            return (int) curr;

        curr = dedlist_get_prev_anchor( dedlist, curr );
    } while ( curr != 0 );
    
    return -1;
}

HashtableStatus hashtable_insert( Hashtable *ht, const char *word )
{
    assert(ht);

    hash_t hash = ht->hash_func( (const uint8_t*)word, strlen(word) );
    hash = hash % ht->size;

    Dedlist *dedlist_ptr = &ht->table[hash];

    int list_ind = find_wordcount( dedlist_ptr, word );
    if (list_ind == -1)
    {
        dedlist_push_head( dedlist_ptr, { word, 1 } );
    }
    else
    {
        WordCount curr_wc = {};

        dedlist_get_by_anchor( dedlist_ptr, (size_t) list_ind, &curr_wc );
        dedlist_change( dedlist_ptr, (size_t) list_ind, {curr_wc.word, curr_wc.repeats + 1} );
    }

    return HT_STATUS_OK;
}

HashtableStatus hashtable_get_distribution( Hashtable *ht, size_t *distr )
{
    assert(ht);

    for (hash_t hash = 0; hash < ht->size; hash++)
    {
        distr[hash] = ht->table[hash].size;
    }

    return HT_STATUS_OK;
}