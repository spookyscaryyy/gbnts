#include <stdio.h>
#include "gbnts.h"
#include "scodes.h"

void showFolderHelp()
{

}

void showNoteHelp()
{

}

void showCommandHelp()
{

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
            showFolderHelp();
            showNoteHelp();
            break;
    }
}

SCODE handleOneArg(char** argv)
{
    return SCODE_OK;
}

SCODE handleTwoArgs(char** argv)
{
    return SCODE_OK;
}

SCODE handleThreeArgs(char** argv)
{
    return SCODE_OK;
}

/* Main function picks arg parse function based on arg amount */
int main(int argc, char** argv)
{
    SCODE status = SCODE_OK;
    switch(argc)
    {
        case(1):
            showHelp(PRINT_ALL_HELP);
            break;
        case(2):
            status = handleOneArg(argv);
            break;
        case(3):
            status = handleTwoArgs(argv);
            break;
        case(4):
            status = handleThreeArgs(argv);
            break;
    }

    return handleScode(status);
}
