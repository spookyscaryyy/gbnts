#ifndef _SCODES_H
#define _SCODES_H

/* Includes */
#include <stdint.h>

/* typedefs */
typedef int32_t SCODE;

/* SCODE structure 
 * [0-11]    code
 * [12-17]   FileID
 * [18-31]   LineNumber
 */

/* Macos/Definitions */
#define SUCCESS(status) status >= 0
#define FAILED(status) status < 0
#define ENCODE(fileID,  scode) _buildCode(fileID, __LINE__, scode)

/* SCODEs */
#define SCODE_OK                            0
#define SCODE_GEN_FAIL                      -1
#define TOO_MANY_ARGS                       -2
#define UNRECOGNIZED_COMMAND                -3
#define UNRECOGNIZED_NOTE_COMMAND           -4
#define NULL_POINTER_DEREF                  -5


/* File IDs */
#define GBNTS_MAIN                          1
#define FOLDER_EXPERT                       2
#define NOTES_EXPERT                        3
#define SCODES_EXPERT                       4


/* Functions */
int handleScode(SCODE code);

SCODE _buildCode(uint8_t fileID, uint16_t lineNo, int16_t scode);

#endif
