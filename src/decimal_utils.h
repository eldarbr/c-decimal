#ifndef __decimal__utils__
#define __decimal__utils__

#include "decimal.h"

int _get_largest_nonzero_mantissa_byte(const int *, const int);
int bank_round_long_mantissa(int *six_int_array, int *six_int_exponent);
int lower_long_mantissa(int *const mantissa, const int ints_count);
int raise_long_mantissa(int *const mantissa, const int ints_count);
int sum_mantissas(const int *, const int *, int *, const int);
int sub_mantissa(const int *mant_1, const int *mant_2, int *result,
                 const int size);

int raise_binary(int *, const int);
int lower_binary(int *, const int);
void mantissa_twos_complement_add(unsigned int *mant1, unsigned int *mant2,
                                  unsigned int *res, int size);
void to_twos_complement(unsigned int *arr, int len);

#endif
