#include "decimal_convertion.h"

#include <limits.h>
#include <math.h>
#include <string.h>

#include "decimal_arithmetics.h"
#include "decimal_utils.h"

int convert_from_int_to_decimal(int src, decimal_t *dst) {
  if (!dst) {
    return 1;
  }
  memset(dst, 0, sizeof(decimal_t));
  long value = src;
  if (src < 0) {
    decimal_set_sign(dst, 1);
    value = -value;
  }
  memcpy(dst, &value, sizeof(long));
  return 0;
}

int get_float_exponent(float);

int convert_from_float_to_decimal(float src, decimal_t *dst) {
  if (!dst) {
    return 1;
  }
  if (fabsf(src) > 7.93e28 || isnan(src) || isinf(src)) {
    return 1;
  }
  memset(dst, 0, sizeof(decimal_t));
  int src_sign = 0;
  if (src < 0) {
    src_sign = 1;
    src = -src;
  }
  const int src_exponent = get_float_exponent(src);
  int additional_shift_power = 0;
  if (src_exponent < -22) {
    additional_shift_power = src_exponent + 22;
  }
  int shift_power = 6 - src_exponent;
  const float shift = powf(10.f, shift_power);
  const float additional_shift = powf(10.f, additional_shift_power);
  int mantissa_digits = (int)roundf(src * shift);
  int overflow = mantissa_digits > 0 && additional_shift_power < -7;
  if (!overflow) {
    mantissa_digits = (int)roundf(mantissa_digits * additional_shift);
    shift_power += additional_shift_power;
    convert_from_int_to_decimal(mantissa_digits, dst);
    decimal_set_sign(dst, src_sign);
  }
  if (shift_power < 0) {
    for (int i = 0; !overflow && i != -shift_power; ++i) {
      overflow = decimal_raise_mantissa(dst);
    }
  } else {
    overflow = decimal_set_exponent(dst, shift_power);
  }
  return overflow;
}

int get_float_exponent(float num) {
  int exp = 0;
  if (!(isnan(num) || isinf(num) || num <= 1e-30))
    while (num < 1.0 || num >= 10.0) {
      if (num >= 10.0) {
        num /= 10.0;
        ++exp;
      } else {
        num *= 10.0;
        --exp;
      }
    }
  return exp;
}

int convert_from_decimal_to_int(decimal_t src, int *dst) {
  if (!dst) {
    return 1;
  }
  int src_expo = decimal_get_exponent(&src);
  while (src_expo) {
    decimal_lower_mantissa(&src);
    decimal_set_exponent(&src, --src_expo);
  }

  int convertion_error = 0;
  if (_get_largest_nonzero_mantissa_byte(src.bits, 12) > 3) {
    convertion_error = 1;
  }

  const int value_sign = decimal_get_sign(&src);

  unsigned long tmp_value = 0;
  memcpy(&tmp_value, src.bits, sizeof(long));
  int overflow = (!value_sign && tmp_value > INT_MAX) ||
                 (value_sign && tmp_value > INT_MAX + 1l);
  if (overflow) {
    convertion_error = 1;
  } else {
    int value = (int)tmp_value;
    if (value_sign) {
      value = -1 * (unsigned int)tmp_value;
    }
    *dst = value;
  }
  return convertion_error;
}

int convert_from_decimal_to_float(decimal_t src, float *dst) {
  if (!dst) {
    return 1;
  }
  int initial_trim = (decimal_get_mantissa_scale(src) - 7);
  decimal_t rounded_mantissa = {0};
  decimal_copy_mantissa(&src, &rounded_mantissa);
  if (initial_trim >= 0) {
    decimal_set_exponent(&rounded_mantissa, initial_trim);
    decimal_round(rounded_mantissa, &rounded_mantissa);
  } else {
    initial_trim = 0;
  }
  const float mantissa = (float)(unsigned int)rounded_mantissa.bits[0];
  float value = mantissa / powf(10., decimal_get_exponent(&src) - initial_trim);
  if (decimal_get_sign(&src)) {
    value = -value;
  }
  *dst = value;
  return 0;
}

// cap is bytes count
int _get_largest_nonzero_mantissa_byte(const int *const src, const int cap) {
  int largest_nonzero_byte = 0;
  const unsigned char *src_mantissa_bytes = (const unsigned char *)src;
  for (int i = 0; i < cap; ++i) {
    if (src_mantissa_bytes[i] && i > largest_nonzero_byte) {
      largest_nonzero_byte = i;
    }
  }
  return largest_nonzero_byte;
}

int convert_from_str_to_decimal(const char *str, decimal_t *num) {
  if (!str || !num) {
    return 1;
  }
  int error = 0;
  int digits_after_point_counter = 0;
  int had_a_point = 0;
  int is_a_negative = 0;
  if (*str == '-') {
    is_a_negative = 1;
  }
  if (*str == '-' || *str == '+') {
    ++str;
  }
  memset(num, 0, sizeof(decimal_t));
  while (*str && !error) {
    if (!((*str >= '0' && *str <= '9') || *str == '.')) {
      error = 1;
    } else {
      if (*str == '.') {
        had_a_point = 1;
      } else {
        int current_digit = *str - '0';
        if (decimal_raise_mantissa(num)) {
          error = 1;
        } else {
          decimal_t tmp_num = {0};
          convert_from_int_to_decimal(current_digit, &tmp_num);
          decimal_add(tmp_num, *num, num);
          if (had_a_point) {
            ++digits_after_point_counter;
          }
        }
      }
      ++str;
    }
  }
  if (!error) {
    decimal_set_exponent(num, digits_after_point_counter);
    decimal_set_sign(num, is_a_negative);
  }
  return error;
}

void reverse_str(char *str);

int convert_from_decimal_to_str(const decimal_t *const src_num,
                                char *const str) {
  if (!src_num || !str) {
    return 1;
  }
  decimal_t num = {0};
  memcpy(&num, src_num, sizeof(decimal_t));
  char *curr_str = str;
  int digits_counter = 0;
  int exponent = decimal_get_exponent(&num);
  while (_get_largest_nonzero_mantissa_byte(num.bits, 12) || num.bits[0]) {
    if (digits_counter == exponent) {
      *curr_str = '.';
    } else {
      *curr_str = decimal_lower_mantissa(&num) + '0';
    }
    ++digits_counter;
    ++curr_str;
  }
  if (digits_counter <= exponent) {
    while (digits_counter < exponent) {
      ++digits_counter;
      *curr_str = '0';
      ++curr_str;
    }
    *curr_str = '.';
    ++curr_str;
  }
  if (!digits_counter) {
    *curr_str = '0';
    ++curr_str;
    ++digits_counter;
  }
  if (decimal_get_sign(src_num)) {
    *curr_str = '-';
    ++curr_str;
  }
  curr_str[0] = 0;
  reverse_str(str);
  return 0;
}

void reverse_str(char *str) {
  if (!str) {
    return;
  }
  int l_p = 0;
  if (str[0] == '-') l_p = 1;
  int r_p = strlen(str) - 1;
  while (l_p < r_p) {
    char buf = 0;
    buf = str[l_p];
    str[l_p] = str[r_p];
    str[r_p] = buf;
    ++l_p;
    --r_p;
  }
}
