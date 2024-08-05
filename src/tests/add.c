#include "tests.h"

START_TEST(t_add_both_zero) {
  decimal_t a = {0};
  decimal_t b = {0};

  decimal_t result = {0};
  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "0.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_positive_numbers) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("12345", &a);
  convert_from_str_to_decimal("67890", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "80235.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_negative_numbers) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("-12345", &a);
  convert_from_str_to_decimal("-67890", &b);
  char tmp[200] = {0};
  convert_from_decimal_to_str(&a, tmp);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "-80235.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_positive_and_negative) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("12345", &a);
  convert_from_str_to_decimal("-6789", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "5556.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_with_carry) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("999999999999999999", &a);
  convert_from_str_to_decimal("1", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "1000000000000000000.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_decimal_with_fraction) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("12345.6789", &a);
  convert_from_str_to_decimal("0.3211", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "12346.0000";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_first_scale_is_smaller) {
  decimal_t a, b, result;

  convert_from_str_to_decimal("1.1", &a);
  convert_from_str_to_decimal("1.0009", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "2.1009";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_first_scale_is_bigger) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("0.111111", &a);
  convert_from_str_to_decimal("1.009", &b);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "1.120111";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

START_TEST(t_add_first_negative) {
  decimal_t a, b, result;
  convert_from_str_to_decimal("-111", &a);
  convert_from_str_to_decimal("100", &b);
  char tmp[200] = {0};
  convert_from_decimal_to_str(&a, tmp);

  int return_code = decimal_add(a, b, &result);

  char result_str[100] = {0};
  convert_from_decimal_to_str(&result, result_str);

  const char *expected = "-11.";

  ck_assert_str_eq(result_str, expected);
  ck_assert_int_eq(return_code, 0);
}
END_TEST

Suite *ts_add(void) {
  Suite *s = suite_create("ts_add");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, t_add_both_zero);
  tcase_add_test(tc, t_add_positive_numbers);
  tcase_add_test(tc, t_add_negative_numbers);
  tcase_add_test(tc, t_add_positive_and_negative);
  tcase_add_test(tc, t_add_with_carry);
  tcase_add_test(tc, t_add_decimal_with_fraction);
  tcase_add_test(tc, t_add_first_scale_is_smaller);
  tcase_add_test(tc, t_add_first_scale_is_bigger);
  tcase_add_test(tc, t_add_first_negative);

  suite_add_tcase(s, tc);

  return s;
}
