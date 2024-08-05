#include "tests.h"

int srun_tests(Suite *s);

int main(void) {
  int number_failed = 0;
  Suite *s1 = ts_mul();
  Suite *s2 = ts_add();
  Suite *s3 = ts_comparison();
  Suite *s4 = ts_float_converters();
  Suite *s5 = ts_sub();
  Suite *s6 = ts_negate();
  Suite *s7 = ts_dtoi();
  Suite *s8 = ts_div();
  Suite *s9 = ts_rounding();

  number_failed += srun_tests(s1);
  number_failed += srun_tests(s2);
  number_failed += srun_tests(s3);
  number_failed += srun_tests(s4);
  number_failed += srun_tests(s5);
  number_failed += srun_tests(s6);
  number_failed += srun_tests(s7);
  number_failed += srun_tests(s8);
  number_failed += srun_tests(s9);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int srun_tests(Suite *s) {
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_ENV);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}
