#include "hashtable.h"
#include "hashfuncs.h"

#include <assert.h>
#include <string.h>
#include <immintrin.h>

inline HashtableStatus init_HashtableElem( HashtableElem *ht_elem )
{
    assert(ht_elem);

    ht_elem->words = ( __m256i* ) aligned_alloc( sizeof( __m256i ), 
                                                 HT_DEFAULT_ELEM_ARRAY_LEN*sizeof(__m256i) );
    if ( !ht_elem->words )
        return HT_STATUS_ERROR_MEM_ALLOC;

    memset( ht_elem->words, 0, HT_DEFAULT_ELEM_ARRAY_LEN*sizeof(__m256i) );

    ht_elem->repeats = ( uint32_t* ) calloc( HT_DEFAULT_ELEM_ARRAY_LEN, sizeof(uint32_t) );
    if ( !ht_elem->repeats )
        return HT_STATUS_ERROR_MEM_ALLOC;
    
    ht_elem->curr_capacity = HT_DEFAULT_ELEM_ARRAY_LEN;

    return HT_STATUS_OK;
}

inline void deinit_HashtableElem( HashtableElem *ht_elem )
{
    assert(ht_elem);

    free(ht_elem->words);
    free(ht_elem->repeats);

    ht_elem->curr_capacity = 0;
}

HashtableStatus hashtable_ctor( Hashtable *ht, size_t ht_size, hash_func_t hash_func )
{
    assert(ht);
    assert(hash_func);
    assert(ht_size > 0);

    if (ht->table || ht->size || ht->hash_func)
        return HT_STATUS_ERROR_ATTEMPT_TO_CTOR_NON_EMPTY;

    ht->table = (HashtableElem *) calloc( ht_size, sizeof(HashtableElem) );
    if (!ht->table)
        return HT_STATUS_ERROR_MEM_ALLOC;

    ht->size        = ht_size;
    ht->hash_func   = hash_func;

    HashtableStatus ht_status = HT_STATUS_OK;
    for (size_t ind = 0; ind < ht_size; ind++)
    {
        ht_status = init_HashtableElem( &ht->table[ind] );
        if (ht_status != HT_STATUS_OK)
            return ht_status;
    }

    return ht_status;
}

HashtableStatus hashtable_dtor( Hashtable *ht )
{
    assert(ht);

    for ( size_t ind = 0; ind < ht->size; ind++ )
    {
        deinit_HashtableElem( &ht->table[ind] );
    }

    free(ht->table);
    ht->size = 0;
    ht->hash_func = NULL;

    return HT_STATUS_OK;
}

//! @brief Returns true if given blocks are equal, false otherwise.
inline bool opt_256_memcmp( __m256i a, __m256i b )
{
    __m256i cmp_res = _mm256_cmpeq_epi8( a, b );
    int mask = _mm256_movemask_epi8( cmp_res );
    return ((uint) mask == 0xFFFFFFFF);
}

//! @brief Returns index of wordcount with given 'word',
//! or -1 if such a wordcount is not found in the 'dedlist'
inline int find_wordcount( HashtableElem *ht_elem, const __m256i *search_word_aligned )
{
    assert(ht_elem);
    assert(search_word_aligned);

    for ( size_t ind = 0; ind < ht_elem->curr_capacity; ind++ )
    {
        if ( opt_256_memcmp( ht_elem->words[ind], *search_word_aligned ) )
            return (int) ind;
    }

    return -1;
}

//! @brief Returns true if given word is free (empty).
//! @attention THIS FUNCTION CONSIDERS THAT EMPTY WORD BEGINS
//! WITH ZERO-CHAR ('\0')!
inline bool is_word_free( const __m256i *word )
{
    return *((const char*) word) == 0;
}

//! @brief My (silly) implementation of aligned realloc.
//! @attention DON'T USE IF YOU DONT UNDERSTAND HOW SILLTY THIS IMPLEMENTATION IS!
inline void* realloc_aligned( size_t alignment, void *ptr, size_t old_size, size_t new_size )
{
    assert(ptr);
    assert(old_size);
    assert(new_size);

    void *new_mem = aligned_alloc(alignment, new_size);
    if ( !new_mem )
        return NULL;

    memcpy( new_mem, ptr, old_size );

    free(ptr);

    return new_mem;
}

inline HashtableStatus realloc_HashtableElem( HashtableElem *ht_elem )
{
    assert(ht_elem);

    size_t old_cap = ht_elem->curr_capacity;
    size_t new_cap = old_cap * 2;
    assert(new_cap != 0);

    ht_elem->words = ( __m256i* ) realloc_aligned( sizeof(__m256i), ht_elem->words, 
                                                   old_cap*sizeof(__m256i),
                                                   new_cap*sizeof(__m256i) );
    if ( !ht_elem->words )
        return HT_STATUS_ERROR_MEM_ALLOC;

    ht_elem->repeats = ( uint32_t* ) realloc( ht_elem->repeats, new_cap*sizeof(uint32_t) );
    if ( !ht_elem->repeats )
        return HT_STATUS_ERROR_MEM_ALLOC;

    ht_elem->curr_capacity = new_cap;   

    return HT_STATUS_OK; 
}

//! @brief Appends given element in the first from the left free "words" element
//! and sets corresponding element in "repeats" to 1.
inline HashtableStatus ht_elem_append( HashtableElem *ht_elem, const __m256i *word )
{
    assert(ht_elem);
    assert(word);

    for ( size_t ind = 0; ind < ht_elem->curr_capacity; ind++ )
    {
        if ( is_word_free( &ht_elem->words[ind] ) )
        {
            ht_elem->words  [ind] = *word;
            ht_elem->repeats[ind] = 1;
            return HT_STATUS_OK;
        }
    }

    // array is full, time to realloc
    size_t old_cap = ht_elem->curr_capacity;
    HashtableStatus ht_status = realloc_HashtableElem( ht_elem );
    if ( ht_status != HT_STATUS_OK )
        return ht_status;

    //placing in the first free elem
    ht_elem->words  [old_cap] = *word;
    ht_elem->repeats[old_cap] = 1;
    return HT_STATUS_OK;
}

HashtableStatus hashtable_insert( Hashtable *ht, const __m256i *word )
{
    assert(ht);

    hash_t hash = ht->hash_func( (const uint8_t*)word, sizeof( *word ) );
    hash = hash % ht->size;

    HashtableElem *ht_elem = &ht->table[hash];

    int list_ind = find_wordcount( ht_elem, word );
    HashtableStatus ht_status = HT_STATUS_OK;
    if (list_ind == -1)
    {
        ht_status = ht_elem_append( ht_elem, word );
    }
    else
    {
        (ht_elem->repeats[list_ind])++;
    }

    return ht_status;
}

uint64_t hashtable_find( Hashtable *ht, const __m256i *word )
{
    assert(ht);
    assert(word);

    hash_t hash = hash_murmur3( (const uint8_t*)word, sizeof(*word) );

    hash = hash % DEFAULT_HASH_TABLE_SIZE;

    HashtableElem *ht_elem = &ht->table[hash];

    int list_ind = find_wordcount( ht_elem, word );
    if (list_ind == -1)
    {
        return 0;
    }
    else
    {
        return ht_elem->repeats[list_ind];
    }
}

inline size_t get_ht_elem_len( const HashtableElem *ht_elem )
{
    assert(ht_elem);

    for ( size_t ind = 0; ind < ht_elem->curr_capacity; ind++ )
    {
        if ( is_word_free( &ht_elem->words[ind] ) )
            return ind;
    }

    return ht_elem->curr_capacity;
}

HashtableStatus hashtable_get_distribution( Hashtable *ht, size_t *distr )
{
    assert(ht);

    for (hash_t hash = 0; hash < ht->size; hash++)
    {
        distr[hash] = get_ht_elem_len( &ht->table[hash] );
    }

    return HT_STATUS_OK;
}