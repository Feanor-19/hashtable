#ifndef DEFINES_H
#define DEFINES_H

#ifndef _DEBUG
#define NDEBUG
#endif

#define NDEBUG

#include <stdlib.h>
#include <stdint.h>

struct WordCount
{
    const char* word = NULL;
    uint32_t repeats = 0;
};

typedef WordCount Elem_t;
const Elem_t ELEM_T_DEFAULT_VALUE = { NULL, 0 };

#endif /* DEFINES_H */