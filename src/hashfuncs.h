#ifndef HASHFUNCS_H
#define HASHFUNCS_H

#include "common.h"

hash_t hash_const( const uint8_t *data, size_t data_size );

hash_t hash_first_letter_ascii( const uint8_t *data, size_t data_size );

hash_t hash_word_len( const uint8_t *data, size_t data_size );

hash_t hash_checksum( const uint8_t *data, size_t data_size );

hash_t hash_rol_xor( const uint8_t *data, size_t data_size );

hash_t hash_ror_xor( const uint8_t *data, size_t data_size );

#endif /* HASHFUNCS_H */