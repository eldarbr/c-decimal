#include <stdlib.h>
#include <string.h>

#include "decimal.h"
#include "decimal_utils.h"

void raw_sub(const int *a, const int *b, int *res, const int size);

void divide_uint(const int *numerator, const int *divisor, int *quotient,
                 int *remainder);

void get_quotient_mantissa(const int *const numerator, const int *const divisor,
                           int *const quotient, int *const quotient_exponent) {
  *quotient_exponent = 0;
  int first_division = 1;
  int remainder[4] = {0};
  int numerator_copy[4] = {0};
  memcpy(numerator_copy, numerator, 12);
  int divisor_copy[4] = {0};
  memcpy(divisor_copy, divisor, 12);
  const int zeromem[6] = {0};
  memset(quotient, 0, 24);
  int overflow = 0;
  while (first_division || (!overflow && memcmp(remainder, zeromem, 12))) {
    overflow = raise_long_mantissa(quotient, 6);
    if (!overflow && first_division) {
      divide_uint(numerator_copy, divisor_copy, quotient, remainder);
      first_division = 0;
    } else if (!overflow) {
      int new_quotient_digit[6] = {0};
      overflow = raise_long_mantissa(remainder, 4);
      divide_uint(remainder, divisor_copy, new_quotient_digit, remainder);
      *quotient_exponent += 1;
      sum_mantissas(quotient, new_quotient_digit, quotient, 6);
    }
  }
}

int decimal_div(decimal_t value_1, decimal_t value_2, decimal_t *result) {
  const decimal_t zero = {0};
  if (decimal_is_equal(value_2, zero)) {
    return DIVISION_BY_ZERO;
  }
  const int result_sign =
      decimal_get_sign(&value_1) ^ decimal_get_sign(&value_2);
  int quotient[6] = {0};
  int quotient_expo = 0;
  get_quotient_mantissa(value_1.bits, value_2.bits, quotient, &quotient_expo);
  const int expo_shift =
      decimal_get_exponent(&value_1) - decimal_get_exponent(&value_2);
  int resulting_expo = quotient_expo + expo_shift;
  int overflow = 0;
  while (!overflow && resulting_expo < 0) {
    overflow = raise_long_mantissa(quotient, 6);
    ++resulting_expo;
  }
  if (!overflow) {
    overflow = bank_round_long_mantissa(quotient, &resulting_expo);
  }
  if (result) {
    memset(result, 0, sizeof(decimal_t));
  }
  if (!overflow && result) {
    memset(result->bits, 0, 16);
    memcpy(result->bits, quotient, 12);
    decimal_set_exponent(result, resulting_expo);
    decimal_set_sign(result, result_sign);
  }
  overflow = overflow > 0;
  return overflow << result_sign;
}

void raw_sub(const int *a, const int *b, int *res, const int size) {
  unsigned int *mant_complement = calloc(size, sizeof(int));
  unsigned int *temp_mant = calloc(size, sizeof(int));
  memcpy(mant_complement, b, size * 4);
  memcpy(temp_mant, a, size * 4);
  to_twos_complement(mant_complement, size);
  mantissa_twos_complement_add(mant_complement, temp_mant, (unsigned int *)res,
                               size);
  free(mant_complement);
  free(temp_mant);
}

#define _regQ_size 4               // regQ is 4 ints long
#define _regA_size _regQ_size + 1  // regA is 4+1 ints long
#define _regM_size _regA_size      // to match with regA for add and substract
void divide_uint(const int *numerator, const int *divisor, int *quotient,
                 int *remainder) {
  int regAQ[_regA_size + _regQ_size];
  int *const regA = regAQ + _regQ_size;
  int *const regQ = regAQ;
  int regM[_regM_size];
  memset(regAQ, 0, sizeof(int) * (_regA_size + _regQ_size));
  memset(regM, 0, sizeof(int) * (_regM_size));
  memcpy(regQ, numerator, _regQ_size * sizeof(int));
  memcpy(regM, divisor, _regQ_size * sizeof(int));

  int N = sizeof(int) * 8 * _regQ_size;

  int regA_sign = 0;

  while (N) {
    raise_binary(regAQ, (_regA_size + _regQ_size) * sizeof(int));
    if (regA_sign) {
      sum_mantissas(regA, regM, regA, _regM_size);
    } else {
      raw_sub(regA, regM, regA, _regM_size);
    }
    regA_sign = regA[_regA_size - 1] & 1;
    if (!regA_sign) {
      regQ[0] += 1;
    }
    --N;
  }
  if (regA_sign) {
    sum_mantissas(regA, regM, regA, _regM_size);
  }
  memset(quotient, 0, sizeof(int) * _regQ_size);
  memset(remainder, 0, sizeof(int) * _regQ_size);
  memcpy(quotient, regQ, sizeof(int) * _regQ_size);
  memcpy(remainder, regA, sizeof(int) * _regQ_size);
}
#undef _regQ_size
#undef _regA_size
#undef _regM_size
