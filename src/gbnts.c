/* C Includes */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Project Includes */
#include "gbnts.h"
#include "scodes.h"
#include "utils.h"

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
    return BAD;
}

bool isCommand(CMD_ARG arg)
{
    return (arg < ARR_SIZE(COMMAND_LIST));
}

SCODE parseArgs(CMD_ARG* args, char** argv, int argc)
{
    args[0] = NAME;
    for (int i = 1; i < argc; i++)
    {
        const char* ARG = argv[i];
        if (COMMAND_SPECIFIER == ARG[0])
        {
            args[i] = detCommand(ARG);
        }
    }
    return SCODE_OK;
}

int main(int argc, char** argv)
{
    SCODE status = SCODE_OK;
    CMD_ARG* args = NULL;
    if (1 == argc)
    {
        showHelp(PRINT_ALL_HELP);
        return handleScode(status);
    }

    NEWN(args, argc);
    status = parseArgs(args, argv, argc);
    if(FAILED(status))
    {
        return handleScode(status);
    }


    DEL(args);
    return handleScode(status);
}
