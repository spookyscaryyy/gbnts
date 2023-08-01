
#include <stdbool.h>
#include <stdio.h>

#include "scodes.h"
#include "notes.h"

void showNoteTypes()
{
    printf("show note types\n");
}

void showNotes(const char* folder)
{
    printf("show notes:  %s\n", folder);
}

bool isNoteType(const char* type)
{
    bool ret = true;
    return ret;
}

SCODE addNote(const char* folder)
{
    SCODE status = SCODE_OK;
    printf("add note: %s\n", folder);
    return status;
}

SCODE removeNote(const char* folder, uint32_t id)
{
    SCODE status = SCODE_OK;
    printf("remove note %s/%d\n", folder, id);
    return status;
}

SCODE editNote(uint32_t id, const char* field, const char* change)
{
    SCODE status = SCODE_OK;
    printf("edit note: %d/%s->%s\n", id, field, change);
    return status;
}
