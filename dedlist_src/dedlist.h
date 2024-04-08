#ifndef DEDLIST_H
#define DEDLIST_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/*
    AVAILABLE DEFINES:

    DEDLIST_DO_DUMP
    DEDLIST_ABORT_ON_DUMP - requires DEDLIST_DO_DUMP
    DEDLIST_SHOW_DUMP_IMG - requires DEDLIST_DO_DUMP
*/
//#define DEDLIST_DO_DUMP
//#define DEDLIST_SHOW_DUMP_IMG

struct WordCount
{
    const char* word = NULL;
    uint64_t repeats = 0;
};

typedef WordCount Elem_t;
const Elem_t ELEM_T_DEFAULT_VALUE = { NULL, 0 };

#ifdef DEDLIST_DO_DUMP
inline void dedlist_print_elem_t(FILE *stream, Elem_t value)
{
    fprintf(stream, "%d", value);
}
#endif /* DEDLIST_DO_DUMP */

//------------------------------------------------------------------------------------------------------

typedef uint32_t dl_verify_res_t;

//------------------------------------------------------------------------------------------------------

#define DEF_STATUS_CODE(id, name, message) DEDLIST_STATUS_##name = id,
enum DedlistStatusCode
{
    #include "dedlist_status_codes.h"
};
#undef DEF_STATUS_CODE

#ifdef DEDLIST_DO_DUMP
#define DEF_VERIFY_FLAG(bit, name, message, cond) DEDLIST_VERIFY_##name = bit,
enum DedlistVerifyResFlag
{
    #include "dedlist_verify_flags.h"
};
#undef DEF_VERIFY_FLAG
#endif // DEDLIST_DO_DUMP

struct DedlistNode
{
    Elem_t data = ELEM_T_DEFAULT_VALUE;
    ptrdiff_t next = 0;
    ptrdiff_t prev = -1;
};

#ifdef DEDLIST_DO_DUMP
struct DedlistOrigInfo
{
    const char *dedlist_name = NULL;
    const char *dedlist_orig_file_name = NULL;
    int orig_line = -1;
    const char *orig_func_name = NULL;
};
#endif // DEDLIST_DO_DUMP

struct Dedlist
{
    DedlistNode *nodes = NULL;
    size_t capacity = 0;
    size_t size = 0;
    ptrdiff_t free = 0;

#ifdef DEDLIST_DO_DUMP
    DedlistOrigInfo orig_info = {};
#endif // DEDLIST_DO_DUMP
};

//------------------------------------------------------------------------------------------------------

#define DEF_STATUS_CODE(id, name, message) message,
const char* const dedlist_status_code_messages[] =
{
    #include "dedlist_status_codes.h"
    "FICTIONAL_MESSAGE!"
};
#undef DEF_STATUS_CODE

#ifdef DEDLIST_DO_DUMP
#define DEF_VERIFY_FLAG(bit, name, message, cond) #bit ": " message,
const char* const dedlist_verification_messages[] =
{
    #include "dedlist_verify_flags.h"
    "FICTIONAL_MESSAGE!"
};
#undef DEF_VERIFY_FLAG
#endif // DEDLIST_DO_DUMP

#ifdef DEDLIST_DO_DUMP
//! @brief Dump files will be stored in folder, specified by this path.
const char* const DEDLIST_DUMP_PATH = ".\\dumps\\";

const size_t DEDLIST_MAX_DUMP_PATH_LENGHT = 1024;

const size_t DEDLIST_MAX_CMD_GEN_DUMP_IMG_LENGHT = 1024;
#endif // DEDLIST_DO_DUMP

//------------------------------------------------------------------------------------------------------

DedlistStatusCode dedlist_ctor_( Dedlist *dedlist_ptr, size_t default_size
#ifdef DEDLIST_DO_DUMP
                                , DedlistOrigInfo orig_info
#endif
                                );

#ifdef DEDLIST_DO_DUMP

#define dedlist_ctor( dedlist_ptr, default_size ) dedlist_ctor_(    dedlist_ptr,            \
                                                                    default_size,           \
                                                                    {                       \
                                                                        #dedlist_ptr,       \
                                                                        __FILE__,           \
                                                                        __LINE__,           \
                                                                        __func__            \
                                                                    }                       \
                                                                )

#else // DEDLIST_DO_DUMP
#define dedlist_ctor(dedlist_ptr, default_size) dedlist_ctor_( dedlist_ptr, default_size )
#endif // DEDLIST_DO_DUMP


DedlistStatusCode dedlist_dtor( Dedlist *dedlist_ptr );

#ifdef DEDLIST_DO_DUMP
dl_verify_res_t dedlist_verify( Dedlist *dedlist_ptr );

void dedlist_dump_( Dedlist *dedlist_ptr,
                    dl_verify_res_t verify_res,
                    const char *file,
                    const int line,
                    const char *func );

#define DEDLIST_DUMP( dedlist_ptr, verify_res ) dedlist_dump_(  dedlist_ptr,        \
                                                                verify_res,         \
                                                                __FILE__,           \
                                                                __LINE__,           \
                                                                __func__ )          \

#define DEDLIST_SELFCHECK( dedlist_ptr ) {                              \
    dl_verify_res_t verify_res = dedlist_verify( dedlist_ptr );         \
    if ( verify_res != 0 )                                              \
    {                                                                   \
        DEDLIST_DUMP(dedlist_ptr, verify_res);                          \
        return DEDLIST_STATUS_ERROR_VERIFY;                             \
    }                                                                   \
}

#else // DEDLIST_DO_DUMP

#define DEDLIST_DUMP( dedlist_ptr, verify_res ) ((void) 0)

#define DEDLIST_SELFCHECK( dedlist_ptr ) ((void) 0)

#endif // DEDLIST_DO_DUMP

//! @brief call dedlist_func, returning DedlistStatusCode, and if
// returned code isn't OK, immediately returns it.
#define DL_WRP_RET(dedlist_func) {                              \
    DedlistStatusCode code = dedlist_func;                  \
    if (code != DEDLIST_STATUS_OK)                          \
        return code;                                        \
}

//! @brief call dedlist_func, returning DedlistStatusCode, and if
// returned code isn't OK, prints status code and returns void.
#define DL_WRP_PRINT(dedlist_func) {                        \
    DedlistStatusCode code = dedlist_func;                  \
    if (code != DEDLIST_STATUS_OK)                          \
    {                                                       \
        dedlist_print_status_code_message(code, stderr);    \
        return;                                             \
    }                                                       \
}

//! @brief Inserts value after element located at anchor.
//! Puts inserted element's anchor by the given pointer.
DedlistStatusCode dedlist_insert(   Dedlist *dedlist_ptr,
                                    size_t anchor,
                                    Elem_t value,
                                    size_t* inserted_elem_anchor_ptr = NULL);

DedlistStatusCode dedlist_change( Dedlist *dedlist_ptr, size_t anchor, Elem_t new_value );

DedlistStatusCode dedlist_delete( Dedlist *dedlist_ptr, size_t anchor );

DedlistStatusCode dedlist_get_by_anchor( Dedlist *dedlist_ptr, size_t anchor, Elem_t *ret);

DedlistStatusCode dedlist_get_head( Dedlist *dedlist_ptr, Elem_t *ret);

DedlistStatusCode dedlist_get_tail( Dedlist *dedlist_ptr, Elem_t *ret);

DedlistStatusCode dedlist_get_size( Dedlist *dedlist_ptr, size_t *ret );

size_t dedlist_get_next_anchor( Dedlist *dedlist_ptr, size_t curr_anchor );

size_t dedlist_get_prev_anchor( Dedlist *dedlist_ptr, size_t curr_anchor );

bool dedlist_is_head( Dedlist *dedlist, size_t anchor );

bool dedlist_is_tail( Dedlist *dedlist, size_t anchor );

DedlistStatusCode dedlist_push_head( Dedlist *dedlist_ptr,
                                     Elem_t value,
                                     size_t* inserted_elem_anchor_ptr = NULL);

DedlistStatusCode dedlist_push_tail(    Dedlist *dedlist_ptr,
                                        Elem_t value,
                                        size_t* inserted_elem_anchor_ptr = NULL);

DedlistStatusCode dedlist_delete_head( Dedlist *dedlist_ptr );

DedlistStatusCode dedlist_delete_tail( Dedlist *dedlist_ptr );

DedlistStatusCode dedlist_realloc_up_( Dedlist *dedlist_ptr );

DedlistStatusCode dedlist_shrink_to_fit_and_loose_anchors( Dedlist *dedlist_ptr );

void dedlist_print_status_code_message( DedlistStatusCode code, FILE *stream);

void init_zeroth_elem_( Dedlist *dedlist_ptr );

void init_free_elem_( Dedlist *dedlist_ptr, ptrdiff_t free_elem_ind );

void init_new_free_elems_( Dedlist *dedlist_ptr, ptrdiff_t start_with );

int is_node_free_( Dedlist *dedlist_ptr, size_t anchor );

void dedlist_print_verify_res_(FILE *stream, int verify_res);

size_t dedlist_get_head_ind( Dedlist *dedlist_ptr );

size_t dedlist_get_tail_ind( Dedlist *dedlist_ptr );

#endif
