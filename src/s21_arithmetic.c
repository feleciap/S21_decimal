#include "./s21_decimal.h"

/// @brief находит результат сложение двух чисел типа decimal.
/// @param value_1 первое слагаемое
/// @param value_2 второе слагаемое
/// @param result результат сложения чисел value_1 и value_2
/// @return код ошибки: OK = 0, BIG = 1, SMALL = 2, ZERRO = 3, ERROR = 4
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_error_code code = arithmetic_OK;
  if (result != NULL) {
    int get = 0, sign_res = 0;
    s21_make_zero_decimal(result);
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      sign_res = 1;
    }
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
      int sign = 0;
      sign = s21_get_sign(value_1);
      s21_set_bit(&value_1, S21_SIGN_INDEX, 0);
      s21_set_bit(&value_2, S21_SIGN_INDEX, 0);
      code = sign ? s21_sub(value_2, value_1, result)
                  : s21_sub(value_1, value_2, result);
    } else {
      s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
      int degree = 0;
      s21_from_decimal_to_big_decimal(value_1, &val_1);
      s21_from_decimal_to_big_decimal(value_2, &val_2);
      val_1.bits[5] = 0;
      val_2.bits[5] = 0;
      int diff = s21_get_degree(value_1) - s21_get_degree(value_2);
      if (diff > 0) {
        get = s21_get_degree(value_1);
        s21_set_degree(&value_2, get);
      } else {
        get = s21_get_degree(value_2);
        s21_set_degree(&value_1, get);
      }
      s21_degree_aligment(&val_1, &val_2, diff);
      s21_simple_add(val_1, val_2, &res);
      degree = s21_div_degree(&res, s21_get_degree(value_1));
      if (degree >= 0) {
        for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];
        s21_set_degree(result, degree);
      } else {
        code = 1;
      }
    }
    if (code == arithmetic_OK) {
      if (s21_check_empty(*result))
        result->bits[3] = 0;
      else
        sign_res == 1 ? s21_set_sign(result, 1) : 0;
    }

    if (code == arithmetic_BIG && s21_get_sign(*result))
      code = arithmetic_SMALL;
    if (code) s21_make_zero_decimal(result);
  } else
    code = arithmetic_BIG;

  return code;
}

/// @brief находит разность двух чисел: из value_1 value_2.
/// @param value_1 Уменьшаемое -- число, из которого вычитают
/// @param value_2 Вычитаемое -– число, которое вычитают
/// @param result Разность -- результат вычитания value_2 из value_1
/// @return код ошибки: OK = 0, BIG = 1, SMALL = 2, ZERRO = 3, ERROR = 4
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0, degree = 0, sign_res = 0;
  s21_make_zero_decimal(result);
  if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
    s21_decimal temp1 = value_1;
    value_1 = value_2;
    value_2 = temp1;
    s21_set_bit(&value_1, S21_SIGN_INDEX, 0);
    s21_set_bit(&value_2, S21_SIGN_INDEX, 0);
  }
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    s21_get_sign(value_1) ? sign_res = 1 : 1;
    s21_set_bit(&value_1, S21_SIGN_INDEX, 0);
    s21_set_bit(&value_2, S21_SIGN_INDEX, 0);
    code = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
    s21_from_decimal_to_big_decimal(value_1, &val_1);
    s21_from_decimal_to_big_decimal(value_2, &val_2);
    val_1.bits[5] = 0;
    val_2.bits[5] = 0;
    int diff = s21_get_degree(value_1) - s21_get_degree(value_2);
    diff > 0 ? s21_set_degree(&value_2, s21_get_degree(value_2) + diff)
             : s21_set_degree(&value_1, s21_get_degree(value_1) - diff);
    s21_degree_aligment(&val_1, &val_2, diff);
    if (s21_is_greater_big_decimal(val_2, val_1)) {
      s21_big_decimal temp2 = val_1;
      val_1 = val_2;
      val_2 = temp2;
      s21_set_sign(result, 1);
    }
    s21_simple_sub(val_1, val_2, &res);
    degree = s21_div_degree(&res, s21_get_degree(value_1));
    if (degree >= 0) {
      for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];
      s21_set_degree(result, degree);
    } else {
      code = arithmetic_BIG;
    }
  }
  sign_res == 1 ? s21_set_sign(result, 1) : 0;
  if (code == arithmetic_BIG && s21_get_sign(*result)) code = arithmetic_SMALL;
  if (code) s21_make_zero_decimal(result);
  return code;
}

/// @brief находит произведение чисел value_1 и value_2
/// @param value_1 первый множитель
/// @param value_2 второй множитель
/// @param result произведение чисел value_1 и value_2
/// @return код ошибки: OK = 0, BIG = 1, SMALL = 2, ZERRO = 3, ERROR = 4
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_error_code code = arithmetic_OK;
  if (result != NULL) {
    s21_make_zero_decimal(result);
    int degree = 0;
    s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
    s21_from_decimal_to_big_decimal(value_1, &val_1);
    s21_from_decimal_to_big_decimal(value_2, &val_2);
    val_1.bits[5] = 0;
    val_2.bits[5] = 0;
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) s21_set_sign(result, 1);
    degree = s21_get_degree(value_1) + s21_get_degree(value_2);
    code = s21_simple_mul(val_1, val_2, &res);
    degree = s21_div_degree(&res, degree);
    if (degree >= 0) {
      for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];  // check
      if (!s21_check_empty(*result)) s21_set_degree(result, degree);
    } else {
      code = arithmetic_BIG;
    }
    if (code == arithmetic_BIG && s21_get_sign(*result))
      code = arithmetic_SMALL;
    if (code) s21_make_zero_decimal(result);
  } else
    code = arithmetic_BIG;
  return code;
}

/// @brief находит честное от деления valuq_1 на value_2
/// @param value_1 Делимое -- число которое делят
/// @param value_2 Делитель -- число на которое делят
/// @param result частное от деления valuq_1 на value_2
/// @return код ошибки: OK = 0, BIG = 1, SMALL = 2, ZERRO = 3, ERROR = 4
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_error_code code = arithmetic_OK;
  // if (s21_correct_decimal(value_2) == 0 || !result)  //добавил result = NULL
  //   code = arithmetic_ZERO;                          //деление на 0
  // else if (s21_correct_decimal(value_1) == 0) {  // 0 делить на x равно 0
  //   decimal_zeroing(result);
  // } else {
  if (s21_correct_decimal(value_2) == 1 || !result ||
      s21_check_empty(value_2)) {
    code = arithmetic_ZERO;
    s21_make_zero_decimal(result);
  } else if (s21_check_empty(value_1))
    s21_make_zero_decimal(result);
  else {
    s21_make_zero_decimal(result);
    int whileStop = 0;
    int degree_1 = s21_get_degree(value_1), degree_2 = s21_get_degree(value_2);
    int sign = s21_get_bit(value_1, S21_SIGN_INDEX) +
               s21_get_bit(value_2, S21_SIGN_INDEX);  //знак децимала
    s21_decimal temp = {{0, 0, 0, 0}};
    s21_decimal temp1 = value_1, temp2 = value_2;
    /*
        need to make mantissa value_1 as big as possible or at least bigger than
       value_2 for better accuracy then divide_simple and calculate delta =
       exp1-exp2, if delta less than 0 then multiply division by 10 and delta +=
       1 if cant multiply until delta == 0 than we got number bigger than 2^32
    */
    // increase mantissa of temp1 as possible
    while (s21_mult_ten(temp1, &temp1) == 0) degree_1 += 1;
    while (s21_is_less(value_1, value_2) == 1 /*1 = true*/ &&
           whileStop == 0)  /// make mantissas of temp1 >= temp2
    {
      if (s21_div_ten(temp2, &temp2) == 0)
        degree_2 -= 1;
      else
        whileStop = 1;
    }
    // here we must have mantissa of temp1 > temp2
    s21_div_simple(temp1, temp2, &temp);  // just divide prepared mantissas
    int delta = degree_1 - degree_2;  //результирующя степень после деления

    // cant have a*10^3, so make 10a*10^2 and so on until 10^0,
    // or until cant multiply by 10
    while (delta < 0 &&
           code == arithmetic_OK)  //степень должна быть больше либо равна 0
    {
      if (s21_mult_ten(temp, &temp) == 0)
        delta += 1;
      else
        code = arithmetic_BIG;  // bigger than 2^32 of +inf
    }
    if (delta >= 0 && code == arithmetic_OK) {
      while (delta > 29 &&
             code == arithmetic_OK)  //если степень больше 29 надо делить
                                     //мантиссу на 10 до степени 28
      {
        if (s21_div_ten(temp, &temp) == 0)
          delta = delta - 1;
        else
          code = arithmetic_SMALL;  // smaller than 1*10^-28
      }
      if (delta <= 28 && code == arithmetic_OK && result) {
        writeInDecParts(temp, delta, sign, result);
        s21_remove_zeros(result);
      }
    }
  }
  return code;
}

int moveLeft(s21_decimal *num)  // move left mantiss by ONE bit:    0001 1011
                                // 0101  -> 0011 0110 1010
{
  int lastBit = s21_get_bit(*num, 95);
  //если старший бит (96-ой) в 3 части мантиссы (bits[2]) равен 0 то мы можем
  //сместить все биты влево, иначе будет переполнение:  GOOD 01101 -> 11010; BAD
  // af 10010 -> 00100
  if (!lastBit) {
    int highBit = 0;
    for (int i = 2; i > 0; i--) {
      highBit = s21_get_bit(
          *num,
          (i - 1) * 32 + 31);  //сохраним старший бит предыдущей части мантиссы
      num->bits[i] <<= 1;      //сдвигаем влево
      s21_set_bit(
          num, i * 32,
          highBit);  //перепишем младший бит i части старшим битом i-1 части:
                     // 0101 0110 то будет 0100 0110
    }
    num->bits[0] <<= 1;  //тупо сдвигаем низшую часть мантиссы
  }
  return lastBit;  //если 0 то все хорошо, 1 - число не было сдвинуто на бит
}

int s21_div_ten(s21_decimal num, s21_decimal *result) {
  int code = 1;
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  if (!s21_div_simple(num, ten, &temp)) {
    *result = temp;
    code = 0;
  }
  return code;
}

int s21_div_simple(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int ret = 0;
  s21_decimal div = {{0}};            //результат
  s21_decimal temp = {{0, 0, 0, 0}};  //временный децимал
  s21_decimal mid = num1;  //промежуточный децимал
  int max1 = s21_get_last_bit_index(num1), maxBitPos = 0;
  int zero = s21_is_equal(num2, div);
  if (s21_is_greater_or_equal(num1, num2) &&
      zero == 0)  //проверяем если делимое больше или равно делителя, делитель
                  //не равен 0
  {
    for (int i = max1; i >= 0; i--) {  //проходим со старшего бита в делимом
      temp = mid;  //записываем временную мантиссу, которая на каждом
      moveRightNTimes(&temp, i);  //смещаем пока temp не станет >= num2
      if (s21_is_greater_or_equal(temp, num2))  //когда temp >= num2
      {
        s21_minus_simple(temp, num2, &temp);  //записываем в temp остаток
        maxBitPos = s21_get_last_bit_index(
            temp);  //находим старший бит остатка равный 1
        for (int j = 0; j <= maxBitPos;
             j++)  //теперь должны переписать этот остаток в промежуточный
                   //децимал начиная с i позиции
          s21_set_bit(&mid, j + i, s21_get_bit(temp, j));
        for (int j = i + maxBitPos + 1; j <= max1;
             j++)  //а все старшие не 0 биты заменить на 0
          s21_set_bit(&mid, j, 0);
        s21_set_bit(&div, i, 1);  //запишем в результат в позицию i ответ 1
      } else
        s21_set_bit(&div, i,
                    0);  //если временный децимал оказался меньше num2 то в
                         //ответ пишем 0 и дальше продолжаем смещение
    }
  } else
    ret = 2;               // small number
  if (zero == 1) ret = 1;  // infinity
  if (ret == 0) *result = div;
  return ret;
}

void moveRightNTimes(
    s21_decimal *num,
    int n)  // move right by n bits:    0001 1011 0101  -> 0000 1101 1010
{
  int firstBit;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < 2; i++) {
      firstBit = s21_get_bit(
          *num, (i + 1) * 32);  //сохраним младший бит следующей части мантиссы
      num->bits[i] >>= 1;       // move right by 1 bit
      s21_set_bit(num, i * 32 + 31,
                  firstBit);  //перепишем старший бит i части младшим битом i+1
                              //части: 0101 0110 то будет 0101 1110
    }
    num->bits[2] >>= 1;  //тупо сдвигаем высшую часть мантиссы вправо
                         // printDec(*num);
  }
}

void writeInDecParts(s21_decimal mantissa, int exp, int sign,
                     s21_decimal *result) {
  if (result)  //если норм с памяться наверно
  {
    s21_decimal res = {0};
    res.bits[0] = mantissa.bits[0];
    res.bits[1] = mantissa.bits[1];
    res.bits[2] = mantissa.bits[2];
    increaseExpByN(&res, exp);
    s21_set_bit(&res, S21_SIGN_INDEX, sign);
    *result = res;
  }
}

void increaseExpByN(s21_decimal *num, int n) {
  int add = n * (1 << 16);
  num->bits[3] += add;
}

// position of highest bit (0..95) with 1 value
int findMaxBit(s21_decimal num) {
  int max = 0, stop = 0;
  for (int i = 95; i >= 0 && !stop; i--) {
    if (s21_get_bit(num, i) == 1) {
      max = i;
      stop = 1;
    }
  }
  return max;
}

// 3000*10^-3  -> 3*10^0
void s21_remove_zeros(s21_decimal *num) {
  s21_decimal temp = *num, mid = {0};
  int lastDigit = get_smallestrank_digit(temp), stop = 0,
      exp = s21_get_degree(temp), memexp = 0;
  int sign = s21_get_bit(*num, S21_SIGN_INDEX);
  memexp = exp;
  while (stop == 0 && exp > 0) {
    /*
    123/10 = 12
    12*10 = 120
    123 != 120 - значит нельзя сократить мантиссу

    1230/10 = 123
    123*10 = 1230
    1230 == 1230 значит можно сократить мантиссу
    */
    mid = temp;
    lastDigit = get_smallestrank_digit(temp);
    if (s21_div_ten(temp, &temp) == 1)
      stop = 1;
    else {
      s21_mult_ten(temp, &temp);
      if (s21_is_equal(temp, mid) == 0) {
        stop = 1;
        temp.bits[0] += lastDigit;
      } else {
        s21_div_ten(temp, &temp);
        exp -= 1;
      }
    }
  }
  int delta = memexp - exp;
  if (delta) {
    for (int i = 0; i < (memexp - exp); i++) {
      s21_div_ten(*num, num);
    }
    num->bits[3] = 0;
    s21_set_bit(num, 127, sign);
    increaseExpByN(num, exp);
    // printf("delta = %d\n", delta);
  }
}

int get_smallestrank_digit(s21_decimal num) {
  s21_decimal temp = num;
  s21_div_ten(temp, &temp);   // 123:10 = 12
  s21_mult_ten(temp, &temp);  // 12*10 = 120
  s21_minus_simple(
      num, temp, &temp);  // 123-120 = 3 - цифра младшего разряда в мантиссе num
  return temp.bits[0];
}

int s21_minus_simple(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int ret = 0, next = 0, maxBitWithOne = 0, s = 0;
  s21_decimal temp = {{0}}, t1 = {{0}}, t2 = {{0}};
  if (s21_is_less(value_1, value_2) == 1) {
    t1 = value_2;
    t2 = value_1;
  } else {
    t1 = value_1;
    t2 = value_2;
  }

  maxBitWithOne = findMaxBit(t1);
  for (int i = 0; i < maxBitWithOne + 1; i++) {
    s = s21_get_bit(t1, i) - s21_get_bit(t2, i) - next;
    if (s < 0) {
      next = 1;
      s21_set_bit(&temp, i, s + 2);
    } else {
      s21_set_bit(&temp, i, s);
      next = 0;
    }
  }
  *result = temp;
  return ret;
}