#include "testing.h"
#include "hashtable.h"

#include <assert.h>
#include <math.h>
#include <string.h>

//! @brief Checks whether the output folder exists; creates it if needed.
inline void check_out_dir( const char *out_dir )
{
    mkdir( out_dir, DEFAULT_FILE_MODE );
}

//! @brief Computes variance of given hashtable's distribution.
// inline double compute_variance( Distribution distr ) //TODO - IN PYTHON
// {
//     size_t sum_x     = 0;
//     size_t sum_x_sqr = 0;
//     for (size_t i = 0; i < distr.size; i++)
//     {
//         size_t elem = distr.distr[i]; 
        
//         sum_x     += elem;
//         sum_x_sqr += elem*elem;
//     }

//     double mean_x     = (double) sum_x     / (double) distr.size;
//     double mean_x_sqr = (double) sum_x_sqr / (double) distr.size;

//     return mean_x_sqr - mean_x;
// }

inline void fill_filename( char *file_name, const char *out_dir, const char *func_name )
{
    assert(file_name);
    assert(out_dir);
    assert(func_name);

    strncpy( file_name, out_dir, FILENAME_LEN );
    
    size_t out_dir_name_len = strlen(out_dir);
    if (file_name[out_dir_name_len-1] != '/')
    {
        file_name[out_dir_name_len] = '/';
        out_dir_name_len++;
    }

    strncpy( file_name + out_dir_name_len, func_name, FILENAME_LEN - out_dir_name_len );
}

inline TestingStatus write_distr_into_file( Distribution distr, const char *out_dir, const char *func_name )
{
    assert(out_dir);
    assert(func_name);

    char file_name[FILENAME_LEN] = {};
    fill_filename(file_name, out_dir, func_name);
    
    FILE* file = fopen( file_name, "w" );
    if (!file)
        return TESTING_STATUS_ERR_CANT_CREATE_OUT_FILE;

    for ( size_t i = 0; i < distr.size; i++ )
    {
        fprintf( file, "%lu\n", distr.distr[i] );
    }

    fclose(file);

    return TESTING_STATUS_OK;
}

TestingStatus run_all_hash_func_tests( WordsList words_list, const char *out_dir, size_t ht_size )
{
    assert(out_dir);

    check_out_dir( out_dir );

    Distribution distr = {};
    TestingStatus status = Distribution_ctor( &distr, ht_size );
    if (status != TESTING_STATUS_OK)
        return status;

    
    for (size_t hash_func_ind = 0; hash_func_ind < HASH_FUNCS_COUNT; hash_func_ind++)
    {
        printf("Testing %s...\n", HASH_FUNCS_LIST[hash_func_ind].hash_func_name);
        run_hash_func_test( HASH_FUNCS_LIST[hash_func_ind].hash_func, words_list, &distr, ht_size );
        write_distr_into_file( distr, out_dir, HASH_FUNCS_LIST[hash_func_ind].hash_func_name );
        printf("Done!\n");
    }

    Distribution_dtor(&distr);
    return TESTING_STATUS_OK;
}

TestingStatus run_hash_func_test( hash_func_t hash_func, WordsList input, 
                                  Distribution *out_distr, size_t ht_size )
{
    assert(hash_func);
    assert(out_distr);

    Hashtable ht = {};
    HashtableStatus ht_status = hashtable_ctor( &ht, ht_size, hash_func );
    if (ht_status != HT_STATUS_OK)
        return TESTING_STATUS_ERR_HASHTABLE_INTERNAL_ERR;

    for (size_t i = 0; i < input.words_n; i++)
    {
        hashtable_insert( &ht, input.words[i] );
    }

    ht_status = hashtable_get_distribution( &ht, out_distr->distr );
    if ( ht_status != HT_STATUS_OK )
    {
        hashtable_dtor(&ht);
        return TESTING_STATUS_ERR_HASHTABLE_INTERNAL_ERR;
    }

    hashtable_dtor(&ht);

    return TESTING_STATUS_OK;
}

TestingStatus Distribution_ctor( Distribution *distr, size_t distr_size )
{
    assert(distr);

    free(distr->distr);

    distr->distr = (size_t*) calloc( distr_size, sizeof(size_t) );
    if (!distr->distr)
        return TESTING_STATUS_ERR_MEM_ALLOC;

    distr->size = distr_size;
    return TESTING_STATUS_OK;
}

void Distribution_dtor( Distribution *distr )
{
    assert(distr);

    free(distr->distr);
    distr->size = 0;
}