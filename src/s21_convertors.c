#include "./s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_other_error_code code = other_OK;
  if (abs(src) > S21_MAX_DEC) {
    code = other_ERROR;
  } else if (src == S21_NAN || src == S21_INF) {
    code = other_ERROR;
  } else {
    s21_make_zero_decimal(dst);
    if (src < 0) {
      src *= -1;
      dst->bits[3] = 1 << 31;
    }
    dst->bits[0] = src;
  }
  return code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_other_error_code code = 0;
  if (dst != NULL) {
    s21_make_zero_decimal(dst);
    if (!isnan(src) && !isinf(src) && !-isinf(src)) {
      if (src != 0) {
        char str_num[100] = {0};
        sprintf(str_num, "%e", src);
        code = s21_parser_string(str_num, dst);
        if (code) s21_make_zero_decimal(dst);
      }
    } else
      code = other_ERROR;
  } else
    code = other_ERROR;
  return code;
}

int s21_parser_string(char *str_num, s21_decimal *dst) {
  int error = 0, sign_dec = 0, degree = 0, degree_sign = 0, str_index = 0,
      int_index = 0;
  char degree_E[100] = {0}, str_int_num[100] = {0};
  if (str_num[0] == '-') {
    sign_dec = 1;
    str_index++;
  }

  for (; str_num[str_index] != '\0'; str_index++) {
    if (str_num[str_index] == 'e') {
      if (str_num[++str_index] == '-') degree_sign = 1;
      str_index++;
      for (int i = 0; str_num[str_index] != '\0'; str_index++) {
        degree_E[i] = str_num[str_index];
        degree_E[++i] = '\0';
      }
    } else if (str_num[str_index] != '.') {
      str_int_num[int_index] = str_num[str_index];
      str_int_num[++int_index] = '\0';
    }
  }
  int degree_E_int = atoi(degree_E);

  if (degree_E_int < 23) {
    if (degree_sign)
      degree = 6 + degree_E_int;
    else if (!degree_sign)
      degree = 6 - degree_E_int;

    unsigned int int_num = atoi(str_int_num);
    if (degree > 0) s21_trailing_zeroes(&int_num, &degree);

    if (degree < 29) {
      s21_decimal dec_ten = {{10, 0, 0, 0}};
      dst->bits[0] = int_num;

      if (!degree_sign) {
        for (; degree < 0 && !error; degree++) {
          error = s21_mul(*dst, dec_ten, dst);
        }
        if (error) error = 1;
      }

      s21_set_degree(dst, degree);
      s21_set_sign(dst, sign_dec);
    } else
      error = 1;
  } else
    error = 1;
  return error;
}

void s21_trailing_zeroes(unsigned int *str_num, int *degree) {
  int flag = 1;
  while (flag) {
    if (*str_num % 10 == 0) {
      *str_num /= 10;
      *degree -= 1;
    } else
      flag = 0;
  }
}
// }

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_other_error_code code = other_OK;
  if (!dst) {
    code = other_ERROR;
  } else {
    s21_truncate(src, &src);
    if (src.bits[2] != 0 || src.bits[1] != 0) {
      code = other_ERROR;
    } else if (src.bits[0] >= INT_MAX) {
      code = other_ERROR;
    } else {
      *dst = src.bits[0];
      if (s21_get_bit(src, S21_SIGN_INDEX) == 1) {
        *dst *= -1;
      }
    }
  }
  return code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_other_error_code code = other_OK;
  *dst = 0;
  double result = 0;
  int degree = s21_get_degree(src), last_ind = 0;
  for (int index = S21_MANTISSA_LAST_INDEX; index >= 0 && last_ind == 0;
       index--) {
    if (s21_get_bit(src, index)) last_ind = index;
  }
  for (int i = 0; i <= last_ind; i++) result += s21_get_bit(src, i) * pow(2, i);
  for (int i = 0; i < degree; i++) result /= 10.0;
  *dst = (float)result;
  if (s21_get_bit(src, S21_SIGN_INDEX)) *dst *= -1;
  return code;
}