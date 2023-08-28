#ifndef _GBNTS_H
#define _GBNTS_H

/* Includes */

/* Macros/Definitions */
#define PRINT_ALL_HELP      'a'
#define PRINT_COMMAND_HELP  'c'
#define PRINT_NOTE_HELP     'n'
#define PRINT_FOLDER_HELP   'f'

#define COMMAND_LIST_SIZE   6
#define LIST_COMMAND        0
#define ADD_COMMAND         1
#define REMOVE_COMMAND      2
#define EDIT_COMMAND        3
#define HELP_COMMAND        4
#define PRUNE_COMMAND       5

/* Data Structures */
typedef enum {
    ls = 0,
    a  = 1,
    r  = 2,
    e  = 3,
    h  = 4,
    t  = 5,
    p  = 6
} CMD_ARG;

/* Functions */

#endif
