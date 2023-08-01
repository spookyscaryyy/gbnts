#include <stdio.h>

#include "scodes.h"
#include "utils.h"

#define LINE_NO_MASK 0x3FFF
#define FILE_ID_MASK 0x3F
#define SCODE_MASK   0x0FFF

#define LINE_NO_SIZE 14
#define FILE_ID_SIZE 6
#define SCODE_SIZE   12

#define FILENAME_LENGTH 20
#define ERR_MESSAGE_LENGTH 200

/* Reads a status code and prints a mesasge associated with it */
int handleScode(SCODE code)
{
    uint16_t lineNo = code & LINE_NO_MASK;
    code >>= LINE_NO_SIZE;

    uint8_t fileID = code & FILE_ID_MASK;
    code >>= FILE_ID_SIZE;

    int16_t scode = code & SCODE_MASK;
    scode <<= 4;
    scode >>= 4;

    if (FAILED(code))
    {
        char filename[FILENAME_LENGTH];
        char err[ERR_MESSAGE_LENGTH];
        switch(fileID)
        {
            case(GBNTS_MAIN):
                snprintf(filename, FILENAME_LENGTH, "gbnts.c");
                break;
            case(FOLDER_EXPERT):
                snprintf(filename, FILENAME_LENGTH, "gbnts.c");
                break;
            default:
                snprintf(filename, FILENAME_LENGTH, "unknown file");
                break;
        }

        switch(scode)
        {
            case(SCODE_GEN_FAIL):
                snprintf(err, ERR_MESSAGE_LENGTH, "Execution failed");
                break;
            default:
                snprintf(err, ERR_MESSAGE_LENGTH, "Unknown Error");
                break;
        }
        printf("Note failed in %s at line %d with message: %s\n",
                filename, lineNo, err);
    }

    return (int)SUCCESS(code);
}

SCODE _buildCode(uint8_t fileID, uint16_t lineNo, int16_t scode)
{
    SCODE code = 0;

    code |= (scode & SCODE_MASK);
    code <<= FILE_ID_SIZE;
    code |= (fileID & FILE_ID_MASK);
    code <<= LINE_NO_SIZE;
    code |= (lineNo & LINE_NO_MASK);

    return code;
}
