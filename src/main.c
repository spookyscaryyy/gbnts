#include "scodes.h"
#include "gbnts.h"
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
