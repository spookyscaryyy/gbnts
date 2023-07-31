#ifndef _FOLDERS_H
#define _FOLDERS_H

#include <stdbool.h>

#include "scodes.h"

bool isFolder(const char* folder);

SCODE addFolder(const char* name);

SCODE removeFolder(const char* folder);

SCODE editFolder(const char* folder, const char* newName);

SCODE pruneFolders();

void showFolders();

#endif
