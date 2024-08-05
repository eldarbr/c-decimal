#include "tests.h"

START_TEST(t_div_periodic_negative_rounding) {
  decimal_t numerator = {0};
  convert_from_str_to_decimal("-1000", &numerator);
  decimal_t divisor = {0};
  convert_from_str_to_decimal(".6", &divisor);

  decimal_t quotient = {0};
  const int actual_ret = decimal_div(numerator, divisor, &quotient);

  const char *expected = "-1666.6666666666666666666666667";
  const int expected_ret = 0;

  char actual[100] = {0};
  convert_from_decimal_to_str(&quotient, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_div_non_periodic_positive_exact_raised) {
  decimal_t numerator = {0};
  convert_from_str_to_decimal("1142", &numerator);
  decimal_t divisor = {0};
  convert_from_str_to_decimal(".000002", &divisor);

  decimal_t quotient = {0};
  const int actual_ret = decimal_div(numerator, divisor, &quotient);

  const char *expected = "571000000.";
  const int expected_ret = 0;

  char actual[100] = {0};
  convert_from_decimal_to_str(&quotient, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_div_full_mantissas_larger_divisor_mantissa) {
  decimal_t numerator = {0};
  convert_from_str_to_decimal("-158483214495476980182195.41812", &numerator);
  decimal_t divisor = {0};
  convert_from_str_to_decimal("3971262594673005929264.3381151", &divisor);

  decimal_t quotient = {0};
  const int actual_ret = decimal_div(numerator, divisor, &quotient);

  const char *expected = "-39.907513219615360233516536066";
  const int expected_ret = 0;

  char actual[100] = {0};
  convert_from_decimal_to_str(&quotient, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

Suite *ts_div(void) {
  Suite *s1 = suite_create("ts_div");
  TCase *tc1_1 = tcase_create("ts_div");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_div_periodic_negative_rounding);
  tcase_add_test(tc1_1, t_div_non_periodic_positive_exact_raised);
  tcase_add_test(tc1_1, t_div_full_mantissas_larger_divisor_mantissa);

  return s1;
}
