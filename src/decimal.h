/*
 * Decimal
 *
 * This library implements the type of
 * 96-bit decimal floating point
 * and operations with it
 *
 * Copyright:
 * Eldar dougiela Bagirov
 * Elise carleeme Koenig
 * Denis neutraea Surjikov
 *
 */

#ifndef DECIMAL_LIB
#define DECIMAL_LIB

enum operation_return_status {
  OK,
  TOO_BIG_OR_INF,
  TOO_SMALL_OR_NEG_INF,
  DIVISION_BY_ZERO
};

#include "decimal_arithmetics.h"
#include "decimal_comparison.h"
#include "decimal_convertion.h"
#include "decimal_num.h"

#endif
