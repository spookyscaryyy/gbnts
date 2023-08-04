#include <check.h>
#include <stdio.h>

#include "../src/scodes.h"
#include "../src/gbnts.h"
#include "../src/utils.h"

#define STR_LEN 200
START_TEST(testHandleStartState)
{
    PARSE_DATA dat;
    SCODE status = SCODE_GEN_FAIL;
    dat.state = START;
    dat.cmd = HELP;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;
    status = handleStartState(&dat, "-h");
    ck_assert(dat.state == HELP_CMD);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = NOCMD;

    status = handleStartState(&dat, "folder");
    ck_assert(dat.state == NOTE_CMD);
    ck_assert_str_eq(dat.folder, "folder");
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = ADD;
    DEL(dat.folder);

    status = handleStartState(&dat, "-a");
    ck_assert(dat.state == FOLDER_ADD);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = REM;

    status = handleStartState(&dat, "-r");
    ck_assert(dat.state == FOLDER_REMOVE);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = EDIT;

    status = handleStartState(&dat, "-e");
    ck_assert(dat.state == FOLDER_EDIT);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = TYPE;

    status = handleStartState(&dat, "-t");
    ck_assert(dat.state == NORM_CMD);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = PRUN;

    status = handleStartState(&dat, "-p");
    ck_assert(dat.state == NORM_CMD);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = LIST;

    status = handleStartState(&dat, "-ls");
    ck_assert(dat.state == NORM_CMD);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = START;
    dat.cmd = NOCMD;

    status = handleStartState(&dat, "test");
    DECODED_SCODE scode;
    decodeScodePackage(&scode, status);
    ck_assert(dat.state == FAILED);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert_int_eq(scode.scode, UNRECOGNIZED_COMMAND);
}
END_TEST

START_TEST(testDetCommand)
{
    char arg[STR_LEN];

    snprintf(arg, STR_LEN, "-ls");
    CMD_ARG result = detCommand(arg);
    ck_assert(result == LIST);

    snprintf(arg, STR_LEN, "-a");
    result = detCommand(arg);
    ck_assert(result == ADD);

    snprintf(arg, STR_LEN, "-r");
    result = detCommand(arg);
    ck_assert(result == REM);

    snprintf(arg, STR_LEN, "-e");
    result = detCommand(arg);
    ck_assert(result == EDIT);

    snprintf(arg, STR_LEN, "-h");
    result = detCommand(arg);
    ck_assert(result == HELP);

    snprintf(arg, STR_LEN, "-t");
    result = detCommand(arg);
    ck_assert(result == TYPE);

    snprintf(arg, STR_LEN, "-p");
    result = detCommand(arg);
    ck_assert(result == PRUN);

    snprintf(arg, STR_LEN, "ls");
    result = detCommand(arg);
    ck_assert(result == NOCMD);

    snprintf(arg, STR_LEN, "test");
    result = detCommand(arg);
    ck_assert(result == NOCMD);
}
END_TEST

START_TEST(testHandleLeftovers)
{
    ck_assert_int_eq(1,1);
}
END_TEST

START_TEST(testHelpParsing)
{
    PARSE_DATA dat;
    SCODE status = SCODE_GEN_FAIL;
    dat.state = START;
    dat.cmd = NOCMD;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;

    status = singleParseLoop(&dat, "test");
    ck_assert(dat.state == FAILED);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "all");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "a");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "notes");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "n");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "command");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "c");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "folder");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
    dat.state = HELP_CMD;
    dat.cmd = NOCMD;

    status = singleParseLoop(&dat, "f");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
}
END_TEST

// TODO: change when folders added
START_TEST(testFolderAddParsing)
{
    PARSE_DATA dat;
    SCODE status = SCODE_GEN_FAIL;
    dat.state = FOLDER_ADD;
    dat.cmd = NOCMD;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;

    status = singleParseLoop(&dat, "test");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
}
END_TEST

// TODO: change when folders added
START_TEST(testFolderRemoveParsing)
{
    PARSE_DATA dat;
    SCODE status = SCODE_GEN_FAIL;
    dat.state = FOLDER_REMOVE;
    dat.cmd = NOCMD;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;

    status = singleParseLoop(&dat, "test");
    ck_assert(dat.state == SUCCESS);
    ck_assert(dat.folder == NULL);
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);
}
END_TEST

// TODO: change when folders added
START_TEST(testFolderEditParsing)
{
    PARSE_DATA dat;
    SCODE status = SCODE_GEN_FAIL;
    dat.state = FOLDER_EDIT;
    dat.cmd = NOCMD;
    dat.folder = NULL;
    dat.type = NULL;
    dat.field = NULL;
    dat.noteID = 0;
    dat.noteIndex = -1;

    status = singleParseLoop(&dat, "test");
    ck_assert(dat.state == FOLDER_EDIT_NAME);
    ck_assert_str_eq(dat.folder, "test");
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);

    status = singleParseLoop(&dat, "test1");
    ck_assert(dat.state == SUCCESS);
    ck_assert_str_eq(dat.folder, "test");
    ck_assert(dat.type == NULL);
    ck_assert(dat.field == NULL);
    ck_assert(dat.noteID == 0);
    ck_assert(dat.noteIndex == -1);
    ck_assert(status == SCODE_OK);

    DEL(dat.folder);
}
END_TEST

START_TEST(testNoteRemove)
{

}
END_TEST

START_TEST(testNoteAdd)
{

}
END_TEST

START_TEST(testNoteEdit)
{

}
END_TEST

START_TEST(testNormalCommands)
{

}
END_TEST

START_TEST(testArgumentParse)
{
    ck_assert_int_eq(1,1);
}
END_TEST

Suite* interface_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Interface");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testDetCommand);
    tcase_add_test(tc_core, testHandleStartState);
    tcase_add_test(tc_core, testHelpParsing);
    tcase_add_test(tc_core, testFolderAddParsing);
    tcase_add_test(tc_core, testFolderRemoveParsing);
    tcase_add_test(tc_core, testFolderEditParsing);
    tcase_add_test(tc_core, testNoteRemove);
    tcase_add_test(tc_core, testNoteAdd);
    tcase_add_test(tc_core, testNoteEdit);
    tcase_add_test(tc_core, testNormalCommands);
    tcase_add_test(tc_core, testHandleLeftovers);
    tcase_add_test(tc_core, testArgumentParse);
    suite_add_tcase(s, tc_core);

    return s;
}

