#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "folders.h"
#include "scodes.h"

bool isFolder(const char* folder)
{
    return (0 == strcmp("folder", folder));
}

SCODE addFolder(const char* name)
{
    SCODE status = SCODE_OK;
    printf("add folder: %s \n", name);
    return status;
}

SCODE removeFolder(const char* folder)
{
    SCODE status = SCODE_OK;
    printf("remove folder: %s \n", folder);
    return status;
}

SCODE editFolder(const char* folder, const char* newName)
{
    SCODE status = SCODE_OK;
    printf("edit folder: %s->%s\n", folder, newName);
    return status;
}

SCODE pruneFolders()
{
    SCODE status = SCODE_OK;
    printf("prune folders\n");
    return status;
}

void showFolders()
{
    printf("show folders\n");
}
