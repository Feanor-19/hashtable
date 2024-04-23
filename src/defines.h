#ifndef DEFINES_H
#define DEFINES_H

#ifndef _DEBUG
#define NDEBUG
#endif

#include <stdlib.h>
#include <stdint.h>
#include <immintrin.h>

struct WordCount
{
    const __m256i* word = NULL;
    uint32_t repeats = 0;
};

typedef WordCount Elem_t;
const Elem_t ELEM_T_DEFAULT_VALUE = { NULL, 0 };

#endif /* DEFINES_H */