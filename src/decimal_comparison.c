#include <limits.h>
#include <stdio.h>

#include "decimal_arithmetics.h"
#include "decimal_convertion.h"
#include "decimal_num.h"

#define TRUE 1
#define FALSE 0

int is_zero(decimal_t value);

int decimal_is_equal(decimal_t value_1, decimal_t value_2) {
  int result = TRUE;

  int both_zero = is_zero(value_1) && is_zero(value_2);

  if (decimal_get_sign(&value_1) != decimal_get_sign(&value_2) && !both_zero) {
    result = FALSE;
  } else {
    int scale1 = decimal_get_exponent(&value_1);
    int scale2 = decimal_get_exponent(&value_2);

    if (scale1 < scale2) {
      decimal_t temp = value_1;
      value_1 = value_2;
      value_2 = temp;
      scale1 = decimal_get_exponent(&value_1);
      scale2 = decimal_get_exponent(&value_2);
    }

    int mantissa_overflow = 0;
    while (scale1 != scale2 && !mantissa_overflow) {
      if (!(mantissa_overflow = decimal_raise_mantissa(&value_2))) {
        decimal_set_exponent(&value_2, ++scale2);
      } else {
        result = FALSE;
      }
    }
    if (scale1 == scale2 && !mantissa_overflow) {
      for (int i = 0; i < 3; i++) {
        if (value_1.bits[i] != value_2.bits[i]) {
          result = FALSE;
          break;
        }
      }
    } else {
      result = FALSE;
    }
  }
  return result;
}

int decimal_is_not_equal(decimal_t value_1, decimal_t value_2) {
  int result = FALSE;
  if (!decimal_is_equal(value_1, value_2)) {
    result = TRUE;
  }
  return result;
}

int decimal_is_less(decimal_t value_1, decimal_t value_2) {
  int result = FALSE;
  int sign1 = decimal_get_sign(&value_1);
  int sign2 = decimal_get_sign(&value_2);

  if (is_zero(value_1) && is_zero(value_2)) {
    result = FALSE;
  } else if (sign1 != sign2) {
    result = sign1 > sign2;
  } else {
    decimal_t diff = {0};
    decimal_sub(value_1, value_2, &diff);

    const int diff_sign = decimal_get_sign(&diff);

    if (diff_sign) {
      result = TRUE;
    }
  }
  return result;
}

int decimal_is_less_or_equal(decimal_t value_1, decimal_t value_2) {
  int result = FALSE;
  if (decimal_is_less(value_1, value_2) || decimal_is_equal(value_1, value_2)) {
    result = TRUE;
  }
  return result;
}

int decimal_is_greater(decimal_t value_1, decimal_t value_2) {
  int result = FALSE;
  if (!decimal_is_less(value_1, value_2) &&
      !decimal_is_equal(value_1, value_2)) {
    result = TRUE;
  }
  return result;
}

int decimal_is_greater_or_equal(decimal_t value_1, decimal_t value_2) {
  int result = FALSE;
  if (decimal_is_greater(value_1, value_2) ||
      decimal_is_equal(value_1, value_2)) {
    result = TRUE;
  }
  return result;
}

int is_zero(decimal_t value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}
