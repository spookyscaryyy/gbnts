#ifndef _GBNTS_H
#define _GBNTS_H

/* Includes */

/* Macros/Definitions */
#define PRINT_ALL_HELP      'a'
#define PRINT_COMMAND_HELP  'c'
#define PRINT_NOTE_HELP     'n'
#define PRINT_FOLDER_HELP   'f'

#define COMMAND_SPECIFIER   '-'
#define LIST_COMMAND        0
#define ADD_COMMAND         1
#define REMOVE_COMMAND      2
#define EDIT_COMMAND        3
#define HELP_COMMAND        4
#define TYPE_COMMAND        5
#define PRUNE_COMMAND       6

/* Data Structures */
typedef enum {
    LIST  = 0,
    ADD   = 1,
    REM   = 2,
    EDIT  = 3,
    HELP  = 4,
    TYPE  = 5,
    PRUN  = 6,
    NAME  = 100,
    BAD   = 101,
    FOLD  = 102,

} CMD_ARG;

/* Functions */

#endif
