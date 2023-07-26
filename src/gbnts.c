#include <stdio.h>
#include "gbnts.h"
#include "scodes.h"

void showHelp(uint8_t which)
{
    switch(which)
    {
        case(1):
            break;
        case(PRINT_ALL_HELP):
        default:
            break;
    }
}

SCODE handleTwoArgs(char** argv)
{
    return SCODE_OK;
}

int main(int argc, char** argv)
{
    SCODE status = SCODE_OK;
    /* no arg given, print help message instead */
    switch(argc)
    {
        case(1):
            showHelp(PRINT_ALL_HELP);
            break;
        case(2):
            status = handleTwoArgs(argv);
            break;
    }

    return handleScode(status);
}
