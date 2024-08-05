#ifndef __decimal_num__
#define __decimal_num__

typedef struct {
  int bits[4];
} decimal_t;

void decimal_copy_number(const decimal_t*, decimal_t*);
void decimal_copy_mantissa(const decimal_t*, decimal_t*);

int decimal_get_sign(const decimal_t*);
int decimal_set_sign(decimal_t*, const int);
int decimal_get_exponent(const decimal_t*);
int decimal_set_exponent(decimal_t*, const int);

int decimal_raise_mantissa(decimal_t*);
int decimal_lower_mantissa(decimal_t*);

int decimal_get_mantissa_scale(decimal_t);

int decimal_floor(decimal_t, decimal_t*);
int decimal_round(decimal_t, decimal_t*);
int decimal_truncate(decimal_t, decimal_t*);
int decimal_negate(decimal_t, decimal_t*);

#endif
