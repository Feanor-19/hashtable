#ifndef INPUT_H
#define INPUT_H

#include "common.h"

#include <immintrin.h>

struct WordsList
{
    char *buf           = NULL; //< buf as read from file (only '\n' -> '\0')
    size_t buf_size     = 0;

    const char **words  = NULL; //< pointers to words' first chars in 'buf' 
    size_t words_n      = 0;

    __m256i *words_aligned = NULL; //< stores copies of words in blocks
                                   //TODO - нужен ли '\0' в конце таких блоков?
    //NOTE - 'words_aligned' size equals 'words_n'.
};

enum WordsListStatus
{
    WL_STATUS_OK,
    WL_STATUS_ERR_FILE_NOT_FOUND,
    WL_STATUS_ERR_MEM_ALLOC,
    WL_STATUS_ERR_CANT_GET_FILE_SIZE,
    WL_STATUS_ERR_CANT_OPEN_FILE,
};

//! @brief In the given file each word must be on its own line.
WordsListStatus WordsList_ctor( WordsList *wl, const char *inp_filename );

void WordsList_dtor( WordsList *wl );

#endif /* INPUT_H */