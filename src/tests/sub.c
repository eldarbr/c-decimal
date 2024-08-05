#include "tests.h"

START_TEST(sub_zeroes) {
  decimal_t a = {0};
  decimal_t b = {0};

  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_zero) {
  decimal_t a = {{5}};
  decimal_t b = {0};

  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "5.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_equal) {
  decimal_t a = {{0xFFFF, 0xFFFF, 0xFFFF}};
  decimal_t b = {{0xFFFF, 0xFFFF, 0xFFFF}};
  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);
  const char *expected = "0.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_from_less) {
  decimal_t a = {{0, 0xFFFF, 0xFFFF}};
  decimal_t b = {{0xFFFF, 0xFFFF, 0xFFFF}};
  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);
  const char *expected = "-65535.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_neg) {
  decimal_t a = {0};
  decimal_t b = {{0xF0F0, 0xF0F0, 0xF0F0}};
  decimal_set_sign(&b, 1);
  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);
  const char *expected = "1137795174731318726553840.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_from_neg) {
  decimal_t a = {{0, 0xFFFF, 0}};
  decimal_set_sign(&a, 1);
  decimal_t b = {{0, 0xFFFF, 0}};
  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);
  decimal_t expected_dec = {{0, 0x1FFFE, 0}};
  decimal_set_sign(&expected_dec, 1);
  // const char *expected = "-18447025540096327680.";
  char expected[100] = {0};
  convert_from_decimal_to_str(&expected_dec, expected);
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(sub_small) {
  decimal_t a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  decimal_t b = {{3, 0, 0}};
  decimal_set_exponent(&b, 1);
  decimal_t result = {0};
  int return_code = decimal_sub(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "79228162514264337593543950335.";
  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

Suite *ts_sub(void) {
  Suite *s1 = suite_create("ts_sub");
  TCase *tc1_1 = tcase_create("ts_sub");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sub_zeroes);
  tcase_add_test(tc1_1, sub_zero);
  tcase_add_test(tc1_1, sub_equal);
  tcase_add_test(tc1_1, sub_from_less);
  tcase_add_test(tc1_1, sub_neg);
  tcase_add_test(tc1_1, sub_from_neg);
  tcase_add_test(tc1_1, sub_small);
  return s1;
}
