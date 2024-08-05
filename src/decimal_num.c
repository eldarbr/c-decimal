#include <limits.h>
#include <string.h>

#include "decimal.h"
#include "decimal_utils.h"

int decimal_get_sign(const decimal_t *const num) {
  if (!num) {
    return 0;
  }
  const unsigned char *num_meta = (const unsigned char *)(num->bits + 3);
  int sign = num_meta[3] >> 7;
  return sign;
}

int decimal_get_exponent(const decimal_t *const num) {
  if (!num) {
    return 0;
  }
  const char *num_meta = (const char *)(num->bits + 3);
  int exponent = num_meta[2];
  return exponent;
}

int decimal_set_sign(decimal_t *const num, const int sign) {
  if (!num || (sign != 1 && sign != 0)) {
    return 1;
  }
  char *num_meta = (char *)(num->bits + 3);
  num_meta[3] = sign << 7;
  return 0;
}

int decimal_set_exponent(decimal_t *const num, const int exponent) {
  if (!num || exponent > 28 || exponent < 0) {
    return 1;
  }
  char *num_meta = (char *)(num->bits + 3);
  num_meta[2] = (char)exponent;
  return 0;
}

int decimal_raise_mantissa(decimal_t *const num) {
  return raise_long_mantissa(num->bits, 3);
}

int decimal_lower_mantissa(decimal_t *const num) {
  return lower_long_mantissa(num->bits, 3);
}

int decimal_get_mantissa_scale(decimal_t num) {
  int scale = 0;
  while (_get_largest_nonzero_mantissa_byte(num.bits, 12) || num.bits[0]) {
    decimal_lower_mantissa(&num);
    ++scale;
  }
  return scale;
}

void decimal_copy_number(const decimal_t *const src,
                             decimal_t *const dst) {
  if (src && dst) {
    memcpy(dst->bits, src->bits, 4 * sizeof(int));
  }
}

void decimal_copy_mantissa(const decimal_t *const src,
                               decimal_t *const dst) {
  if (src && dst) {
    memcpy(dst->bits, src->bits, 3 * sizeof(int));
  }
}

int decimal_floor(decimal_t value, decimal_t *const result) {
  if (!result) {
    return 1;
  }
  int deleted_digits_are_nonzero = 0;
  int current_exponent = 0;
  while ((current_exponent = decimal_get_exponent(&value))) {
    int recently_deleted_digit = decimal_lower_mantissa(&value);
    --current_exponent;
    decimal_set_exponent(&value, current_exponent);
    if (recently_deleted_digit) {
      deleted_digits_are_nonzero = 1;
    }
  }
  if (decimal_get_sign(&value) && deleted_digits_are_nonzero) {
    decimal_t tmp = {{1}};
    decimal_sub(value, tmp, &value);
  }
  decimal_copy_number(&value, result);
  return 0;
}

int decimal_round(decimal_t value, decimal_t *const result) {
  if (!result) {
    return 1;
  }
  int latest_deleted_digit = 0;
  int current_exponent = 0;
  while ((current_exponent = decimal_get_exponent(&value))) {
    latest_deleted_digit = decimal_lower_mantissa(&value);
    --current_exponent;
    decimal_set_exponent(&value, current_exponent);
  }
  if (latest_deleted_digit >= 5) {
    decimal_t tmp = {{1}};
    if (decimal_get_sign(&value)) {
      decimal_sub(value, tmp, &value);
    } else {
      decimal_add(value, tmp, &value);
    }
  }
  decimal_copy_number(&value, result);
  return 0;
}

int decimal_truncate(decimal_t value, decimal_t *const result) {
  if (!result) {
    return 1;
  }
  int current_exponent = 0;
  while ((current_exponent = decimal_get_exponent(&value))) {
    decimal_lower_mantissa(&value);
    --current_exponent;
    decimal_set_exponent(&value, current_exponent);
  }
  decimal_copy_number(&value, result);
  return 0;
}

int decimal_negate(decimal_t value, decimal_t *const result) {
  if (!result) {
    return 1;
  }
  const int new_sign = 1 - decimal_get_sign(&value);
  decimal_set_sign(&value, new_sign);
  decimal_copy_number(&value, result);
  return 0;
}
