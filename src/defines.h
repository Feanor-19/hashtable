#ifndef DEFINES_H
#define DEFINES_H

#ifndef _DEBUG
#define NDEBUG
#endif

#include <stdlib.h>
#include <stdint.h>
#include <immintrin.h>


typedef uint64_t hash_t;
typedef hash_t (*hash_func_t)(const uint8_t *data, size_t data_size);
#define SPECF_HASH_T "%lu"


struct WordCount
{
    const __m256i* word = NULL;
    uint32_t repeats = 0;
};

typedef WordCount Elem_t;
const Elem_t ELEM_T_DEFAULT_VALUE = { NULL, 0 };

const size_t DEFAULT_NUM_OF_ITERS     = 150;  

#endif /* DEFINES_H */