#ifndef INPUT_H
#define INPUT_H

#include "common.h"

struct WordsList
{
    const char **words  = NULL;
    size_t words_n      = 0;
    char *buf           = NULL;
    size_t buf_size     = 0;
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