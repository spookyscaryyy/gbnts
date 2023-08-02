#include <check.h>
#include <stdio.h>

#include "../src/scodes.h"
#include "../src/gbnts.h"

#define STR_LEN 200
START_TEST(testHandleStartState)
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

START_TEST(testDetCommand)
{
    ck_assert_int_eq(1,1);
}
END_TEST

START_TEST(testHandleLeftovers)
{
    ck_assert_int_eq(1,1);
}
END_TEST

START_TEST(testSingleParseLoop)
{
    ck_assert_int_eq(1,1);
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
    tcase_add_test(tc_core, testHandleLeftovers);
    tcase_add_test(tc_core, testSingleParseLoop);
    tcase_add_test(tc_core, testArgumentParse);
    suite_add_tcase(s, tc_core);

    return s;
}

