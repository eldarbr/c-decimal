#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decimal_arithmetics.h"
#include "decimal_convertion.h"
#include "decimal_num.h"
#include "decimal_utils.h"

int decimal_add(decimal_t value_1, decimal_t value_2, decimal_t *result) {
  int overflow = 0;
  const int sign1 = decimal_get_sign(&value_1);
  const int sign2 = decimal_get_sign(&value_2);
  if (sign1 == sign2) {
    int scale1 = decimal_get_exponent(&value_1);
    int scale2 = decimal_get_exponent(&value_2);
    int add_mantissa[6] = {0};
    if (scale1 < scale2) {
      decimal_t temp;
      temp = value_1;
      value_1 = value_2;
      value_2 = temp;
      scale1 = decimal_get_exponent(&value_1);
      scale2 = decimal_get_exponent(&value_2);
    }
    int result_exponent = scale1;
    int v1_mantissa[6] = {0};
    memcpy(v1_mantissa, &value_1, 12);
    int v2_mantissa[6] = {0};
    memcpy(v2_mantissa, &value_2, 12);
    while (scale1 != scale2) {
      if (!raise_long_mantissa(v2_mantissa, 6)) {
        scale2++;
      } else {
        overflow = 1 << sign1;
      }
    }
    if (!overflow) {
      overflow = sum_mantissas(v1_mantissa, v2_mantissa, add_mantissa, 6)
                 << sign1;
    }
    if (!overflow && bank_round_long_mantissa(add_mantissa, &result_exponent)) {
      overflow = 1 << sign1;
    }
    if (!overflow && result) {
      for (int i = 0; i < 3; ++i) {
        result->bits[i] = add_mantissa[i];
      }
      decimal_set_exponent(result, result_exponent);
      decimal_set_sign(result, sign1);
    }
  } else {
    // v1 is negative
    if (sign1) {
      decimal_set_sign(&value_1, 0);
      overflow = decimal_sub(value_2, value_1, result);
    } else {
      decimal_set_sign(&value_2, 0);
      overflow = decimal_sub(value_1, value_2, result);
    }
  }
  return overflow;
}
