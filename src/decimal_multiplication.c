#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decimal_num.h"
#include "decimal_utils.h"

int multiply_binary(const decimal_t *, const decimal_t *, decimal_t *);

int decimal_mul(decimal_t value_1, decimal_t value_2, decimal_t *result) {
  int result_sign =
      (decimal_get_sign(&value_1) + decimal_get_sign(&value_2)) & 1;
  int result_exponent =
      decimal_get_exponent(&value_1) + decimal_get_exponent(&value_2);
  int result_min_decimal_digits = decimal_get_mantissa_scale(value_1) +
                                  decimal_get_mantissa_scale(value_2) -
                                  result_exponent;
  int result_code = 0;
  if (result_min_decimal_digits > 30) {
    if (result_sign) {
      result_code = 2;
    } else {
      result_code = 1;
    }
  }
  if (!result_code) {
    result_code = multiply_binary(&value_1, &value_2, result);
  }
  return result_code;
}

int multiply_binary(const decimal_t *const v1, const decimal_t *const v2,
                    decimal_t *result) {
  int result_exponent =
      decimal_get_exponent(v1) + decimal_get_exponent(v2);
  int v1_mantissa[6] = {0};
  memcpy(v1_mantissa, v1, 12);
  int v2_mantissa[6] = {0};
  memcpy(v2_mantissa, v2, 12);
  int multiplication_mantissa[6] = {0};
  while (_get_largest_nonzero_mantissa_byte(v2_mantissa, 24) ||
         v2_mantissa[0]) {
    if (v2_mantissa[0] & 1) {
      sum_mantissas(v1_mantissa, multiplication_mantissa,
                    multiplication_mantissa, 6);
    }
    raise_binary(v1_mantissa, 24);
    lower_binary(v2_mantissa, 24);
  }
  int overflow =
      bank_round_long_mantissa(multiplication_mantissa, &result_exponent);
  int result_sign = (decimal_get_sign(v1) + decimal_get_sign(v2)) & 1;
  if (!overflow && result) {
    memset(result->bits, 0, 16);
    memcpy(result->bits, multiplication_mantissa, 12);
    decimal_set_sign(result, result_sign);
    decimal_set_exponent(result, result_exponent);
  }
  return overflow << result_sign;
}
