
#include <check.h>

#include "system.h"
#include "c-ctype.h"

/* The official name of this program (e.g., no 'g' prefix).  */
#define PROGRAM_NAME "util-test"

#define AUTHORS \
  proper_name ("Wes Edens")

START_TEST (c_ctype)
{
    fail_if(c_isascii(-1), "c_isascii()");
}
END_TEST

START_TEST (c_ctype2)
{
    fail_if(c_isascii(-1), "c_isascii()");
    fail_if(c_isascii(0), "c_isascii()");
}
END_TEST

Suite* str_suite (void)
{
    Suite *suite = suite_create("isascii");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase, c_ctype);
    tcase_add_test(tcase, c_ctype2);
    suite_add_tcase(suite, tcase);
    return suite;
}

int main (int argc, char *argv[])
{
    int number_failed;
    Suite *suite = str_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}
