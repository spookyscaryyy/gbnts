#include <stdio.h>
#include <stdlib.h>

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

void decodeScode(uint8_t* fileID, uint16_t* lineNo, int16_t* scode, SCODE code)
{
    /* decode scode into fields */
    *lineNo = code & LINE_NO_MASK;
    code >>= LINE_NO_SIZE;
    *fileID = code & FILE_ID_MASK;
    code >>= FILE_ID_SIZE;
    *scode = code & SCODE_MASK;

    /* this makes sure negative numbers work correctly */
    *scode <<= 4;
    *scode >>= 4;
}


void decodeScodePackage(DECODED_SCODE* scode, SCODE code)
{
    scode->lineNo = code & LINE_NO_MASK;
    code >>= LINE_NO_SIZE;
    scode->fileID = code & FILE_ID_MASK;
    code >>= FILE_ID_SIZE;
    scode->scode = code & SCODE_MASK;

    /* this makes sure negative numbers work correctly */
    scode->scode <<= 4;
    scode->scode >>= 4;
}

void handleFailed(SCODE code)
{
    DECODED_SCODE scode;
    decodeScodePackage(&scode, code);

    char filename[FILENAME_LENGTH];
    char err[ERR_MESSAGE_LENGTH];

    switch(scode.fileID)
    {
        case(TEST_FILE):
            snprintf(filename, FILENAME_LENGTH, "test file");
            break;
        case(GBNTS_MAIN):
            snprintf(filename, FILENAME_LENGTH, "gbnts.c");
            break;
        case(FOLDER_EXPERT):
            snprintf(filename, FILENAME_LENGTH, "folderExpert.c");
            break;
        case(NOTES_EXPERT):
            snprintf(filename, FILENAME_LENGTH, "noteExpert.c");
            break;
        case(SCODES_EXPERT):
            snprintf(filename, FILENAME_LENGTH, "scodeExpert.c");
            break;
        default:
            snprintf(filename, FILENAME_LENGTH, "unknown file");
            break;
    }

    switch(scode.scode)
    {
        case(SCODE_GEN_FAIL):
            snprintf(err, ERR_MESSAGE_LENGTH, "Execution failed");
            break;
        case(TOO_MANY_ARGS):
            snprintf(err, ERR_MESSAGE_LENGTH, "Too many args to command");
            break;
        case(UNRECOGNIZED_COMMAND):
            snprintf(err, ERR_MESSAGE_LENGTH, "Invalid command");
            break;
        case(UNRECOGNIZED_NOTE_COMMAND):
            snprintf(err, ERR_MESSAGE_LENGTH, "Invalid note command");
            break;
        case(NULL_POINTER_DEREF):
            snprintf(err, ERR_MESSAGE_LENGTH, "Attempted nullptr dereference");
            break;
        default:
            snprintf(err, ERR_MESSAGE_LENGTH, "Unknown Error");
            break;
    }
    printf("Note failed in %s at line %d with message: %s\n",
            filename, scode.lineNo, err);
}

/* Reads a status code and prints a mesasge associated with it */
int handleScode(SCODE code)
{
    /* print error info if program failed */
    if (FAILED(code))
    {
        handleFailed(code);
    }

    return SUCCESS(code) ? EXIT_SUCCESS : EXIT_FAILURE;
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
