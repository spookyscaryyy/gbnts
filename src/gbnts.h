#ifndef _GBNTS_H
#define _GBNTS_H

/* Includes */

/* Macros/Definitions */
#define PRINT_ALL_HELP      'a'
#define PRINT_COMMAND_HELP  'c'
#define PRINT_NOTE_HELP     'n'
#define PRINT_FOLDER_HELP   'f'

#define COMMAND_SPECIFIER   '-'

/* Data Structures */
typedef enum {
    LIST  = 0,
    ADD   = 1,
    REM   = 2,
    EDIT  = 3,
    HELP  = 4,
    TYPE  = 5,
    PRUN  = 6,
    NOCMD  = 101,

} CMD_ARG;

typedef enum {
    START,
    FAILED,
    SUCCESS,
    HELP_CMD,
    NORM_CMD,
    FOLDER_ADD,
    FOLDER_REMOVE,
    FOLDER_EDIT,
    FOLDER_EDIT_NAME,
    NOTE_CMD,
    NOTE_ADD,
    NOTE_ADD_TYPE,
    NOTE_REMOVE,
    NOTE_REMOVE_ID,
    NOTE_EDIT,
    NOTE_EDIT_ID,
    NOTE_EDIT_FIELD,
} PARSE;

typedef struct {
    PARSE state;
    CMD_ARG cmd;
    char* folder;
    char* type;
    char* field;
    int noteID;
    int noteIndex;
} PARSE_DATA;

/* Functions */

#endif
