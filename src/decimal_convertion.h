#ifndef __decimal_convertion__
#define __decimal_convertion__

#include "decimal_num.h"

int convert_from_int_to_decimal(int src, decimal_t *dst);
int convert_from_float_to_decimal(float src, decimal_t *dst);
int convert_from_decimal_to_int(decimal_t src, int *dst);
int convert_from_decimal_to_float(decimal_t src, float *dst);

int convert_from_str_to_decimal(const char *, decimal_t *);
int convert_from_decimal_to_str(const decimal_t *, char *);

#endif
