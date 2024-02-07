#include "./s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code code = comparison_FALSE;
  s21_decimal zero;
  s21_make_zero_decimal(&zero);
  if (s21_check_empty(value_1) && s21_check_empty(value_2)) {
    code = comparison_FALSE;
  } else {
    code = s21_is_simple_less(value_1, value_2);
  }
  return code;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code result;
  result = (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code code = comparison_TRUE;
  code = !s21_is_less_or_equal(value_1, value_2);
  return code;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code code = comparison_TRUE;
  code = (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2));
  return code;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code code = comparison_TRUE;
  if (s21_check_empty(value_1) && s21_check_empty(value_2)) {
    code = comparison_TRUE;
  } else {
    s21_decimal cpy_value_1, cpy_value_2, tmp;
    s21_make_zero_decimal(&cpy_value_1);
    s21_make_zero_decimal(&cpy_value_2);
    int sign_value_1 = 0, sign_value_2 = 0;
    sign_value_1 = s21_get_bit(value_1, S21_SIGN_INDEX);
    sign_value_2 = s21_get_bit(value_2, S21_SIGN_INDEX);
    if (sign_value_1 != sign_value_2) {
      code = comparison_FALSE;
    } else {
      int degree_value_1 = 0, degree_value_2 = 0;
      degree_value_1 = s21_get_degree(value_1);
      degree_value_2 = s21_get_degree(value_2);
      if (degree_value_1 != degree_value_2)
        s21_degree_alignment(&value_1, &value_2, &tmp);
      for (int index = 0; index < 3 && code == comparison_TRUE; index++) {
        if (value_1.bits[index] != value_2.bits[index]) {
          code = comparison_FALSE;
        }
      }
    }
  }
  return code;
}

/// @brief
/// @param value_1
/// @param value_2
/// @return
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_code code = comparison_FALSE;
  code = !s21_is_equal(value_1, value_2);
  return code;
}
