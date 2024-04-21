#ifndef SETTINGS_H
#define SETTINGS_H

#include "common.h"

#include <getopt.h>

enum LongOptionsIds
{
    ID_TEST_SEARCH      = 't', 
    ID_INP_FILE         = 'i',
    ID_OUT_DIR          = 'o',
    ID_HASHTABLE_SIZE   = 's',
};

const char * const SHORT_OPTIONS = "t::i:o:s:";

struct option const long_options[] = 
{
    {"test-search", optional_argument, 0, ID_TEST_SEARCH    },
    {"input",       required_argument, 0, ID_INP_FILE       },
    {"output",      required_argument, 0, ID_OUT_DIR        },
    {"table-size",  required_argument, 0, ID_HASHTABLE_SIZE },
    {0, 0, 0, 0}
};

enum SettingsStatus
{
    SETS_STATUS_OK,
    SETS_STATUS_ERROR_INP_FILE_DOES_NOT_EXIST,
};


void parse_cmd_args( int argc, char **argv, Settings *settings );

SettingsStatus check_settings( const Settings *settings );

void print_settings_error( SettingsStatus status );

void print_settings( const Settings *settings );

#endif /* SETTINGS_H */