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
    for (int i = 0; i < ARR_SIZE(COMMAND_LIST); i++)
    {
        if (0 == strcmp(COMMAND_LIST[i], ARG))
        {
            return (CMD_ARG)i;
        }
    }
    return NOCMD;
}

void handleStartState(SCODE* status, PARSE* state,
        CMD_ARG cmd, char* folder, const char* ARG)
{
    if (isFolder(ARG))
    {
        NEWN(folder, strlen(ARG)+1);
        strcpy(folder, ARG);
        *state = NOTE_CMD;
        return;
    }
    switch(cmd)
    {
        case(HELP):
            *state = HELP_CMD;
            break;
        case(ADD):
            *state = FOLDER_ADD;
            break;
        case(REM):
            *state = FOLDER_REMOVE;
            break;
        case(EDIT):
            *state = FOLDER_EDIT;
            break;
        case(TYPE):
        case(PRUN):
        case(LIST):
            *state = NORM_CMD;
            break;
        case(NOCMD):
            *status = UNRECOGNIZED_COMMAND;
            *state = FAILED;
            break;
    }
}

int main(int argc, char** argv)
{
    SCODE status = SCODE_OK;
    if (1 == argc)
    {
        showHelp(PRINT_ALL_HELP);
        return handleScode(status);
    }

    PARSE state = START;
    CMD_ARG cmd = NOCMD;
    char* folder = NULL;
    char* type = NULL;
    char* field = NULL;
    uint32_t noteID = 0;
    int newNoteIndex = -1;
    for (int i = 1; i < argc; i++)
    {
        const char* ARG = argv[i];
        cmd = detCommand(ARG);

        switch(state)
        {
            case(START):
                handleStartState(&status, &state, cmd, folder, ARG);
                break;
            case(HELP_CMD):
                showHelp(ARG[0]);
                state = SUCCESS;
                break;
            case(NORM_CMD):
                status = TOO_MANY_ARGS;
                state = FAILED;
                break;
            case(NOTE_CMD):
                switch(cmd)
                {
                    case(ADD):
                        state = NOTE_ADD;
                        break;
                    case(REM):
                        state = NOTE_REMOVE;
                        break;
                    case(EDIT):
                        state = NOTE_EDIT;
                        break;
                    case(LIST):
                        showNotes(folder);
                        state = SUCCESS;
                        break;
                    default:
                        status = UNRECOGNIZED_NOTE_COMMAND;
                        state = FAILED;
                }
                break;
            case(NOTE_ADD):
                if (isNoteType(ARG))
                {
                    NEWN(type, strlen(ARG)+1);
                    strcpy(type, ARG);
                    state = NOTE_ADD_TYPE;
                    break;
                }
                state = FAILED;
                break;
            case(NOTE_ADD_TYPE):
                newNoteIndex = i;
                state = SUCCESS;
                break;
            case(NOTE_REMOVE):
                noteID = atoi(ARG);
                state = NOTE_REMOVE_ID;
                break;
            case(NOTE_REMOVE_ID):
                status = removeNote(folder, noteID);
                state = SUCCESS;
                break;
            case(NOTE_EDIT):
                noteID = atoi(ARG);
                state = NOTE_EDIT_ID;
                break;
            case(NOTE_EDIT_ID):
                NEWN(field, strlen(ARG)+1);
                strcpy(field, ARG);
                state = NOTE_EDIT_FIELD;
                break;
            case(NOTE_EDIT_FIELD):
                status = editNote(noteID, field, ARG);
                state = SUCCESS;
                break;
            case(FOLDER_ADD):
                status = addFolder(ARG);
                state = SUCCESS;
                break;
            case(FOLDER_REMOVE):
                status = removeFolder(ARG);
                state = SUCCESS;
                break;
            case(FOLDER_EDIT):
                NEWN(folder, strlen(ARG)+1);
                strcpy(folder, ARG);
                state = FOLDER_EDIT_NAME;
                break;
            case(FOLDER_EDIT_NAME):
                status = editFolder(folder, ARG);
                state = SUCCESS;
                break;
            case(SUCCESS):
            case(FAILED):
                // do nothing
                break;
        }
    }

    if (HELP_CMD == state)
    {
        showHelp(PRINT_ALL_HELP);
    }
    else if (NORM_CMD == state && TYPE == cmd)
    {
        showNoteTypes();
    }
    else if (NORM_CMD == state && PRUN == cmd)
    {
        status = pruneFolders();
    }
    else if (NORM_CMD == state && LIST == cmd)
    {
        showFolders();
    }
    else if (NOTE_CMD == state)
    {
        showNotes(folder);
    }


    DEL(folder);
    DEL(type);
    DEL(field);
    return handleScode(status);
}
