#ifndef HASHFUNCS_H
#define HASHFUNCS_H

#include "common.h"


#define UNUSED(x) (x=x)


hash_t hash_const( const uint8_t *data, size_t data_size );

hash_t hash_first_letter_ascii( const uint8_t *data, size_t data_size );

hash_t hash_word_len( const uint8_t *data, size_t data_size );

hash_t hash_checksum( const uint8_t *data, size_t data_size );

hash_t hash_rol_xor( const uint8_t *data, size_t data_size );

hash_t hash_ror_xor( const uint8_t *data, size_t data_size );

hash_t hash_murmur3( const uint8_t *data, size_t data_size );


#include <nmmintrin.h>
inline hash_t hash_crc32( const uint8_t *data, size_t data_size )
{
    UNUSED(data_size);

    uint32_t hash = 0;
    asm ( "xor %0, %0\n"
          "crc32 %0, DWORD PTR [%1]"
          : "=r" (hash)
          : "r" (data) );

    return (hash_t) hash;
}


struct HashFuncDef
{
    hash_func_t hash_func       = NULL;
    const char *hash_func_name  = NULL;
};

const HashFuncDef HASH_FUNCS_LIST[] = 
{
    { hash_const,               "hash_const" },
    { hash_first_letter_ascii,  "hash_first_letter_ascii" },
    { hash_word_len,            "hash_word_len" },
    { hash_checksum,            "hash_checksum" },
    { hash_rol_xor,             "hash_rol_xor" },
    { hash_ror_xor,             "hash_ror_xor" },
    { hash_murmur3,             "hash_murmur3" }
};

const size_t HASH_FUNCS_COUNT = sizeof(HASH_FUNCS_LIST)/sizeof(HASH_FUNCS_LIST[0]);

#undef UNUSED

#endif /* HASHFUNCS_H */