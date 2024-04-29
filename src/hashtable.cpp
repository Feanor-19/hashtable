#include "hashtable.h"
#include "hashfuncs.h"

#include <assert.h>
#include <string.h>
#include <immintrin.h>

HashtableStatus hashtable_ctor( Hashtable *ht, size_t ht_size, hash_func_t hash_func )
{
    assert(ht);
    assert(hash_func);
    assert(ht_size > 0);

    if (ht->table || ht->size || ht->hash_func)
        return HT_STATUS_ERROR_ATTEMPT_TO_CTOR_NON_EMPTY;

    ht->table = (HashtableElem *) aligned_alloc( sizeof(__m256i), ht_size*sizeof(HashtableElem) );
    if (!ht->table)
        return HT_STATUS_ERROR_MEM_ALLOC;

    ht->size        = ht_size;
    ht->hash_func   = hash_func;

    return HT_STATUS_OK;
}

HashtableStatus hashtable_dtor( Hashtable *ht )
{
    assert(ht);

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

    for ( size_t ind = 0; ind < HT_ELEM_ARRAY_LEN; ind++ )
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

//! @brief Appends given element in the first from the left free "words" element
//! and sets corresponding element in "repeats" to 1.
inline HashtableStatus ht_elem_append( HashtableElem *ht_elem, const __m256i *word )
{
    assert(ht_elem);
    assert(word);

    for ( size_t ind = 0; ind < HT_ELEM_ARRAY_LEN; ind++ )
    {
        if ( is_word_free( &ht_elem->words[ind] ) )
        {
            ht_elem->words  [ind] = *word;
            ht_elem->repeats[ind] = 1;
            return HT_STATUS_OK;
        }
    }
    return HT_STATUS_ERROR_HT_ELEM_LIST_IS_FULL;
}

HashtableStatus hashtable_insert( Hashtable *ht, const __m256i *word )
{
    assert(ht);

    hash_t hash = hash_murmur3( (const uint8_t*)word, sizeof( *word ) );
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

inline uint8_t get_ht_elem_len( const HashtableElem *ht_elem )
{
    assert(ht_elem);

    for ( uint8_t ind = 0; ind < HT_ELEM_ARRAY_LEN; ind++ )
    {
        if ( is_word_free( &ht_elem->words[ind] ) )
            return ind;
    }

    return 0xFF;
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