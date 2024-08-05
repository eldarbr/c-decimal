#include "tests.h"

START_TEST(t_mul_both_zero) {
  decimal_t a = {0};
  decimal_t b = {0};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_first_zero) {
  decimal_t a = {0};
  decimal_t b = {{99999}};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_second_zero) {
  decimal_t a = {{99999}};
  decimal_t b = {0};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_same_sign_integers_full_int) {
  decimal_t a = {{-1}};
  decimal_t b = {{-1}};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "18446744065119617025.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_same_sign_rational_full_int) {
  decimal_t a = {{-1}};
  decimal_set_exponent(&a, 14);
  decimal_t b = {{-1}};
  decimal_set_exponent(&b, 5);

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "1.8446744065119617025";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_same_sign_overflow) {
  decimal_t a = {0};
  convert_from_str_to_decimal("79228162514264337593543950335", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal("2", &b);

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(t_mul_same_sign_overflow_prevented_rounding) {
  decimal_t a = {0};
  convert_from_str_to_decimal("79228162514264337593543950335", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal(".00256445", &b);

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "203176661359705180541763783.44";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_same_sign_overflow_prevented_no_rounding) {
  decimal_t a = {0};
  convert_from_str_to_decimal("79228162514264337593543950335", &a);
  decimal_t b = {0};
  convert_from_str_to_decimal(".02", &b);

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "1584563250285286751870879006.7";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_mul_positive_overflow_long_mantissa) {
  decimal_t a = {{0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  decimal_t b = {{20}};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(t_mul_negative_overflow_long_mantissa) {
  decimal_t a = {{0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  decimal_t b = {{20}};
  decimal_set_sign(&b, 1);

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 2);
}
END_TEST

START_TEST(t_mul_positive_no_overflow_long_mantissa) {
  decimal_t a = {{0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  decimal_t b = {{1}};

  decimal_t result = {0};
  int return_code = decimal_mul(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  char expected[100] = {0};
  convert_from_decimal_to_str(&a, expected);

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

Suite *ts_mul(void) {
  Suite *s1 = suite_create("ts_mul");
  TCase *tc1_1 = tcase_create("ts_mul");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_mul_both_zero);
  tcase_add_test(tc1_1, t_mul_first_zero);
  tcase_add_test(tc1_1, t_mul_second_zero);
  tcase_add_test(tc1_1, t_mul_same_sign_integers_full_int);
  tcase_add_test(tc1_1, t_mul_same_sign_rational_full_int);
  tcase_add_test(tc1_1, t_mul_same_sign_overflow);
  tcase_add_test(tc1_1, t_mul_same_sign_overflow_prevented_rounding);
  tcase_add_test(tc1_1, t_mul_same_sign_overflow_prevented_no_rounding);
  tcase_add_test(tc1_1, t_mul_positive_overflow_long_mantissa);
  tcase_add_test(tc1_1, t_mul_negative_overflow_long_mantissa);
  tcase_add_test(tc1_1, t_mul_positive_no_overflow_long_mantissa);

  return s1;
}
