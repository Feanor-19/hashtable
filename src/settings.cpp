#include "settings.h"

#include <assert.h>

void parse_cmd_args( int argc, char **argv, Settings *settings )
{
    assert(argv);
    assert(settings);

    int c = 0;

    while (1)
    {
        // getopt_long stores the option index here
        int option_index = 0;

        c = getopt_long(argc, argv, "t", long_options, &option_index);

        // Detect the end of the options
        if (c == -1)
            break;

        switch (c)
        {
            case ID_INP_FILE:
                settings->inp_file = optarg;
                break;
            case ID_OUT_DIR:
                settings->out_dir = optarg;
                break;
            case ID_HASHTABLE_SIZE:
                if ( sscanf( optarg, SPECF_HASH_T, &settings->hash_table_size ) != 1)
                    printf( "--table-size has a bad argument <%s>, setting it to default\n", optarg );
                break;
            case '?':
                // getopt_long already printed an error message
                break;

            default:
                assert(0 && "Unreacheable line!");
        }
    }

    // Print any remaining command line arguments (not options).
    if (optind < argc)
    {
        printf ("Unrecognised options: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
        
}

SettingsStatus check_settings( const Settings *settings )
{
    // TODO удостовериться что существует входной файл (существование папки не требуется)

    return SETS_STATUS_OK;
}

void print_settings_error( SettingsStatus status )
{
    switch (status)
    {
    case SETS_STATUS_OK:
        assert(0 && "Unreacheable line!");
        break;
    case SETS_STATUS_ERROR_INP_FILE_DOES_NOT_EXIST:
        printf( "ERROR: given input file doesn't exist!\n" );
    default:
        break;
    }
}

void print_settings( const Settings *settings )
{
    printf( "Applied settings:\n"
            "\tInput file: %s\n"
            "\tOutput dir: %s\n"
            "\tHashtable's size: %lu\n",
            settings->inp_file,
            settings->out_dir,
            settings->hash_table_size);
}