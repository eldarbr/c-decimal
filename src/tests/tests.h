#ifndef __DECIMAL_TESTS
#define __DECIMAL_TESTS

#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../decimal.h"

Suite *ts_add(void);
Suite *ts_mul(void);
Suite *ts_comparison(void);
Suite *ts_float_converters(void);
Suite *ts_sub(void);
Suite *ts_negate(void);
Suite *ts_dtoi(void);
Suite *ts_div(void);
Suite *ts_rounding(void);

#endif
