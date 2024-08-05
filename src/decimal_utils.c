#include "decimal_utils.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "decimal.h"

int bank_round_long_mantissa(int *six_int_array, int *six_int_exponent) {
  int overflow = 0;
  int tmp_mantissa[6] = {0};
  int previous_digits_were_zero = 1;
  while ((*six_int_exponent > 28 ||
          _get_largest_nonzero_mantissa_byte(six_int_array, 24) > 11) &&
         !overflow) {
    if (*six_int_exponent) {
      int deleted_digit = 0;
      tmp_mantissa[0] =
          ((deleted_digit = lower_long_mantissa(six_int_array, 6)) > 5) ||
          ((deleted_digit == 5) &&
           (((previous_digits_were_zero) && (six_int_array[0] & 1)) ||
            !previous_digits_were_zero));
      previous_digits_were_zero =
          previous_digits_were_zero >> (deleted_digit != 0);
      --(*six_int_exponent);
    } else {
      overflow = 1;
    }
  }
  if (!overflow) {
    overflow = sum_mantissas(tmp_mantissa, six_int_array, six_int_array, 3);
  }
  return overflow;
}

int lower_long_mantissa(int *const mantissa, const int ints_count) {
  if (!mantissa) {
    return 0;
  }
  unsigned int *new_mantissa = calloc(sizeof(unsigned int), ints_count);
  unsigned int *old_mantissa = (unsigned int *)mantissa;
  for (int i = ints_count - 1; i >= 0; --i) {
    if (i < ints_count - 1) {
      long tmp = 0;
      memcpy(&tmp, old_mantissa + i, sizeof(long));
      long tmp_ten = tmp / 10;
      tmp = tmp % 10;
      memcpy(new_mantissa + i, &tmp_ten, sizeof(int));
      memcpy(old_mantissa + i, &tmp, sizeof(int));
    } else {
      new_mantissa[i] = (old_mantissa[i]) / 10;
      old_mantissa[i] = (old_mantissa[i]) % 10;
    }
  }
  int remainder = ((unsigned char *)old_mantissa)[0];
  memcpy(mantissa, new_mantissa, sizeof(int) * ints_count);
  free(new_mantissa);
  return remainder;
}

int raise_long_mantissa(int *const mantissa, const int ints_count) {
  if (!mantissa) {
    return 0;
  }
  int overflow = 0;
  unsigned int *new_mantissa = calloc(sizeof(unsigned int), ints_count);
  unsigned int *old_mantissa = (unsigned int *)mantissa;
  for (int i = 0; i < ints_count; ++i) {
    long current_raised = old_mantissa[i] * 10l + new_mantissa[i];
    if (i != ints_count - 1) {
      memcpy(new_mantissa + i, &current_raised, sizeof(long));
    } else {
      if (current_raised <= UINT_MAX) {
        new_mantissa[i] = current_raised;
      } else {
        overflow = 1;
      }
    }
  }
  if (!overflow) memcpy(mantissa, new_mantissa, sizeof(int) * ints_count);
  free(new_mantissa);
  return overflow;
}

// size is in ints count
int sum_mantissas(const int *v1, const int *v2, int *res, const int size) {
  if (!v1 || !v2 || !res || size < 1) {
    return 1;
  }
  const unsigned int *v1_c = (const unsigned int *)v1;
  const unsigned int *v2_c = (const unsigned int *)v2;
  unsigned int *res_c = calloc(sizeof(int), size);
  int overflow = 0;
  for (int i = 0; !overflow && i != size; ++i) {
    long current = (long)v1_c[i] + v2_c[i] + res_c[i];
    overflow = (i == size - 1) && (current > UINT_MAX);
    if (i == size - 1) {
      *(res_c + i) = current & UINT_MAX;
    } else {
      memcpy(res_c + i, &current, sizeof(long));
    }
  }
  memcpy(res, res_c, sizeof(int) * size);
  free(res_c);
  return overflow;
}

void to_twos_complement(unsigned int *arr, int len) {
  unsigned int carry_bit_value = 1;
  unsigned int temp;
  for (int i = 0; i < len; ++i) {
    temp = ~arr[i];
    arr[i] = ~arr[i] + carry_bit_value;
    if (temp > arr[i])
      carry_bit_value = 1;
    else
      carry_bit_value = 0;
  }
}

void mantissa_twos_complement_add(unsigned int *mant1, unsigned int *mant2,
                                  unsigned int *res, int size) {
  unsigned int carry = 0;
  for (int i = 0; i < size; ++i) {
    long tmp_res = (long)mant1[i] + mant2[i] + (long)carry;
    carry = (tmp_res & (1l << 32)) > 0;
    res[i] = tmp_res & 0xFFFFFFFF;
  }
}

int is_mantissa_less(const unsigned int *num1, const unsigned int *num2,
                     int length) {
  int flag = 0;
  for (int i = length - 1; (i >= 0) && (flag == 0); --i) {
    if (num1[i] < num2[i])
      flag = 1;
    else if (num1[i] > num2[i])
      flag = -1;
  }
  return (flag == 1) ? 1 : 0;
}

int sub_mantissa(const int *mant_1, const int *mant_2, int *result,
                 const int size) {
  int result_sign = is_mantissa_less((const unsigned int *)mant_1,
                                     (const unsigned int *)mant_2, size);
  unsigned int *mant_complement = calloc(size, sizeof(int));
  unsigned int *temp_mant = calloc(size, sizeof(int));
  if (result_sign) {
    memcpy(mant_complement, mant_1, size * 4);
    memcpy(temp_mant, mant_2, size * 4);
    to_twos_complement(mant_complement, size);
  } else {
    memcpy(mant_complement, mant_2, size * 4);
    memcpy(temp_mant, mant_1, size * 4);
    to_twos_complement(mant_complement, size);
  }
  mantissa_twos_complement_add(mant_complement, temp_mant,
                               (unsigned int *)result, size);
  free(mant_complement);
  free(temp_mant);
  return result_sign;
}

// size in bytes
int raise_binary(int *const mantissa, const int size) {
  unsigned char *mantissa_ch = (unsigned char *)mantissa;
  for (int i = size - 1; i >= 0; --i) {
    int raised = (int)mantissa_ch[i] << 1;
    mantissa_ch[i] = raised & 0xFF;
    if (i < size - 1) {
      mantissa_ch[i + 1] += (raised & 256) > 0;
    }
  }
  return 0;
}

int lower_binary(int *const mantissa, const int size) {
  unsigned char *mantissa_ch = (unsigned char *)mantissa;
  for (int i = 0; i != size; ++i) {
    int lowered = (int)mantissa_ch[i] >> 1;
    if (i) {
      mantissa_ch[i - 1] += (mantissa_ch[i] & 1) << 7;
    }
    mantissa_ch[i] = lowered & 0xFF;
  }
  return 0;
}

void twos_complement_add(decimal_t value_1, decimal_t value_2, decimal_t *res) {
  int mant1[6] = {0};
  int mant2[6] = {0};
  int result[6] = {0};
  memcpy(mant1, value_1.bits, 12);
  memcpy(mant2, value_2.bits, 12);
  int exp1 = decimal_get_exponent(&value_1);
  int exp2 = decimal_get_exponent(&value_2);
  int invert = 0;
  if (exp1 < exp2) {
    invert = 1;
    int temp[6] = {0};
    memcpy(temp, mant1, 12);
    memcpy(mant1, mant2, 12);
    memcpy(mant2, temp, 12);
    exp1 = exp2;
    exp2 = decimal_get_exponent(&value_1);
  }
  while (exp1 != exp2) {
    exp2 += 1;
    raise_long_mantissa(mant2, 6);
  }
  int result_sign = sub_mantissa(mant1, mant2, result, 6);
  if (invert) result_sign = 1 - result_sign;
  bank_round_long_mantissa(result, &exp1);
  if (res) {
    memset(res, 0, sizeof(decimal_t));
    memcpy(res->bits, result, 12);
    decimal_set_exponent(res, exp1);
    decimal_set_sign(res, result_sign);
  }
}
