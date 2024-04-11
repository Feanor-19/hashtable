#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "hashfuncs.h"
#include "hashtable.h"
#include "input.h"
#include "testing.h"

// - Входной файл должен состоять из слов, содержащих только английские буквы, каждое на своей строке
// - значения дисперсий печатаются в stdout
// - всегда тестятся все хэш-фии, нет возможности задать конкретные
// - задается размер хэш-таблицы, по умолчанию тот, который хорошо подходит для итоговых данных
// - задается директория (обязательно с '/' в конце!!!), в которой будут
// созданы файлы для каждой хэш-фии, содержащие распределение заполненности хэш-таблицы (для гистограмм)

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

    TestingStatus t_status = run_all_hash_func_tests( words_list, settings.out_dir, settings.hash_table_size );
    if ( t_status != TESTING_STATUS_OK )
    {
        printf("ERROR: Something went wrong during testing. TestingStatus value: %d.\n", t_status);
        WordsList_dtor(&words_list); // REVIEW - странный вопрос: а нужно ли морочиться с освобождением памяти,
                                     // если мы все равно завершаемся уже?
        exit(t_status);
    }

    WordsList_dtor( &words_list );
}