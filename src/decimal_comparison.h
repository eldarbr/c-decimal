#ifndef __decimal_comparison__
#define __decimal_comparison__

#include "decimal_num.h"

int decimal_is_equal(decimal_t, decimal_t);
int decimal_is_less(decimal_t, decimal_t);
int decimal_is_not_equal(decimal_t, decimal_t);
int decimal_is_less_or_equal(decimal_t, decimal_t);
int decimal_is_greater(decimal_t, decimal_t);
int decimal_is_greater_or_equal(decimal_t, decimal_t);

#endif
