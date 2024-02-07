#include "s21_decimal.h"

/// @brief определение значения бита по индексу
/// @param value в каком числе ищем
/// @param index индекс интересующего нас бита
/// @return возвращает значение интересующего бита
int s21_get_bit(s21_decimal value, int index) {
  return ((value.bits[index / 32] >> (index % 32)) & 1u);
}

int s21_get_big_bit(s21_big_decimal value, int index) {
  return ((value.bits[index / 32] >> (index % 32)) & 1u);
}

/// @brief задает новое значение бита по индексу
/// @param value заданное число
/// @param index индекс изменяемого бита
/// @param bit на какое значение изменяем
void s21_set_bit(s21_decimal *value, int index, int bit) {
  int mask = 0b1 << (index % 32);
  if (bit == 1) {
    value->bits[index / 32] |= mask;
  } else {
    value->bits[index / 32] &= ~mask;
  }
}

void s21_set_big_bit(s21_big_decimal *value, int index, int bit) {
  int mask = 0b1 << (index % 32);
  if (bit == 1) {
    value->bits[index / 32] |= mask;
  } else {
    value->bits[index / 32] &= ~mask;
  }
}

/// @brief проверяет на пустоту число
/// @param value проверяемое число
/// @return возвращает 0, если число есть, и 1, если числа нет.
int s21_check_empty(s21_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}

/// @brief  обнуляет значение числа
/// @param value обнуляемое число
void s21_make_zero_decimal(s21_decimal *value) {
  for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

void s21_make_zero_big_decimal(s21_big_decimal *value) {
  for (int i = 0; i < 6; i++) value->bits[i] = 0;
}

int s21_get_degree(s21_decimal value) {
  int degree = 0;
  for (int i = 16; i <= 23; i++) {
    degree += ((value.bits[3] >> (i)) & 1u) * pow(2, i - 16);
  }
  return degree;
}

int s21_get_big_degree(s21_big_decimal value) {
  int degree = 0;
  for (int i = 16; i <= 23; i++) {
    degree += ((value.bits[5] >> (i)) & 1u) * pow(2, i - 16);
  }
  return degree;
}

s21_decimal s21_shift_left_decimal(s21_decimal value, int length) {
  while (length > 0) {
    for (int i = 2; i >= 0; i--) {
      int flag = 0;
      if (s21_get_bit(value, i * 32 - 1)) flag = 1;
      value.bits[i] <<= 1;
      if (flag == 1) s21_set_bit(&value, i * 32, 1);
    }
    length--;
  }
  return value;
}

s21_big_decimal s21_shift_left_big_decimal(s21_big_decimal value, int length,
                                           s21_arithmetic_error_code *code) {
  s21_big_decimal copy;
  for (int i = 0; i < 6; i++) copy.bits[i] = value.bits[i];
  int buffer[8] = {0};
  while (length > 0) {
    if (s21_get_big_bit(copy, S21_BIG_MANTISSA_LAST_INDEX) != 1) {
      for (int i = 0; i < 5; i++) {
        buffer[i] = s21_get_big_bit(copy, (i + 1) * 32 - 1);
      }
      for (int i = 4; i > 0; i--) {
        copy.bits[i] <<= 1;
        s21_set_big_bit(&copy, i * 32, buffer[i - 1]);
      }
      copy.bits[0] <<= 1;
    } else {
      *code = arithmetic_BIG;
    }
    length--;
  }
  return copy;
}

void s21_simple_add(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  s21_big_decimal res;
  s21_make_zero_big_decimal(&res);
  int tmp = 0, sum = 0;
  for (int index = 0; index <= S21_BIG_MANTISSA_LAST_INDEX; index++) {
    sum =
        s21_get_big_bit(value_1, index) + s21_get_big_bit(value_2, index) + tmp;
    tmp = sum / 2;
    s21_set_big_bit(&res, index, sum % 2);
  }
  for (int i = 0; i < 6; i++) result->bits[i] = res.bits[i];
}

int s21_from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst) {
  s21_arithmetic_error_code code = arithmetic_OK;
  int degree = s21_get_big_degree(src);
  int sign = s21_get_big_bit(src, S21_BIG_SIGN_INDEX);
  s21_set_big_degree(&src, 0);
  while ((src.bits[4] || src.bits[3]) && (degree > 0)) {
    s21_divide_big_by_ten(&src);
    degree--;
  }
  if (src.bits[4] || src.bits[3]) {
    if (sign == 1)
      code = arithmetic_SMALL;
    else {
      code = arithmetic_BIG;
    }
    s21_make_zero_decimal(dst);
  } else {
    s21_set_big_degree(&src, degree);
    for (int i = 0; i < 4; i++) dst->bits[i] = src.bits[i];
    s21_set_degree(dst, degree);
    s21_set_sign(dst, sign);
  }
  return code;
}

int s21_div_degree(s21_big_decimal *src, int degree) {
  int tmp = 0;
  while ((src->bits[3] || src->bits[4] || src->bits[5]) && degree > 0) {
    if (degree == 1 && src->bits[3]) tmp = 1;
    s21_divide_big_by_ten(src);
    degree--;
  }
  if (tmp && degree == 0 && src->bits[3] == 0 && s21_get_big_bit(*src, 0))
    s21_set_big_bit(src, 0, 0);
  if (src->bits[3] || src->bits[4] || src->bits[5]) degree = -1;
  return degree;
}

int s21_big_degree_alignment(s21_big_decimal *value_1, s21_big_decimal *value_2,
                             s21_big_decimal *result) {
  int sign_value_1 = 0, sign_value_2 = 0, degree_value_1 = 0,
      degree_value_2 = 0;
  s21_arithmetic_error_code code = arithmetic_OK;
  s21_decimal tmp;
  s21_big_decimal tmp1, copy;
  s21_make_zero_decimal(&tmp);
  s21_make_zero_big_decimal(&tmp1);
  degree_value_1 = s21_get_big_degree(*value_1);
  degree_value_2 = s21_get_big_degree(*value_2);
  sign_value_1 = s21_get_big_bit(*value_1, S21_SIGN_INDEX);
  sign_value_2 = s21_get_big_bit(*value_2, S21_SIGN_INDEX);
  s21_from_int_to_decimal(pow(10, abs(degree_value_1 - degree_value_2)), &tmp);
  s21_from_decimal_to_big_decimal(tmp, &tmp1);
  if (degree_value_1 > degree_value_2) {
    for (int i = 0; i < 6; i++) copy.bits[i] = value_2->bits[i];
    code = s21_simple_mul(*value_2, tmp1, &copy);
    s21_set_big_degree(&copy, degree_value_1);
    s21_set_big_bit(&copy, S21_SIGN_INDEX, sign_value_2);
    s21_set_big_degree(result, degree_value_1);
    for (int i = 0; i < 6; i++) value_2->bits[i] = copy.bits[i];
  } else {
    for (int i = 0; i < 6; i++) copy.bits[i] = value_1->bits[i];
    code = s21_simple_mul(*value_1, tmp1, &copy);
    s21_set_big_degree(&copy, degree_value_2);
    s21_set_big_bit(&copy, S21_SIGN_INDEX, sign_value_1);
    s21_set_big_degree(result, degree_value_2);
    for (int i = 0; i < 6; i++) copy.bits[i] = value_1->bits[i];
  }
  return code;
}

int s21_degree_alignment(s21_decimal *value_1, s21_decimal *value_2,
                         s21_decimal *result) {
  int sign_value_1 = 0, sign_value_2 = 0, degree_value_1 = 0,
      degree_value_2 = 0;
  s21_decimal tmp, copy;
  s21_make_zero_decimal(&tmp);
  s21_make_zero_decimal(&copy);
  degree_value_1 = s21_get_degree(*value_1);
  degree_value_2 = s21_get_degree(*value_2);
  sign_value_1 = s21_get_bit(*value_1, S21_SIGN_INDEX);
  sign_value_2 = s21_get_bit(*value_2, S21_SIGN_INDEX);
  s21_from_int_to_decimal(pow(10, abs(degree_value_1 - degree_value_2)), &tmp);
  if (degree_value_1 > degree_value_2) {
    for (int i = 0; i < 4; i++) copy.bits[i] = value_2->bits[i];
    s21_old_mul(*value_2, tmp, &copy);
    s21_set_degree(&copy, degree_value_1);
    s21_set_sign(&copy, sign_value_2);
    s21_set_degree(result, degree_value_1);
    for (int i = 0; i < 4; i++) value_2->bits[i] = copy.bits[i];
  } else {
    for (int i = 0; i < 4; i++) copy.bits[i] = value_1->bits[i];
    s21_old_mul(*value_1, tmp, &copy);
    s21_set_degree(&copy, degree_value_2);
    s21_set_sign(&copy, sign_value_1);
    s21_set_degree(result, degree_value_2);
    for (int i = 0; i < 4; i++) value_1->bits[i] = copy.bits[i];
  }
  return 0;
}

void s21_set_degree(s21_decimal *value, int degree) {
  int degree_argument[8] = {0};
  for (int i = 7; i >= 0; i--) {
    degree_argument[i] = degree % 2;
    degree /= 2;
  }
  for (int i = 0, index = 119; i < 8; i++, index--) {
    s21_set_bit(value, index, degree_argument[i]);
  }
}

void s21_set_big_degree(s21_big_decimal *value, int degree) {
  int degree_argument[8] = {0};
  for (int i = 7; i >= 0; i--) {
    degree_argument[i] = degree % 2;
    degree /= 2;
  }
  for (int i = 0, index = 183; i < 8; i++, index--) {
    s21_set_big_bit(value, index, degree_argument[i]);
  }
}

int s21_simple_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result) {
  s21_big_decimal one;
  int last_ind = 0;
  s21_make_zero_big_decimal(&one);
  one.bits[0] = 1;
  if (s21_is_big_simple_less(value_1, value_2)) {
    value_1 = s21_big_binary_not(value_1);
    last_ind = s21_get_big_last_bit_index(value_2);
    s21_simple_add(value_1, one, &value_1);
  } else {
    value_2 = s21_big_binary_not(value_2);
    last_ind = s21_get_big_last_bit_index(value_1);
    s21_simple_add(value_2, one, &value_2);
  }
  s21_simple_add_for_sub(value_2, value_1, result);
  s21_set_big_bit(result, last_ind + 1, 0);
  return 0;
}

int s21_simple_add_for_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result) {
  s21_big_decimal cpy_res;
  int tmp = 0;
  s21_make_zero_big_decimal(&cpy_res);
  for (int index = 0; index <= S21_MANTISSA_LAST_INDEX + 5; index++) {
    int sum = 0;
    sum =
        s21_get_big_bit(value_1, index) + s21_get_big_bit(value_2, index) + tmp;
    s21_set_big_bit(&cpy_res, index, sum % 2);
    tmp = sum / 2;
  }
  for (int i = 0; i < 6; i++) result->bits[i] = cpy_res.bits[i];
  return 0;
}

int s21_is_simple_less(s21_decimal value_1, s21_decimal value_2) {
  int flag_stop = 0;
  s21_comparison_code code = 0;
  s21_big_decimal val_1, val_2, tmp;
  s21_from_decimal_to_big_decimal(value_1, &val_1);
  s21_from_decimal_to_big_decimal(value_2, &val_2);
  s21_make_zero_big_decimal(&tmp);
  int sign_value_1 = 0, sign_value_2 = 0;
  sign_value_1 = s21_get_sign(value_1);
  sign_value_2 = s21_get_sign(value_2);
  s21_big_degree_alignment(&val_1, &val_2, &tmp);
  s21_make_zero_big_decimal(&tmp);
  int check = s21_is_equal(value_1, value_2);
  if (check) {
    code = comparison_FALSE;
  } else {
    if ((sign_value_1 - sign_value_2) == -1) {
      code = comparison_FALSE;
    } else if ((sign_value_1 - sign_value_2) == 1) {
      code = comparison_TRUE;
    } else {
      for (int i = S21_BIG_MANTISSA_LAST_INDEX; i >= 0 && flag_stop == 0; i--) {
        flag_stop = s21_get_big_bit(val_2, i) - s21_get_big_bit(val_1, i);
      }
      code = (flag_stop == 1) ? comparison_TRUE : comparison_FALSE;
      if (sign_value_1 == 1) {
        if (code == comparison_TRUE)
          code = comparison_FALSE;
        else
          code = comparison_TRUE;
      }
    }
  }
  return code;
}

int s21_is_big_simple_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  int flag = 0;
  s21_comparison_code code = 0;
  for (int index = S21_BIG_MANTISSA_LAST_INDEX; index >= 0 && flag == 0;
       index--) {
    int b1 = 0, b2 = 0;
    b1 = s21_get_big_bit(value_1, index);
    b2 = s21_get_big_bit(value_2, index);
    switch (b1 - b2) {
      case 1:
        code = comparison_FALSE;
        flag = 1;
        break;
      case -1:
        code = comparison_TRUE;
        flag = 1;
        break;
      default:
        break;
    }
  }
  return code;
}

s21_big_decimal s21_big_binary_not(s21_big_decimal value) {
  s21_big_decimal result;
  s21_make_zero_big_decimal(&result);
  for (int i = 0; i < 5; i++) result.bits[i] = ~value.bits[i];
  return result;
}

int s21_simple_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result) {
  s21_arithmetic_error_code code = arithmetic_OK;
  int count = 0;
  s21_make_zero_big_decimal(result);
  for (int i = 0; i <= S21_BIG_MANTISSA_LAST_INDEX; i++) {
    if (s21_get_big_bit(value_2, i)) {
      value_1 = s21_shift_left_big_decimal(value_1, i - count, &code);
      s21_simple_add(value_1, *result, result);
      count = i;
    }
  }
  return code;
}

int s21_get_last_bit_index(s21_decimal value) {
  int last_ind = 0;
  for (int index = S21_MANTISSA_LAST_INDEX; index >= 0 && last_ind == 0;
       index--) {
    if (s21_get_bit(value, index)) last_ind = index;
  }
  return last_ind;
}

int s21_get_big_last_bit_index(s21_big_decimal value) {
  int last_ind = 0;
  for (int index = S21_BIG_MANTISSA_LAST_INDEX; index >= 0 && last_ind == 0;
       index--) {
    if (s21_get_big_bit(value, index)) last_ind = index;
  }
  return last_ind;
}

int s21_divide_by_ten(s21_decimal *value) {
  int divider = 0, last_ind = 0;
  s21_decimal result;
  s21_make_zero_decimal(&result);
  last_ind = s21_get_last_bit_index(*value);
  for (int i = 0; i < last_ind + 2; i++) {
    if (divider >= 10) {
      result = s21_shift_left_decimal(result, 1);
      s21_set_bit(&result, 0, 1);
      divider -= 10;
    } else {
      result = s21_shift_left_decimal(result, 1);
      s21_set_bit(&result, 0, 0);
    }
    int new_bit = s21_get_bit(*value, last_ind - i);
    divider <<= 1;
    divider += new_bit;
  }
  *value = result;
  return (divider >>= 1);
}

int s21_divide_big_by_ten(s21_big_decimal *value) {
  int divider = 0, last_ind = 0;
  s21_arithmetic_error_code code = arithmetic_OK;
  s21_big_decimal result;
  s21_make_zero_big_decimal(&result);
  last_ind = s21_get_big_last_bit_index(*value);
  for (int i = 0; i < last_ind + 2 && code == arithmetic_OK; i++) {
    if (divider >= 10) {
      result = s21_shift_left_big_decimal(result, 1, &code);
      s21_set_big_bit(&result, 0, 1);
      divider -= 10;
    } else {
      result = s21_shift_left_big_decimal(result, 1, &code);
      s21_set_big_bit(&result, 0, 0);
    }
    int new_bit = s21_get_big_bit(*value, last_ind - i);
    divider <<= 1;
    divider += new_bit;
  }
  *value = result;
  return (divider >>= 1);
}

void s21_from_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst) {
  if (dst != NULL) {
    dst->bits[0] = src.bits[0];
    dst->bits[1] = src.bits[1];
    dst->bits[2] = src.bits[2];
    dst->bits[3] = 0;
    dst->bits[4] = 0;
    dst->bits[5] = src.bits[3];
  }
}

int s21_check_big(s21_decimal value_1, s21_decimal value_2) {
  s21_arithmetic_error_code code = 0;
  if ((value_1.bits[0] == UINT_MAX && value_1.bits[1] == UINT_MAX &&
       value_1.bits[2] == UINT_MAX) &&
      !s21_check_empty(value_2)) {
    code = arithmetic_BIG;
  }
  return code;
}

void s21_set_sign(s21_decimal *value, int sign) {
  s21_set_bit(value, S21_SIGN_INDEX, sign);
}

int s21_correct_decimal(s21_decimal value) {
  int ret = 1;
  for (size_t i = 0; i < 3; i++) {
    if (value.bits[i] != 0) ret = 0;
  }
  return ret;
}

int s21_help_round(s21_decimal *value, int point) {
  s21_decimal result;
  s21_make_zero_decimal(&result);
  if (point) {
    s21_truncate(*value, &result);
    if (result.bits[0] + 1u < result.bits[0]) {
    } else {
      result.bits[0] += 1u;
    }
  } else {
    s21_truncate(*value, &result);
  }
  for (int i = 0; i < 4; i++) value->bits[i] = result.bits[i];
  return 0;
}

int s21_get_sign(s21_decimal value) {
  return s21_get_bit(value, S21_SIGN_INDEX);
}

int s21_old_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_error_code code = arithmetic_OK;
  s21_big_decimal val_1, val_2, res;
  s21_make_zero_big_decimal(&res);
  s21_from_decimal_to_big_decimal(value_1, &val_1);
  s21_from_decimal_to_big_decimal(value_2, &val_2);
  int res_sign = (s21_get_sign(value_1) + s21_get_sign(value_2)) % 2;
  code = s21_simple_mul(val_1, val_2, &res);
  s21_set_big_degree(&res, s21_get_degree(value_1) + s21_get_degree(value_2));
  s21_set_big_bit(&res, S21_BIG_SIGN_INDEX, res_sign);
  s21_make_zero_decimal(result);
  if (code == arithmetic_BIG && res_sign) {
    code = arithmetic_SMALL;
  }
  if (!code) code = s21_from_big_decimal_to_decimal(res, result);
  return code;
}

void s21_degree_aligment(s21_big_decimal *value_1, s21_big_decimal *value_2,
                         int degree) {
  if (degree > 0)
    s21_increase_degree(value_2, degree);
  else if (degree < 0)
    s21_increase_degree(value_1, -degree);
}

void s21_increase_degree(s21_big_decimal *value, int degree) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < degree; i++) {
    s21_simple_mul(*value, ten, &tmp);
    *value = tmp;
    s21_make_zero_big_decimal(&tmp);
  }
}

int s21_mult_ten(s21_decimal num, s21_decimal *result) {
  s21_arithmetic_error_code code = 0;
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal sum = {{0}};
  s21_decimal temp = {{0}};
  for (int i = 0; i < 4 && code == arithmetic_OK;
       i++)  // max pos of 1 in ten(1010) = 3, 3+1 = 4
  {
    temp = num;
    if (s21_get_bit(ten, i) == 1) {
      for (int j = 0; j < i && code == arithmetic_OK; j++)
        code = moveLeft(&temp);  // ret = 0  cмогли сдвинуть на бит влево
      if (code == arithmetic_OK)
        code = s21_add(temp, sum,
                       &sum);  // ret = 0 смогли сложить без переполнения
    }
  }
  if (code == arithmetic_OK) *result = sum;
  return code;
}

int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 5; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}
