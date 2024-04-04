#include <stdio.h>
#include <stdlib.h>

#include "settings.h"

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


}