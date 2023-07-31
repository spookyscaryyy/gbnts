#ifndef _SCODES_H
#define _SCODES_H

/* Includes */
#include <stdint.h>

/* typedefs */
typedef int32_t SCODE;

/* Macos/Definitions */
#define SUCCESS(status) status >= 0
#define FAILED(status) status < 0

/* SCODEs */
#define SCODE_OK 0
#define SCODE_GEN_FAIL                      -1
#define TOO_MANY_ARGS                       -2
#define UNRECOGNIZED_COMMAND                -3
#define UNRECOGNIZED_NOTE_COMMAND           -4

/* Functions */
int handleScode(SCODE code);

#endif
