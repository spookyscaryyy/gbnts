#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/scodes.h"
#include "../src/gbnts.h"

#define STR_LEN 200

START_TEST(testHandleScode)
{
    SCODE res = ENCODE(TEST_FILE, SCODE_OK);
    ck_assert(EXIT_SUCCESS == handleScode(res));
    res = ENCODE(TEST_FILE, SCODE_GEN_FAIL);
    ck_assert(EXIT_FAILURE == handleScode(res));
    res = ENCODE(TEST_FILE, TOO_MANY_ARGS);
    ck_assert(EXIT_FAILURE == handleScode(res));
    res = ENCODE(TEST_FILE, UNRECOGNIZED_COMMAND);
    ck_assert(EXIT_FAILURE == handleScode(res));
    res = ENCODE(TEST_FILE, UNRECOGNIZED_NOTE_COMMAND);
    ck_assert(EXIT_FAILURE == handleScode(res));
    res = ENCODE(TEST_FILE, NULL_POINTER_DEREF);
    ck_assert(EXIT_FAILURE == handleScode(res));
}
END_TEST

START_TEST(testBuildCode)
{
    SCODE res;
    uint16_t lineNo = 0;
    uint8_t fileID = 0;
    int16_t scode = 0;

    for (int i = 0; i <= SCODES_EXPERT; i++)
    {
        for (int j = SCODE_OK; j >= NULL_POINTER_DEREF; j--)
        {
            int correctLineNum = __LINE__ + 1;
            res = ENCODE(i, j);
            decodeScode(&fileID, &lineNo, &scode, res);
            ck_assert_int_eq(fileID, i);
            ck_assert_int_eq(lineNo, correctLineNum);
            ck_assert_int_eq(scode,j);
        }
    }
}
END_TEST

Suite* scode_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Scodes");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testHandleScode);
    tcase_add_test(tc_core, testBuildCode);
    suite_add_tcase(s, tc_core);

    return s;
}
