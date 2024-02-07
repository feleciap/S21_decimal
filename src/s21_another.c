#include "./s21_decimal.h"

/// @brief округляет число в сторону отрицательно бесконечности
/// @param value число, которое требуется округлить
/// @param result число, в которое передастся результат округления
/// @return код ошибки OK = 1, ERROR = 0
int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_other_error_code code = other_OK;
  s21_decimal tmp;
  for (int i = 0; i < 4; i++) tmp.bits[i] = value.bits[i];
  unsigned int number = 0;
  int sign = s21_get_bit(value, S21_SIGN_INDEX);
  int degree = s21_get_degree(value), point = 0;
  if (sign) {
    for (int i = 0; i < degree && !number; i++) {
      number += s21_divide_by_ten(&tmp);
    }
    point = 0;
    if (number > 0) point = 1;
    s21_help_round(&value, point);
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  } else {
    s21_truncate(value, result);
  }
  return code;
}

/// @brief округляет число до ближайшего целого числа.
/// @param value число, которое требуется округлить
/// @param result число, в которое передастся результат округления
/// @return код ошибки OK = 1, ERROR = 0
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_other_error_code code = other_ERROR;
  s21_decimal tmp;
  s21_make_zero_decimal(&tmp);
  for (int i = 0; i < 4; i++) tmp.bits[i] = value.bits[i];
  unsigned int number = 0, plus = 0;
  int degree = s21_get_degree(value), point = 0;
  for (int i = 0; i < degree; i++) {
    number = s21_divide_by_ten(&tmp);
    plus += number;
  }
  plus -= number;
  if ((number == 5 && plus > 0) || number > 5) point = 1;
  s21_help_round(&value, point);
  code = other_OK;
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  return code;
}

/// @brief Возвращает целые цифры указанного числа; любые дробные цифры
/// отбрасываются, включая конечные нули.
/// @param value число, дробную часть которого необходимо отбросить
/// @param result число, в которое передастся результат
/// @return код ошибки OK = 1, ERROR = 0
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int sign = 0, degree = 0;
  if (result != NULL) {
    sign = s21_get_bit(value, S21_SIGN_INDEX);
    degree = s21_get_degree(value);
    for (int i = 0; i < degree; i++) {
      s21_divide_by_ten(&value);
    }
    *result = value;
    s21_set_sign(result, sign);
    s21_set_degree(result, 0);
  }

  return 0;
}

/// @brief Возвращает результат умножения указанного на -1.
/// @param value число, знак которого необходимо изменить на противоположный
/// @param result число, в которое передастся результат
/// @return код ошибки OK = 1, ERROR = 0
int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_other_error_code code = other_ERROR;
  if (result) {
    result->bits[3] = value.bits[3];
    result->bits[3] ^= (1 << 31);
    for (int i = 0; i < 3; i++) {
      result->bits[i] = value.bits[i];
    }
    code = other_OK;
  }
  return code;
}
