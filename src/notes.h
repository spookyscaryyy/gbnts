#ifndef _NOTES_H
#define _NOTES_H

#include <stdbool.h>
#include <stdint.h>

#include "scodes.h"

void showNoteTypes();

void showNotes(const char* folder);

bool isNoteType(const char* type);

SCODE removeNote(const char* folder, uint32_t id);

SCODE editNote(uint32_t id, const char* field, const char* change);

#endif
