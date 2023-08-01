/* C Includes */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* Project Includes */
#include "gbnts.h"
#include "scodes.h"
#include "utils.h"
#include "folders.h"
#include "notes.h"

/* Globals */
const char* COMMAND_LIST[] =
{"-ls", "-a", "-r", "-e", "-h", "-t", "-p"};

void showFolderHelp()
{
    printf("gbnts [folder cmd] {folder args}\n"
            "folder cmds:\n"
            "    ls - lists all available folders\n"
            "    a  - creates a new folder with a given name\n"
            "    r  - removes a folder by it's ID or name\n"
            "    e  - edit a folder's name by it's ID or name\n");
}

void showNoteHelp()
{
    printf("gbnts [folder name] {note cmd}\n"
            "note cmds:\n"
            "    ls - lists all notes in folder, also if no note cmd given\n"
            "    a  - creates a new note with it's given fields\n"
            "    r  - removes a note by it's ID\n"
            "    e  - edit a note by it's ID\n");
}

void showCommandHelp()
{
    printf("gbnts [cmd] {help}\n"
            "cmds:\n"
            "    h  - shows all help or the selected help\n"
            "    t  - lists all possible note types and their fields\n"
            "    p  - removes all empty folders\n");
}

void showHelp(uint8_t which)
{
    switch(which)
    {
        case(PRINT_COMMAND_HELP):
            printf("Showing command help menu\n");
            showCommandHelp();
            break;
        case(PRINT_NOTE_HELP):
            printf("Showing note help menu\n");
            showNoteHelp();
            break;
        case(PRINT_FOLDER_HELP):
            printf("Showing folder help menu\n");
            showFolderHelp();
            break;
        case(PRINT_ALL_HELP):
        default:
            printf("Showing full help menu\n");
            showCommandHelp();
            printf("\n");
            showFolderHelp();
            printf("\n");
            showNoteHelp();
            break;
    }
}

CMD_ARG detCommand(const char* ARG)
{
    /* look through each command and try to find which this is */
    for (int i = 0; i < ARR_SIZE(COMMAND_LIST); i++)
    {
        /* selected command matches argument */
        if (0 == strcmp(COMMAND_LIST[i], ARG))
        {
            return (CMD_ARG)i;
        }
    }

    /* whatever it is, it is not a command */
    return NOCMD;
}

SCODE handleStartState(PARSE_DATA* data, const char* ARG)
{
    SCODE status = SCODE_OK;
    /* if this is a folder than we are dealing with a note command */
    if (isFolder(ARG))
    {
        NEWN(data->folder, strlen(ARG)+1);
        strcpy(data->folder, ARG);
        data->state = NOTE_CMD;
        return status;
    }

    /* either one of the normal commands, folder command, or invalid */
    switch(data->cmd)
    {
        case(HELP):
            data->state = HELP_CMD;
            break;
        case(ADD):
            data->state = FOLDER_ADD;
            break;
        case(REM):
            data->state = FOLDER_REMOVE;
            break;
        case(EDIT):
            data->state = FOLDER_EDIT;
            break;
        case(TYPE):
        case(PRUN):
        case(LIST):
            data->state = NORM_CMD;
            break;
        case(NOCMD):
            status = ENCODE(GBNTS_MAIN, UNRECOGNIZED_COMMAND);
            data->state = FAILED;
            break;
    }
    return status;
}

SCODE handleLeftovers(PARSE_DATA* data)
{
    SCODE status = SCODE_OK;
    if (!data)
    {
        return ENCODE(GBNTS_MAIN, NULL_POINTER_DEREF);
    }

    /* some commands utilize a leftover state */
    if (HELP_CMD == data->state)
    {
        showHelp(PRINT_ALL_HELP);
    }
    else if (NORM_CMD == data->state && TYPE == data->cmd)
    {
        showNoteTypes();
    }
    else if (NORM_CMD == data->state && PRUN == data->cmd)
    {
        status = pruneFolders();
    }
    else if (NORM_CMD == data->state && LIST == data->cmd)
    {
        showFolders();
    }
    else if (NOTE_CMD == data->state)
    {
        showNotes(data->folder);
    }
    else if (data->noteIndex > 0)
    {
        addFolder(data->folder);
    }
    return status;
}

SCODE singleParseLoop(PARSE_DATA* data, const char* ARG)
{
    SCODE status = SCODE_OK;
    data->cmd = detCommand(ARG);

    /* argument parse state machine */
    switch(data->state)
    {
        case(START):
            status = handleStartState(data, ARG);
            break;
        case(HELP_CMD):
            showHelp(ARG[0]);
            data->state = SUCCESS;
            break;
        case(NORM_CMD):
            status = ENCODE(GBNTS_MAIN, TOO_MANY_ARGS);
            data->state = FAILED;
            break;

        case(NOTE_CMD):
            switch(data->cmd)
            {
                case(ADD):
                    data->state = NOTE_ADD;
                    break;
                case(REM):
                    data->state = NOTE_REMOVE;
                    break;
                case(EDIT):
                    data->state = NOTE_EDIT;
                    break;
                case(LIST):
                    showNotes(data->folder);
                    data->state = SUCCESS;
                    break;
                default:
                    status = ENCODE(GBNTS_MAIN, UNRECOGNIZED_NOTE_COMMAND);
                    data->state = FAILED;
            }
            break;

        case(NOTE_ADD):
            NEWN(data->type, strlen(ARG)+1);
            strcpy(data->type, ARG);
            data->state = NOTE_ADD_TYPE;
            break;
        case(NOTE_ADD_TYPE):
            data->noteIndex = 1;
            data->state = SUCCESS;
            break;

        case(NOTE_REMOVE):
            data->noteID = atoi(ARG);
            data->state = NOTE_REMOVE_ID;
            break;
        case(NOTE_REMOVE_ID):
            status = removeNote(data->folder, data->noteID);
            data->state = SUCCESS;
            break;

        case(NOTE_EDIT):
            data->noteID = atoi(ARG);
            data->state = NOTE_EDIT_ID;
            break;
        case(NOTE_EDIT_ID):
            NEWN(data->field, strlen(ARG)+1);
            strcpy(data->field, ARG);
            data->state = NOTE_EDIT_FIELD;
            break;
        case(NOTE_EDIT_FIELD):
            status = editNote(data->noteID, data->field, ARG);
            data->state = SUCCESS;
            break;

        case(FOLDER_ADD):
            status = addFolder(ARG);
            data->state = SUCCESS;
            break;

        case(FOLDER_REMOVE):
            status = removeFolder(ARG);
            data->state = SUCCESS;
            break;

        case(FOLDER_EDIT):
            NEWN(data->folder, strlen(ARG)+1);
            strcpy(data->folder, ARG);
            data->state = FOLDER_EDIT_NAME;
            break;
        case(FOLDER_EDIT_NAME):
            status = editFolder(data->folder, ARG);
            data->state = SUCCESS;
            break;

        case(SUCCESS):
        case(FAILED):
            // do nothing
            break;
    }
    return status;
}

SCODE argumentParse(int argc, char** argv)
{
    SCODE status = SCODE_OK;

    /* variables used in parsing */
    PARSE_DATA dat;
    dat.state = START;
    dat.cmd = NOCMD;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;

    /* argument parse loop */
    for (int i = 1; i < argc; i++)
    {
        const char* ARG = argv[i];
        singleParseLoop(&dat, ARG);
    }

    status = handleLeftovers(&dat);

    /* DEL handles if they were never allocated */
    DEL(dat.folder);
    DEL(dat.type);
    DEL(dat.field);
    return status;
}

int main(int argc, char** argv)
{
    SCODE status = SCODE_OK;

    /* print help if there was no arguments given */
    if (1 == argc)
    {
        showHelp(PRINT_ALL_HELP);
        return handleScode(status);
    }
    status = argumentParse(argc, argv);

    return handleScode(status);
}
