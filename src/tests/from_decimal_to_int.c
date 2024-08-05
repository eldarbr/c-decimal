#include "tests.h"

START_TEST(zero_to_int) {
  decimal_t a = {0};

  int result = -1;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(neg_zero_to_int) {
  decimal_t a = {0};
  decimal_set_sign(&a, 1);
  int result = -1;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(ordinary_to_int) {
  decimal_t a = {{69420}};
  decimal_set_sign(&a, 1);
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, -69420);
}
END_TEST

START_TEST(neg_ordinary_to_int) {
  decimal_t a = {{69420}};
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 69420);
}
END_TEST

START_TEST(limit_to_int) {
  decimal_t a = {{2147483647}};
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 2147483647);
}
END_TEST

START_TEST(neg_limit_to_int) {
  decimal_t a = {{2147483648U}};
  decimal_set_sign(&a, 1);
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, -2147483648);
}
END_TEST

START_TEST(big_to_int) {
  decimal_t a = {{0, 1, 0}};
  int result = 0;
  int return_code = convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(neg_big_to_int) {
  decimal_t a = {{0, 1, 0}};
  decimal_set_sign(&a, 1);
  int result = 0;
  int return_code = convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(floating_decimal_to_int) {
  decimal_t a = {{3141528}};
  decimal_set_exponent(&a, 6);
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(decimal_no_whole_part_to_int) {
  decimal_t a = {{999999}};
  decimal_set_exponent(&a, 6);
  int result = 0;
  convert_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *ts_dtoi(void) {
  Suite *s1 = suite_create("ts_dtoi");
  TCase *tc1_1 = tcase_create("ts_dtoi");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, zero_to_int);
  tcase_add_test(tc1_1, neg_zero_to_int);
  tcase_add_test(tc1_1, ordinary_to_int);
  tcase_add_test(tc1_1, neg_ordinary_to_int);
  tcase_add_test(tc1_1, limit_to_int);
  tcase_add_test(tc1_1, neg_limit_to_int);
  tcase_add_test(tc1_1, big_to_int);
  tcase_add_test(tc1_1, neg_big_to_int);
  tcase_add_test(tc1_1, floating_decimal_to_int);
  tcase_add_test(tc1_1, decimal_no_whole_part_to_int);
  return s1;
}