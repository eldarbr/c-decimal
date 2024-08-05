#include "tests.h"

START_TEST(t_negate_zero) {
  decimal_t a = {0};
  decimal_t result = {0};
  decimal_set_sign(&result, 1);
  int return_code = decimal_negate(a, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "-0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_negate_negative_zero) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t result = {0};
  decimal_set_sign(&result, 1);
  int return_code = decimal_negate(a, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_negate_positive) {
  decimal_t a = {{10}};
  decimal_t result = {0};
  int return_code = decimal_negate(a, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "-10.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_negate_negative) {
  decimal_t a = {{10}};
  decimal_set_sign(&a, 1);
  decimal_t result = {0};
  int return_code = decimal_negate(a, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "10.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_negate_null_result) {
  decimal_t a = {{10}};
  int return_code = decimal_negate(a, NULL);

  ck_assert_int_eq(return_code, 1);
}
END_TEST

Suite *ts_negate(void) {
  Suite *s1 = suite_create("ts_negate");
  TCase *tc1_1 = tcase_create("ts_negate");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_negate_zero);
  tcase_add_test(tc1_1, t_negate_negative_zero);
  tcase_add_test(tc1_1, t_negate_positive);
  tcase_add_test(tc1_1, t_negate_negative);
  tcase_add_test(tc1_1, t_negate_null_result);

  return s1;
}