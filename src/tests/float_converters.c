#include "tests.h"

#define OK 0
#define CONV_ERR 1

START_TEST(t_from_float_abnormal_inf) {
  const float inp = 1. / 0.;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_abnormal_nan) {
  const float inp = 0. / 0.;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_abnormal_too_large_positive) {
  const float inp = 1e32f;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_abnormal_too_large_negative) {
  const float inp = -8e29f;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_abnormal_too_small_positive) {
  const float inp = 1e-29f;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_abnormal_too_small_negative) {
  const float inp = -1e-29f;
  decimal_t val = {0};
  const decimal_t expected_result = {0};
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = CONV_ERR;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_positive_medium) {
  const float inp = 923.6612f;
  decimal_t val = {0};
  decimal_t expected_result = {0};
  convert_from_str_to_decimal("923.6612", &expected_result);
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_positive_large) {
  const float inp = 923.6612e12f;
  decimal_t val = {0};
  decimal_t expected_result = {0};
  convert_from_str_to_decimal("923661200000000", &expected_result);
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_positive_small) {
  const float inp = 923.6612e-12f;
  decimal_t val = {0};
  decimal_t expected_result = {0};
  convert_from_str_to_decimal(".0000000009236612", &expected_result);
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_from_float_negative_small) {
  const float inp = -923.6612e-12f;
  decimal_t val = {0};
  decimal_t expected_result = {0};
  convert_from_str_to_decimal("-.0000000009236612", &expected_result);
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

// in the test the float mantissa gets partially rounded because it doesn't fit
START_TEST(t_from_float_negative_ultrasmall) {
  const float inp = -1.45e-27f;
  decimal_t val = {0};
  decimal_t expected_result = {0};
  convert_from_str_to_decimal("-.0000000000000000000000000015", &expected_result);
  const int actual_return_code = convert_from_float_to_decimal(inp, &val);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_mem_eq(&val, &expected_result, sizeof(decimal_t));
}
END_TEST

START_TEST(t_to_float_positive_medium) {
  decimal_t val = {0};
  convert_from_str_to_decimal("100.9123", &val);
  const float expected = 100.9123f;
  float actual = 0.;
  const int actual_return_code = convert_from_decimal_to_float(val, &actual);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_float_eq_tol(expected, actual, 1e-4);
}
END_TEST

START_TEST(t_to_float_negative_ultrasmall) {
  decimal_t val = {0};
  convert_from_str_to_decimal("-.0000000000000000000000000015", &val);
  const float expected = -15e-28f;
  float actual = 0.;
  const int actual_return_code = convert_from_decimal_to_float(val, &actual);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_float_eq_tol(expected, actual, 1e-33);
}
END_TEST

START_TEST(t_to_float_positive_large_mantissa) {
  decimal_t val = {0};
  convert_from_str_to_decimal("100000155555555", &val);
  const float expected = 1000002e8f;
  float actual = 0.;
  const int actual_return_code = convert_from_decimal_to_float(val, &actual);
  const int expected_return_code = OK;

  ck_assert_int_eq(actual_return_code, expected_return_code);
  ck_assert_float_eq_tol(expected, actual, 1e8);
}
END_TEST

Suite *ts_float_converters(void) {
  Suite *s1 = suite_create("ts_float_converters");
  TCase *tc1_1 = tcase_create("ts_float_converters");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_from_float_abnormal_inf);
  tcase_add_test(tc1_1, t_from_float_abnormal_nan);
  tcase_add_test(tc1_1, t_from_float_abnormal_too_large_positive);
  tcase_add_test(tc1_1, t_from_float_abnormal_too_large_negative);
  tcase_add_test(tc1_1, t_from_float_abnormal_too_small_positive);
  tcase_add_test(tc1_1, t_from_float_abnormal_too_small_negative);
  tcase_add_test(tc1_1, t_from_float_positive_medium);
  tcase_add_test(tc1_1, t_from_float_positive_large);
  tcase_add_test(tc1_1, t_from_float_positive_small);
  tcase_add_test(tc1_1, t_from_float_negative_small);
  tcase_add_test(tc1_1, t_from_float_negative_ultrasmall);

  tcase_add_test(tc1_1, t_to_float_positive_medium);
  tcase_add_test(tc1_1, t_to_float_negative_ultrasmall);
  tcase_add_test(tc1_1, t_to_float_positive_large_mantissa);

  return s1;
}
