#include "tests.h"

#define TRUE 1
#define FALSE 0

START_TEST(t_equal_same_expo_same_sign_positive_zeros) {
  decimal_t a = {0};
  decimal_t b = {0};

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_same_expo_same_sign_negative_zeros) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_same_expo_diff_sign_zeros_1) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {0};

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_same_expo_diff_sign_zeros_2) {
  decimal_t a = {0};
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_diff_expo_diff_sign_zeros_1) {
  decimal_t a = {0};
  decimal_set_exponent(&a, 3);
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_same_expo_same_sign_small) {
  decimal_t a = {{15}};
  decimal_t b = {{9}};

  const int expected = FALSE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_diff_expo_same_sign_small) {
  decimal_t a = {{9}};
  decimal_t b = {{90}};
  decimal_set_exponent(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_equal_diff_expo_diff_sign_small) {
  decimal_t a = {{9}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{90}};
  decimal_set_exponent(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_same_expo_same_sign_positive_zeros) {
  decimal_t a = {0};
  decimal_t b = {0};

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_same_expo_same_sign_negative_zeros) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_same_expo_diff_sign_zeros_1) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {0};

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_same_expo_diff_sign_zeros_2) {
  decimal_t a = {0};
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_diff_expo_diff_sign_zeros_1) {
  decimal_t a = {0};
  decimal_set_exponent(&a, 3);
  decimal_t b = {0};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_same_expo_same_sign_small) {
  decimal_t a = {{15}};
  decimal_t b = {{9}};

  const int expected = TRUE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_diff_expo_same_sign_small) {
  decimal_t a = {{9}};
  decimal_t b = {{90}};
  decimal_set_exponent(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_not_equal_diff_expo_diff_sign_small) {
  decimal_t a = {{9}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{90}};
  decimal_set_exponent(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_not_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_same_expo_diff_sign_zeros) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {0};

  const int expected = FALSE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_same_expo_same_sign_small) {
  decimal_t a = {{9}};
  decimal_t b = {{15}};

  const int expected = TRUE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_diff_expo_diff_sign_small) {
  decimal_t a = {{90}};
  decimal_set_exponent(&a, 1);
  decimal_t b = {{9}};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_equal_values) {
  decimal_t a = {{12345}};
  decimal_t b = {{12345}};

  const int expected = FALSE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_same_expo_same_sign_large) {
  decimal_t a = {{4294967295, 4294967295, 4294967295}};
  decimal_t b = {{4294967295, 4294967295, 4294967294}};

  const int expected = FALSE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_diff_expo_diff_sign_large) {
  decimal_t a = {{4294967295, 4294967295, 4294967295}};
  decimal_set_exponent(&a, 1);
  decimal_t b = {{4294967295, 4294967295, 4294967294}};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_zero_positive) {
  decimal_t a = {0};
  decimal_t b = {{1}};

  const int expected = TRUE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_zero_negative) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  decimal_t b = {{1}};

  const int expected = TRUE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_negative_diff_positive_result) {
  decimal_t a = {{9}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{5}};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_less(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_same_expo_same_sign_equal) {
  decimal_t a = {{10}};
  decimal_t b = {{10}};

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_same_expo_same_sign_less) {
  decimal_t a = {{5}};
  decimal_t b = {{10}};

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_same_expo_diff_sign_zero) {
  decimal_t a = {{0}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{0}};

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_diff_expo_same_sign) {
  decimal_t a = {{50}};
  decimal_set_exponent(&a, 2);
  decimal_t b = {{500}};
  decimal_set_exponent(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_diff_expo_same_sign_not_equal) {
  decimal_t a = {{50}};
  decimal_set_exponent(&a, 1);
  decimal_t b = {{500}};
  decimal_set_exponent(&b, 2);

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_diff_sign) {
  decimal_t a = {{10}};
  decimal_t b = {{5}};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_negative_less_positive) {
  decimal_t a = {{10}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{5}};

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_less_or_equal_negative_equal) {
  decimal_t a = {{10}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{10}};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_less_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_both_positive) {
  decimal_t a = {{10}};
  decimal_t b = {{5}};

  const int expected = TRUE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_both_negative_1) {
  decimal_t a = {{5}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{10}};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_both_negative_2) {
  decimal_t a = {{10}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{5}};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_second_negative) {
  decimal_t a = {{5}};
  decimal_t b = {{5}};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_first_negative) {
  decimal_t a = {{5}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{5}};

  const int expected = FALSE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_same_value_positive) {
  decimal_t a = {{10}};
  decimal_t b = {{10}};

  const int expected = FALSE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_same_value_both_negative) {
  decimal_t a = {{10}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{10}};
  decimal_set_sign(&b, 1);

  const int expected = FALSE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_zeros) {
  decimal_t a = {{0}};
  decimal_t b = {{0}};

  const int expected = FALSE;
  const int actual = decimal_is_greater(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_zeros) {
  decimal_t a = {{0}};
  decimal_t b = {{0}};
  decimal_set_sign(&b, 1);

  const int expected = TRUE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_close_positive_same_expo) {
  decimal_t a = {0};
  convert_from_str_to_decimal("10.0000", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal("9.9999", &b);

  const int expected = TRUE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_different_sign_same_expo) {
  decimal_t a = {0};
  convert_from_str_to_decimal("-10.0000", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal("9.9999", &b);

  const int expected = FALSE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_different_sign_same_expo_rev) {
  decimal_t a = {0};
  convert_from_str_to_decimal("10.0000", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal("-9.9999", &b);

  const int expected = TRUE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_diff_expo_same_mantissa) {
  decimal_t a = {0};
  convert_from_str_to_decimal("45512", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal(".45512", &b);

  const int expected = TRUE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(t_greater_or_equal_diff_expo_same_mantissa_rev) {
  decimal_t a = {0};
  convert_from_str_to_decimal(".45512", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal("45512", &b);

  const int expected = FALSE;
  const int actual = decimal_is_greater_or_equal(a, b);

  ck_assert_int_eq(expected, actual);
}
END_TEST

Suite *ts_comparison(void) {
  Suite *s1 = suite_create("ts_comparison");
  TCase *tc1_1 = tcase_create("ts_comparison");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_equal_same_expo_same_sign_positive_zeros);
  tcase_add_test(tc1_1, t_equal_same_expo_same_sign_negative_zeros);
  tcase_add_test(tc1_1, t_equal_same_expo_diff_sign_zeros_1);
  tcase_add_test(tc1_1, t_equal_same_expo_diff_sign_zeros_2);
  tcase_add_test(tc1_1, t_equal_diff_expo_diff_sign_zeros_1);
  tcase_add_test(tc1_1, t_equal_same_expo_same_sign_small);
  tcase_add_test(tc1_1, t_equal_diff_expo_same_sign_small);
  tcase_add_test(tc1_1, t_equal_diff_expo_diff_sign_small);

  tcase_add_test(tc1_1, t_not_equal_same_expo_same_sign_positive_zeros);
  tcase_add_test(tc1_1, t_not_equal_same_expo_same_sign_negative_zeros);
  tcase_add_test(tc1_1, t_not_equal_same_expo_diff_sign_zeros_1);
  tcase_add_test(tc1_1, t_not_equal_same_expo_diff_sign_zeros_2);
  tcase_add_test(tc1_1, t_not_equal_diff_expo_diff_sign_zeros_1);
  tcase_add_test(tc1_1, t_not_equal_same_expo_same_sign_small);
  tcase_add_test(tc1_1, t_not_equal_diff_expo_same_sign_small);
  tcase_add_test(tc1_1, t_not_equal_diff_expo_diff_sign_small);

  tcase_add_test(tc1_1, t_less_same_expo_diff_sign_zeros);
  tcase_add_test(tc1_1, t_less_same_expo_same_sign_small);
  tcase_add_test(tc1_1, t_less_diff_expo_diff_sign_small);
  tcase_add_test(tc1_1, t_less_equal_values);
  tcase_add_test(tc1_1, t_less_same_expo_same_sign_large);
  tcase_add_test(tc1_1, t_less_diff_expo_diff_sign_large);
  tcase_add_test(tc1_1, t_less_zero_positive);
  tcase_add_test(tc1_1, t_less_zero_negative);
  tcase_add_test(tc1_1, t_less_negative_diff_positive_result);

  tcase_add_test(tc1_1, t_less_or_equal_same_expo_same_sign_equal);
  tcase_add_test(tc1_1, t_less_or_equal_same_expo_same_sign_less);
  tcase_add_test(tc1_1, t_less_or_equal_same_expo_diff_sign_zero);
  tcase_add_test(tc1_1, t_less_or_equal_diff_expo_same_sign);
  tcase_add_test(tc1_1, t_less_or_equal_diff_expo_same_sign_not_equal);
  tcase_add_test(tc1_1, t_less_or_equal_diff_sign);
  tcase_add_test(tc1_1, t_less_or_equal_negative_less_positive);
  tcase_add_test(tc1_1, t_less_or_equal_negative_equal);

  tcase_add_test(tc1_1, t_greater_both_positive);
  tcase_add_test(tc1_1, t_greater_both_negative_1);
  tcase_add_test(tc1_1, t_greater_both_negative_2);
  tcase_add_test(tc1_1, t_greater_second_negative);
  tcase_add_test(tc1_1, t_greater_first_negative);
  tcase_add_test(tc1_1, t_greater_same_value_positive);
  tcase_add_test(tc1_1, t_greater_same_value_both_negative);
  tcase_add_test(tc1_1, t_greater_zeros);

  tcase_add_test(tc1_1, t_greater_or_equal_zeros);
  tcase_add_test(tc1_1, t_greater_or_equal_close_positive_same_expo);
  tcase_add_test(tc1_1, t_greater_or_equal_different_sign_same_expo);
  tcase_add_test(tc1_1, t_greater_or_equal_different_sign_same_expo_rev);
  tcase_add_test(tc1_1, t_greater_or_equal_diff_expo_same_mantissa);
  tcase_add_test(tc1_1, t_greater_or_equal_diff_expo_same_mantissa_rev);

  return s1;
}
