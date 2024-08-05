#include "tests.h"

START_TEST(t_floor_positive_trailing_zeros) {
  decimal_t src = {0};
  convert_from_str_to_decimal("310551293500396000.00000000000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "310551293500396000.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_negative_trailing_zeros) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-310551293500396000.00000000000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "-310551293500396000.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_positive_trailing_non_zeros_somewhere) {
  decimal_t src = {0};
  convert_from_str_to_decimal("310551293500396000.00000003000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "310551293500396000.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_negative_trailing_non_zeros_somewhere) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-310551293500396000.00004000000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "-310551293500396001.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_positive_trailing_non_zeros_all) {
  decimal_t src = {0};
  convert_from_str_to_decimal("310551293500396000.39215092721", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "310551293500396000.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_negative_trailing_non_zeros_all) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-310551293500396000.39215092721", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "-310551293500396001.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_floor_negative_no_action_is_needed) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-3105512935003", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_floor(src, &result);

  const int expected_ret = 0;
  const char *expected = "-3105512935003.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_goes_down) {
  decimal_t src = {0};
  convert_from_str_to_decimal("14674059546529340.430186245479", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "14674059546529340.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_goes_down_still) {
  decimal_t src = {0};
  convert_from_str_to_decimal("14674059546529340.499999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "14674059546529340.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_goes_up_finally) {
  decimal_t src = {0};
  convert_from_str_to_decimal("14674059546529340.5000000000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_goes_up_suspiciously) {
  decimal_t src = {0};
  convert_from_str_to_decimal("14674059546529340.5000000001", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_goes_up_confidently) {
  decimal_t src = {0};
  convert_from_str_to_decimal("14674059546529340.99999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_goes_down) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340.430186245479", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529340.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_goes_down_still) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340.499999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529340.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_goes_up_finally) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340.5000000000", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_goes_up_suspiciously) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340.5000000001", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_goes_up_confidently) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340.99999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529341.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_negative_no_action_is_needed) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546529340", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546529340.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_round_positive_whole_number) {
  decimal_t src = {0};
  convert_from_str_to_decimal(".914674059546529340", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_round(src, &result);

  const int expected_ret = 0;
  const char *expected = "1.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_positive_whole_number) {
  decimal_t src = {0};
  convert_from_str_to_decimal(".5493123388147974722938360583", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "0.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_positive_no_action_is_needed) {
  decimal_t src = {0};
  convert_from_str_to_decimal("54931233881479747229383605832", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "54931233881479747229383605832.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_positive_somewhere_in_between) {
  decimal_t src = {0};
  convert_from_str_to_decimal("5493123388.1479747229383605832", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "5493123388.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_negative_whole_number) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-.1467405954652934099999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "-0.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_negative_no_action_is_needed) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-1467405954652934099999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "-1467405954652934099999999.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

START_TEST(t_truncate_negative_somewhere_in_between) {
  decimal_t src = {0};
  convert_from_str_to_decimal("-14674059546.52934099999999", &src);

  decimal_t result = {0};
  const int actual_ret = decimal_truncate(src, &result);

  const int expected_ret = 0;
  const char *expected = "-14674059546.";

  char actual[100] = {0};
  convert_from_decimal_to_str(&result, actual);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(expected_ret, actual_ret);
}
END_TEST

Suite *ts_rounding(void) {
  Suite *s1 = suite_create("ts_rounding");
  TCase *tc1_1 = tcase_create("ts_rounding");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, t_floor_positive_trailing_zeros);
  tcase_add_test(tc1_1, t_floor_negative_trailing_zeros);
  tcase_add_test(tc1_1, t_floor_positive_trailing_non_zeros_somewhere);
  tcase_add_test(tc1_1, t_floor_negative_trailing_non_zeros_somewhere);
  tcase_add_test(tc1_1, t_floor_positive_trailing_non_zeros_all);
  tcase_add_test(tc1_1, t_floor_negative_trailing_non_zeros_all);
  tcase_add_test(tc1_1, t_floor_negative_no_action_is_needed);

  tcase_add_test(tc1_1, t_round_positive_goes_down);
  tcase_add_test(tc1_1, t_round_positive_goes_down_still);
  tcase_add_test(tc1_1, t_round_positive_goes_up_finally);
  tcase_add_test(tc1_1, t_round_positive_goes_up_suspiciously);
  tcase_add_test(tc1_1, t_round_positive_goes_up_confidently);
  tcase_add_test(tc1_1, t_round_negative_goes_down);
  tcase_add_test(tc1_1, t_round_negative_goes_down_still);
  tcase_add_test(tc1_1, t_round_negative_goes_up_finally);
  tcase_add_test(tc1_1, t_round_negative_goes_up_suspiciously);
  tcase_add_test(tc1_1, t_round_negative_goes_up_confidently);
  tcase_add_test(tc1_1, t_round_negative_no_action_is_needed);
  tcase_add_test(tc1_1, t_round_positive_whole_number);

  tcase_add_test(tc1_1, t_truncate_positive_whole_number);
  tcase_add_test(tc1_1, t_truncate_positive_no_action_is_needed);
  tcase_add_test(tc1_1, t_truncate_positive_somewhere_in_between);
  tcase_add_test(tc1_1, t_truncate_negative_whole_number);
  tcase_add_test(tc1_1, t_truncate_negative_no_action_is_needed);
  tcase_add_test(tc1_1, t_truncate_negative_somewhere_in_between);

  return s1;
}
