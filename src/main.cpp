#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "hashfuncs.h"
#include "hashtable.h"
#include "input.h"
#include "testing.h"

#include <string.h>

int main(int argc, char **argv)
{
    Settings settings = {};
    parse_cmd_args(argc, argv, &settings);
    SettingsStatus settings_status = check_settings( &settings );
    if (settings_status != SETS_STATUS_OK)
    {
        print_settings_error( settings_status );
        exit(settings_status);
    }
    print_settings( &settings );

    // ---------------------------------------------------------------

    WordsList words_list = {};
    WordsListStatus wl_status = WordsList_ctor( &words_list, settings.inp_file );
    if ( wl_status != WL_STATUS_OK )
    {
        printf( "ERROR: Something went wrong during reading input file. "
                "TestingStatus value: %d.\n", wl_status);
        WordsList_dtor(&words_list);
        exit(wl_status);
    }

    if ( settings.test_search )
    {
        WordsList search_list = {};
        WordsListStatus sl_status = WordsList_ctor( &search_list, settings.search_file );
        if ( sl_status != WL_STATUS_OK )
        {
            printf( "ERROR: Something went wrong during reading search file. "
                    "TestingStatus value: %d.\n", sl_status);
            WordsList_dtor(&search_list);
            exit(sl_status);
        }

        run_search_perf_test( words_list, search_list, settings.hash_table_size );
        WordsList_dtor( &search_list );
    }
    else
    {
        // Testing hash-funcs' distributions.

        TestingStatus t_status = run_all_hash_func_tests( words_list, settings.out_dir, settings.hash_table_size );
        if ( t_status != TESTING_STATUS_OK )
        {
            printf("ERROR: Something went wrong during testing. TestingStatus value: %d.\n", t_status);
            WordsList_dtor(&words_list); // REVIEW - странный вопрос: а нужно ли морочиться с освобождением памяти,
                                        // если мы все равно завершаемся уже?
            exit(t_status);
        }
    }

    WordsList_dtor( &words_list );
}