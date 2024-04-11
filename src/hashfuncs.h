#ifndef HASHFUNCS_H
#define HASHFUNCS_H

#include "common.h"

hash_t hash_const( const uint8_t *data, size_t data_size );

hash_t hash_first_letter_ascii( const uint8_t *data, size_t data_size );

hash_t hash_word_len( const uint8_t *data, size_t data_size );

hash_t hash_checksum( const uint8_t *data, size_t data_size );

hash_t hash_rol_xor( const uint8_t *data, size_t data_size );

hash_t hash_ror_xor( const uint8_t *data, size_t data_size );



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
    { hash_ror_xor,             "hash_ror_xor" }
};

const size_t HASH_FUNCS_COUNT = sizeof(HASH_FUNCS_LIST)/sizeof(HASH_FUNCS_LIST[0]);

#endif /* HASHFUNCS_H */