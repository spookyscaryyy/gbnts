#include <check.h>
#include <stdlib.h>

extern Suite* interface_suite(void);

int main(void)
{
    int failed;
    SRunner *sr;

    sr = srunner_create(interface_suite());

    srunner_run_all(sr, CK_VERBOSE);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
