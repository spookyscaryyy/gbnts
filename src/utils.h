#ifndef _UTILS_H
#define _UTILS_H

/* Includes for below macros */
#include <stdlib.h>
#include <stddef.h>

/* Macros to allocate memory */
#define NEWN(x, n) ((x) = calloc((n), sizeof *(x)))

/* Macros to clear memory and set to null */
#define DEL(x) free(x); x = NULL

/* Get array size */
#define ARR_SIZE(x) (sizeof((x))/sizeof(*(x)))
#endif
