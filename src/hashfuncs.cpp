#include "hashfuncs.h"

#include "string.h"

#define UNUSED(x) (x=x)

hash_t hash_const( const uint8_t *data, size_t data_size )
{
    UNUSED(data);
    UNUSED(data_size);
    return 19;
}

hash_t hash_first_letter_ascii( const uint8_t *data, size_t data_size )
{
    UNUSED(data_size);
    return (hash_t) *data;
}

hash_t hash_word_len( const uint8_t *data, size_t data_size )
{
    UNUSED(data);
    return data_size;
}

hash_t hash_checksum( const uint8_t *data, size_t data_size )
{
    hash_t res = 0;
    while ( data_size )
    {
        res += *data;
    }

    return res;
}

inline hash_t rol( hash_t hash )
{
    asm volatile( "rol %0, 1" 
                : "=r" (hash) 
                : "0" (hash) );
    
    return hash;
}


hash_t hash_rol_xor( const uint8_t *data, size_t data_size )
{
    hash_t hash = 0;
    for (size_t i = 0; i < data_size; i++)
    {
        hash = rol(hash);
        hash = hash ^ data[i];
    }

    return hash;
}

inline hash_t ror( hash_t hash )
{
    asm volatile( "ror %0, 1" 
                : "=r" (hash) 
                : "0" (hash) );
    
    return hash;
}

hash_t hash_ror_xor( const uint8_t *data, size_t data_size )
{
    hash_t hash = 0;
    for (size_t i = 0; i < data_size; i++)
    {
        hash = ror(hash);
        hash = hash ^ data[i];
    }

    return hash;
}