#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "hashfuncs.h"
#include "hashtable.h"

// - Входной файл должен состоять из слов, содержащих только английские буквы, каждое на своей строке
// - значения дисперсий печатаются в stdout
// - всегда тестятся все хэш-фии, нет возможности задать конкретные
// - задается размер хэш-таблицы, по умолчанию тот, который хорошо подходит для итоговых данных
// - задается директория (можно с '/' в конце, можно без, оба варианта должны обрабатываться), в которой будут
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

    Hashtable ht = {};
    hashtable_ctor( &ht, 20, hash_const );

    hashtable_insert( &ht, "hello" );
    hashtable_insert( &ht, "word" );
    hashtable_insert( &ht, "hello" );
    hashtable_insert( &ht, "aaa" );
    hashtable_insert( &ht, "aaa" );

    size_t distr[20] = {};
    hashtable_get_distribution( &ht, distr );
    for (int i = 0; i < 20; i++)
    {
        printf("%lu ", distr[i]);
    }
    printf("\n");

    hashtable_dtor( &ht );
}