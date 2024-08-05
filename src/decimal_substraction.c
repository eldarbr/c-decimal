#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decimal.h"
#include "decimal_utils.h"

void twos_complement_add(decimal_t value_1, decimal_t value_2,
                         decimal_t *result);

int is_mantissa_less(unsigned int *num1, unsigned int *num2, int length);

void decimal_switch_sign(decimal_t *num) {
  decimal_set_sign(num, 1 - decimal_get_sign(num));
}

int decimal_sub(decimal_t value_1, decimal_t value_2, decimal_t *result) {
  int result_code = 0;
  const int v1_sign = decimal_get_sign(&value_1);
  const int v2_sign = decimal_get_sign(&value_2);
  if (!v1_sign && v2_sign) {
    decimal_switch_sign(&value_2);
    result_code = decimal_add(value_1, value_2, result);
  } else if (v1_sign && !v2_sign) {
    decimal_switch_sign(&value_2);
    result_code = decimal_add(value_1, value_2, result);
  } else if (v1_sign && v2_sign) {
    decimal_switch_sign(&value_2);
    decimal_switch_sign(&value_1);
    result_code = decimal_sub(value_2, value_1, result);
  } else {
    twos_complement_add(value_1, value_2, result);
  }
  return result_code;
}
