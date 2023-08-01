#include <check.h>

#include "../src/scodes.h"

START_TEST(test_scodes)
{
    ck_assert_int_eq(10, 10);
    ck_assert_int_eq(11, 10);
}
END_TEST

Suite* interface_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Interface");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_scodes);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int failed;
    Suite *s;
    SRunner *sr;

    s = interface_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return 0;
}
