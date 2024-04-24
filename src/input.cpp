#include "input.h"

#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <memory.h>

//! @brief Writes file's size into size_ptr. If error occurs,
// corresponding status code is returned.
inline WordsListStatus get_file_size(const char *file_name, size_t *size_ptr)
{
    assert(file_name);

    struct stat st_buf = {};
    if ( stat(file_name, &st_buf) == -1)
        return WL_STATUS_ERR_CANT_GET_FILE_SIZE;

    *size_ptr = (size_t) st_buf.st_size;
    return WL_STATUS_OK;
}

//! @brief Creates and fills wl->words with pointers onto 
//! words' beginnings, stored in wl->buf.
inline WordsListStatus fill_words ( WordsList *wl )
{
    assert(wl);

    // counting number of words
    size_t words_n = 1;
    for (size_t i = 0; i < wl->buf_size; i++)
    {
        if ( wl->buf[i] == '\n' )
            words_n++;
    }

    wl->words = (const char **) calloc( words_n + 2, sizeof( const char * ) );
    if (!wl->words)
        return WL_STATUS_ERR_MEM_ALLOC;

    // filling wl->words
    wl->words[0] = wl->buf;
    size_t curr_word = 1;
    for (size_t i = 0; i < wl->buf_size; i++)
    {
        if ( wl->buf[i] == '\n' )
        {
            wl->buf[i] = '\0';
            wl->words[curr_word++] = wl->buf + i + 1;
        }
    }

    wl->words_n = words_n;
    
    return WL_STATUS_OK;
}

inline WordsListStatus fill_words_aligned( WordsList *wl )
{
    assert(wl);

    wl->words_aligned = (__m256i*) aligned_alloc( sizeof(__m256i), wl->words_n * sizeof(__m256i) );
    if ( !wl->words_aligned )
        return WL_STATUS_ERR_MEM_ALLOC;

    memset( wl->words_aligned, 0, wl->words_n * sizeof(__m256i) );

    for (size_t i = 0; i < wl->words_n; i++)
    {
        memcpy( wl->words_aligned + i, wl->words[i], strlen(wl->words[i]) );
        //NOTE - это можно сделать чуть хитрее и не вызывать strlen, но
        // данный сценарий не требует оптимизации загрузки таблицы
    }

    return WL_STATUS_OK;
}

WordsListStatus WordsList_ctor( WordsList *wl, const char *inp_filename )
{
    assert( wl );
    assert( inp_filename );

    WordsListStatus status = WL_STATUS_OK;

    size_t file_size = 0;
    if ( (status = get_file_size( inp_filename, &file_size ) ) != WL_STATUS_OK )
    {
        return status;
    }

    FILE *file_ptr = fopen( inp_filename, "rb" );
    if ( !file_ptr )
    {
        return WL_STATUS_ERR_FILE_NOT_FOUND;
    }

    char *data = (char *) calloc( file_size + 1, sizeof(char) );
    if (!data)
    {
        fclose(file_ptr);
        return WL_STATUS_ERR_MEM_ALLOC;
    }

    size_t data_size = fread( data, sizeof(char), file_size, file_ptr );
    if ( ferror(file_ptr) != 0 )
    {
        free( data );
        fclose(file_ptr);
        return WL_STATUS_ERR_CANT_OPEN_FILE;
    }

    fclose(file_ptr);

    wl->buf = data;
    wl->buf_size = data_size;
    status = fill_words( wl );
    if (status != WL_STATUS_OK)
        return status;

    status = fill_words_aligned( wl );
    if (status != WL_STATUS_OK)
        return status;

    return WL_STATUS_OK;
}

void WordsList_dtor( WordsList *wl )
{
    assert( wl );

    free(wl->words_aligned);
    wl->words_aligned = NULL;

    free(wl->words);
    wl->words = NULL;

    free(wl->buf);
    wl->buf = NULL;
    
    wl->words_n = 0;
}