#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define S21_INF __builtin_inf()
#define S21_NAN __builtin_nan("")
#define S21_NINF __builtin_isinf
#define S21_NNAN __builtin_isnan
#define S21_SIGN_INDEX 127
#define S21_BIG_SIGN_INDEX 191
#define S21_MANTISSA_LAST_INDEX 95
#define S21_BIG_MANTISSA_LAST_INDEX 159
#define S21_BIT_LAST_INDEX 31
#define S21_BEGIN_OF_DEGREE 112
#define S21_DECIMAL_BIT_DEGREE 3
#define S21_BIG_DECIMAL_BIT_DEGREE 5
#define S21_MAX_DEC 2e96 - 1
#define S21_MIN_DEC -2e96 + 1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[6];
} s21_big_decimal;

typedef enum s21_arithmetic_error_code {
  arithmetic_OK = 0,
  arithmetic_BIG = 1,
  arithmetic_SMALL = 2,
  arithmetic_ZERO = 3,
  arithmetic_ERROR = 4
} s21_arithmetic_error_code;

typedef enum s21_comparison_code {
  comparison_FALSE = 0,
  comparison_TRUE = 1
} s21_comparison_code;

typedef enum s21_other_error_code {
  other_OK = 0,
  other_ERROR = 1
} s21_other_error_code;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_get_bit(s21_decimal value, int index);
int s21_get_big_bit(s21_big_decimal value, int index);
void s21_set_bit(s21_decimal *value, int index, int bit);
void s21_set_big_bit(s21_big_decimal *value, int index, int bit);
void s21_bank_round(s21_decimal *value);
int s21_check_empty(s21_decimal value);
int s21_check_empty_big(s21_big_decimal value);
void s21_make_zero_decimal(s21_decimal *value);
void s21_from_decimal_to_big_decimal(s21_decimal value,
                                     s21_big_decimal *cpy_value);
s21_big_decimal s21_shift_left_big_decimal(s21_big_decimal value, int length,
                                           s21_arithmetic_error_code *code);
s21_big_decimal s21_add_big_decimal(s21_big_decimal value_1,
                                    s21_big_decimal value_2);
int s21_from_big_decimal_to_decimal(s21_big_decimal value,
                                    s21_decimal *cpy_value);
int s21_big_degree_alignment(s21_big_decimal *value_1, s21_big_decimal *value_2,
                             s21_big_decimal *result);
int s21_degree_alignment(s21_decimal *value_1, s21_decimal *value_2,
                         s21_decimal *result);
int s21_get_degree(s21_decimal value);
int s21_get_big_decimal_degree(s21_big_decimal value);
s21_decimal s21_abs(s21_decimal value);
s21_big_decimal s21_big_simple_mul(s21_decimal value_1, s21_decimal value_2);
int s21_simple_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result);
int s21_simple_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result);
s21_big_decimal s21_binary_and(s21_big_decimal value_1,
                               s21_big_decimal value_2);
s21_decimal s21_shift_left(s21_decimal value, int count);
s21_decimal s21_shift_one_iter(s21_decimal value);
s21_big_decimal s21_big_simple_add(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
s21_big_decimal s21_big_simple_sub(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
void s21_make_inf(s21_decimal *value);
int s21_get_shift_size(s21_big_decimal value);
s21_big_decimal s21_big_binary_xor(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
int number_of_abbreviations_by_10(s21_big_decimal value);
s21_decimal s21_binary_not(s21_decimal value);
s21_big_decimal s21_big_simple_div(s21_big_decimal value_1,
                                   s21_big_decimal value_2,
                                   s21_big_decimal *remainder);
void s21_set_degree(s21_decimal *value, int degree);
s21_big_decimal s21_big_binary_not(s21_big_decimal value);
int s21_is_simple_less(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_shift_left_decimal(s21_decimal value, int length);
unsigned int s21_divide_int(s21_decimal *value, int divid);
int s21_multiplakete(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_simple_add_for_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result);
int s21_divide_big_by_ten(s21_big_decimal *value);
int s21_divide_by_ten(s21_decimal *value);
void s21_make_zero_big_decimal(s21_big_decimal *value);
int s21_get_big_degree(s21_big_decimal value);
void s21_set_big_degree(s21_big_decimal *value, int degree);
int s21_from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst);
int s21_check_big(s21_decimal value_1, s21_decimal value_2);
int s21_is_big_simple_less(s21_big_decimal value_1, s21_big_decimal value_2);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_sign(s21_decimal value);
int s21_correct_decimal(s21_decimal value);
int s21_get_big_last_bit_index(s21_big_decimal value);
int s21_help_round(s21_decimal *src, int point);
int s21_old_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_degree(s21_big_decimal *src, int degree);
void s21_degree_aligment(s21_big_decimal *value_1, s21_big_decimal *value_2,
                         int degree);

void s21_simple_add(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void s21_increase_degree(s21_big_decimal *value, int degree);

int s21_mult_ten(s21_decimal num, s21_decimal *result);
int moveLeft(s21_decimal *num);
int s21_div_ten(s21_decimal num, s21_decimal *result);
int s21_div_simple(s21_decimal num1, s21_decimal num2, s21_decimal *result);
void moveRightNTimes(s21_decimal *num, int n);
void writeInDecParts(s21_decimal mantissa, int exp, int sign,
                     s21_decimal *result);
void increaseExpByN(s21_decimal *num, int n);
void s21_remove_zeros(s21_decimal *num);
int get_smallestrank_digit(s21_decimal num);
int s21_minus_simple(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_get_last_bit_index(s21_decimal value);
int countDecimalPlaces(float num);
void decimal_zeroing(s21_decimal *dst);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_parser_string(char *str_num, s21_decimal *dst);
void s21_trailing_zeroes(unsigned int *str_num, int *degree);

#endif
