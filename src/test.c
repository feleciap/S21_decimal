
#include <check.h>
#include <math.h>

#include "s21_decimal.h"
#define CONVERTING_ERROR 1
#define OK 0
#define SIGN 0x80000000
#define TRUE 1
#define FALSE 0
#define INF 1
#define NINF 2
#define NAN12 3
#define SUCCESS 0
// Функции сравнения:

START_TEST(s21_is_greater_1) {
  s21_decimal value_1 = {{123, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{12, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal value_1 = {{12, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal value_1 = {{123456, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0x10000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_8) {
  s21_decimal value_1 = {{234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{2, 0, 0, 0x80000000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_9) {
  s21_decimal value_1 = {{234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_11) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_13) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_15) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_degree(&value_2, 10);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_16) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_set_degree(&value_1, 2);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0x10000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_9) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0}};
  s21_set_degree(&value_2, 1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal value_1 = {{123457, 1, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x200000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_9) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_10) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_11) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_degree(&value_2, 2);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_15) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_set_degree(&value_1, 4);
  s21_decimal value_2 = {{12u, 0, 0, 0}};
  s21_set_degree(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {{12345, 654, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{12, 654, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {{123456, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123, 6, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 3454334633}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal value_1 = {{123456, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456, 6, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_9) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_10) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_11) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_degree(&value_2, 2);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{12346, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{12345, 6, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_11) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_13) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_15) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_degree(&value_2, 2);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_16) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_1) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST
// Тесты на арифметические операции:

START_TEST(s21_add_1) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 3;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 3;
  // src2 = 2;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 3;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01001100110100101000000111001000;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000010011101100000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000101110100011001110100011111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000011111010011101111100100011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000001011001000011001011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 98745654321;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11111101101100110001110000110010;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01001100110100101000000111001000;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b10001001111010000000000000000000;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615;
  // src2 = 1;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000001;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_15) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;
  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00111111011101000111010111001010;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000001010;
  origin.bits[3] = 0b00000000000000010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_16) {
  s21_decimal src1, src2;
  int value_type_result, value_type_origin;
  // result = null
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;
  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, NULL);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_17) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;
  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_18) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = +0;
  // src2 = +0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_19) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = +0;
  // src2 = -0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_20) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -0;
  // src2 = -0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_21) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01100010111100011011000010101001;
  origin.bits[1] = 0b01101101111100110111111101100111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_22) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00110111111111010001010100111010;
  origin.bits[1] = 0b00000000000111110100000111110010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_23) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;
  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b10011010010111001101001011101010;
  origin.bits[1] = 0b10111110010100100100110100010011;
  origin.bits[2] = 0b00000000000010101001000111100111;
  origin.bits[3] = 0b00000000000110000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_24) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;
  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;
  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11010101111011100000000010001100;
  origin.bits[1] = 0b01111000000001011001100110101101;
  origin.bits[2] = 0b00011111101010011000001000100010;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_25) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;
  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01110000110111010100000010001101;
  origin.bits[1] = 0b01011010100111011110001100001010;
  origin.bits[2] = 0b00100111111010111100110001011010;
  origin.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_26) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;
  src1.bits[0] = 0b01001111101101000110000001100101;
  src1.bits[1] = 0b01000010001101101011011001100001;
  src1.bits[2] = 0b01111010101111011000110010011010;
  src1.bits[3] = 0b10000000000011000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01001111101101000110000001100101;
  origin.bits[1] = 0b01000010001101101011011001100001;
  origin.bits[2] = 0b01111010101111011000110010011010;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_float_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_27) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -79228162514264337593543950335;
  // src2 = 0;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_28) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 546378;
  // src2 = 0;
  src1.bits[0] = 0b00000000000010000101011001001010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000010000101011001001010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_29) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 8976545415646545.5746845454;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11011101111000010000101100001110;
  src2.bits[1] = 0b00000101010000010110101000000010;
  src2.bits[2] = 0b00000000010010100100000010010011;
  src2.bits[3] = 0b00000000000010100000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11011101111000010000101100001110;
  origin.bits[1] = 0b00000101010000010110101000000010;
  origin.bits[2] = 0b00000000010010100100000010010011;
  origin.bits[3] = 0b00000000000010100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_30) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_31) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_32) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000001000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_33) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_34) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000001000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_35) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000110110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_36) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000010011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000100110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_37) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000010011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_38) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000010011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000001000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_39) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000010011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000101110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_40) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000010011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000001000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_41) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_42) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000001100101100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000001100110001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_43) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b00000000000000000000000000000111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000101010111101101100011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000101010111101101101010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_44) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000001;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_45) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_add_46) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_add(src1, src2, &result);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_sub_111) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result), x = 0;
  s21_from_decimal_to_int(result, &x);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub__2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  for (int i = 0; i < 3; i++) ck_assert_int_eq(result.bits[i], 0xFFFFFFFF - 1);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{2147483638, 0, 0, 0}};
  s21_decimal result = {{2147483628, 0, 0, 0}};
  s21_set_sign(&result, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[0], 2147483628);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0] + result.bits[1] + result.bits[2], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{12345678, 0, 0, 0}};
  s21_decimal result = {0};
  s21_set_degree(&value_2, 7);
  int x = 2;
  float result_float = 0, z = x - 1.2345678;
  s21_from_int_to_decimal(x, &value_1);
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(fabs((result_float - z)) < 0, 0);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_set_degree(&value_1, 1);
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  s21_set_degree(&value_2, 2);
  s21_set_sign(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{156, 0, 0, 0}};
  s21_set_degree(&check, 2);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_set_degree(&value_1, 1);
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  s21_set_degree(&value_2, 2);
  s21_decimal result;
  s21_decimal check = {{416, 0, 0, 0}};
  s21_set_degree(&check, 2);
  s21_set_sign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, NINF);
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, NINF);
}
END_TEST

START_TEST(s21_sub_12) {
  s21_decimal value_1 = {{64071, 0, 0, 0}};
  s21_set_degree(&value_1, 4);
  s21_decimal value_2 = {{5919, 0, 0, 0}};
  s21_set_degree(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{5854929, 0, 0, 0}};
  s21_set_degree(&check, 4);
  s21_set_sign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_13) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 50);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_14) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -150);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_15) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(-50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -50);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_16) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(-50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 150);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_17) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(500, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -400);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_18) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(-500, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 400);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_19) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;

  dec2.bits[0] = 1236;
  dec2.bits[3] = 983040;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 607087404;
  true_ans.bits[1] = 123904785;
  true_ans.bits[3] = 983040;
  int res = s21_sub(dec1, dec2, &ans);
  ck_assert_int_eq(ans.bits[0], true_ans.bits[0]);
  ck_assert_int_eq(ans.bits[1], true_ans.bits[1]);
  ck_assert_int_eq(ans.bits[2], true_ans.bits[2]);
  ck_assert_int_eq(ans.bits[3], true_ans.bits[3]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_20) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 532167;
  true_ans.bits[3] = 196608;
  int res = s21_sub(dec1, dec2, &ans);
  ck_assert_int_eq(ans.bits[0], true_ans.bits[0]);
  ck_assert_int_eq(ans.bits[1], true_ans.bits[1]);
  ck_assert_int_eq(ans.bits[2], true_ans.bits[2]);
  ck_assert_int_eq(ans.bits[3], true_ans.bits[3]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int x = 2, y = 3;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_div(value_1, value_2, &result);
  float result_float = 0;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(fabs((result_float - 0.66666)) < 1e-4, 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, NAN12);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  int a = 1246, b = 2;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int rez = 0, origin_rez = a / b;
  value_type_result = s21_div(src1, src2, &result);
  value_type_origin = 0;
  s21_from_decimal_to_int(result, &rez);
  ck_assert_int_eq(rez, origin_rez);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  int a = 1246, b = 4;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int rez = 0, origin_rez = a / b;
  value_type_result = s21_div(src1, src2, &result);
  value_type_origin = 0;
  s21_from_decimal_to_int(result, &rez);
  ck_assert_int_eq(rez, origin_rez);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  float a = 5224, b = 20;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float rez = 0, origin_rez = a / b;
  value_type_result = s21_div(src1, src2, &result);
  value_type_origin = 0;
  s21_from_decimal_to_float(result, &rez);
  ck_assert_float_eq(rez, origin_rez);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  float a = 5224, b = 235;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float rez = 0, origin_rez = a / b;
  value_type_result = s21_div(src1, src2, &result);
  value_type_origin = 0;
  s21_from_decimal_to_float(result, &rez);
  ck_assert_float_eq(rez, origin_rez);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  float a = 65224, b = 23512;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float rez = 0, origin_rez = a / b;
  value_type_result = s21_div(src1, src2, &result);
  value_type_origin = 0;
  s21_from_decimal_to_float(result, &rez);
  ck_assert_float_eq(rez, origin_rez);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal src1, src2, result, origin;
  // 0
  // 0.015
  // 0
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal src1, src2, result;
  // 3
  // 2
  // result = NULL;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check_origin, check);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal src1, src2, result;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 3;
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_15) {
  s21_decimal src1, src2, result, origin;
  // 1
  // 3
  // 0.3(3)
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000101010101010101010101010101;
  origin.bits[1] = 0b00010100101101110000000011001011;
  origin.bits[2] = 0b00001010110001010100010011001010;
  origin.bits[3] = 0b00000000000111000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_16) {
  s21_decimal src1, src2, result = {0};
  float a = -115.2;
  float b = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 3;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(s21_div_17) {
  s21_decimal src1, src2, result = {{0}};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000111000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 1;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(s21_div_18) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_19) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_mul_test_1) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1, -1, -1, -2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_2) {
  s21_decimal a = {{-2017942635, 47083, 0, 65536}};  // 20222222222222.9
  s21_decimal b = {{0, 0, 0, 0}};                    // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};
  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_3) {
  s21_decimal a = {{292342, 0, 0, 327680}};  // 2.92342
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_4) {
  s21_decimal a = {{292342, 0, 0, -2147155968}};  // -2.92342
  s21_decimal b = {{781413, 0, 0, -2147483648}};  // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{806572558, 53, 0, 327680}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_5) {
  s21_decimal a = {{-1158315456, -197194979, 33, 0}};  // 626342352523521000000
  s21_decimal b = {{781413, 0, 0, -2147483648}};       // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1347460288, -177876063, 26532164, 2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_6) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};     // -79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 2);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_7) {
  s21_decimal a = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 1);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_8) {
  s21_decimal a = {{1015837740, 287445, 0, 0}};  // 1234567890236460
  s21_decimal b = {{-2045900063, 28744, 0, 0}};  // 123456789023457
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 1);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_9) {
  s21_decimal a = {{-1345409089, 146074521, 0, 0}};  // 627385293423423423
  s21_decimal b = {
      {1668895137, 1064696021, 0, -2147483648}};  // -4572834592045224353
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 2);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_10) {
  s21_decimal a = {{5, 0, 0, -2147483648}};  // -5
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{0, 0, 0, 0}};
  s21_set_sign(&check, 1);
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_11) {
  s21_decimal a = {{351661334, 63675, 0, 0}};  // 273482394234134
  s21_decimal b = {{7, 0, 0, 0}};              // 7
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1833337958, 445725, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_12) {
  s21_decimal a = {{61237812, 0, 0, -2147024896}};  // -6.1237812
  s21_decimal b = {{81230311, 0, 0, 196608}};       // 81230.311
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-183998228, 1158184, 0, -2146828288}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_13) {
  s21_decimal a = {{17403, 0, 0, 0}};              // 17403
  s21_decimal b = {{4789282, 0, 0, -2147352576}};  // -47892.82
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{1743496022, 19, 0, -2147352576}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_15) {
  s21_decimal a = {{610781734, 168435, 0, 983040}};  // 0.723423427283494
  s21_decimal b = {{784, 0, 0, 196608}};             // 0.784
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{2111509600, 132053151, 0, 1179648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_16) {
  s21_decimal a = {{7938402, 0, 0, 0}};               // 7938402
  s21_decimal b = {{1830490002, 0, 0, -2147155968}};  // -18304.90002
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1654667292, 3383300, 0, -2147155968}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_21) {
  s21_decimal a = {{0, 0, 0, 0}};  // 0
  s21_decimal b = {{0, 0, 0, 0}};  // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_23) {
  s21_decimal a = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal b = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{808348673, 232830643, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_24) {
  s21_decimal a = {{-1, -1, -78293423, 0}};  // 77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    0}};  // 11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 1);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_25) {
  s21_decimal a = {
      {-1, -1, -78293423, -2147483648}};  // -77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    -2147483648}};  // -11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 1);
  s21_decimal check = {{0, 0, 0, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_26) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1, -1, -1, 0}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_27) {
  s21_decimal a = {{8, 0, 0, 0}};        // 8
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{8, 0, 0, 1835008}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_28) {
  s21_decimal a = {{10, 0, 0, 0}};       // 10
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{10, 0, 0, 1835008}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_29) {
  s21_decimal a = {{8, 0, 0, 0}};            // 8
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{8, 0, 0, -2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_30) {
  s21_decimal a = {{10, 0, 0, 0}};           // 10
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{10, 0, 0, -2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_31) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1, -1, -1, -2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_32) {
  s21_decimal a = {{1, 0, 0, 0}};  // 1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1, -1, -1, -2147483648}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_33) {
  s21_decimal a = {{-1, -1, -1, 0}};   // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1717986919, -1717986919, -1717986919, 0}};
  ck_assert_float_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_34) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};            // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1717986919, -1717986919, -1717986919, 0}};
  ck_assert_float_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_35) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1717986919, -1717986919, -1717986919, -2147483648}};
  ck_assert_float_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_36) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};      // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1717986919, -1717986919, -1717986919, -2147483648}};
  ck_assert_float_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_test_37) {
  s21_decimal a = {{-1, -1, -1, 0}};    // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, 196608}};  // 0.001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq(res, 0);
  s21_decimal check = {{-1, -1, -1, 196608}};
  ck_assert_int_eq(res_bits.bits[0], check.bits[0]);
  ck_assert_int_eq(res_bits.bits[1], check.bits[1]);
  ck_assert_int_eq(res_bits.bits[2], check.bits[2]);
  ck_assert_int_eq(res_bits.bits[3], check.bits[3]);
  // ck_assert_int_eq(s21_is_equal(res_bits, check), 1);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 3;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 3;
  // src2 = 2;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 3;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 2;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00011100110011110011101011000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00010111010001100111010001101100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_8) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00010011100100010101101110010110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000001011001000011001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_10) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 1;
  // src2 = 98745654321;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11111101101100110001110000110001;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11100110011101111000010101001111;
  origin.bits[1] = 0b00000000000000000000000000000110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_12) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b10001001111001111111111111111111;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_13) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 18446744073709551615;
  // src2 = 1;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_14) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_15) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_16) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 0;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_17) {
  s21_decimal src1, src2;
  int value_type_result, value_type_origin;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;
  // result = null
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, NULL);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_18) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01011111001100010111011110111010;
  origin.bits[1] = 0b01000100111111001101101110110001;
  origin.bits[2] = 0b00000001101011100011011100011110;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_19) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11000100010110100111001000111001;
  origin.bits[1] = 0b01100100100011011110110011010011;
  origin.bits[2] = 0b00000000000001001101011111010011;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_20) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = -8798232189789785;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11000100010110100111001000111001;
  origin.bits[1] = 0b01100100100011011110110011010011;
  origin.bits[2] = 0b00000000000001001101011111010011;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_21) {
  s21_decimal src1, src2;
  s21_decimal *result = NULL;
  int value_type_result, value_type_origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, result);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_22) {
  s21_decimal src1, src2, result;
  int value_type_result, value_type_origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 1;
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_23) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_24) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_25) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_26) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  // 27
  src1.bits[0] = 0b00000000000000000000000000011011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // 19
  src2.bits[0] = 0b00000000000000000000000000010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  // 513
  origin.bits[0] = 0b00000000000000000000001000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_27) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  // 2668745618745983003
  src1.bits[0] = 0b00101001001111000000000000011011;
  src1.bits[1] = 0b00100101000010010100101000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // 275
  src2.bits[0] = 0b00000000000000000000000100010011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  // 733905045155145325825
  origin.bits[0] = 0b01001011011101000001110100000001;
  origin.bits[1] = 0b11001000111110100111111000101100;
  origin.bits[2] = 0b00000000000000000000000000100111;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_28) {
  // null * null
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  //
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_29) {
  // null * digit
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  //
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00000000000011000010001000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_30) {
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  // digit * null
  src1.bits[0] = 0b00000100100011000100101100000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000001001001001000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_31) {
  // neg null * null
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  //
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_32) {
  // null * neg_null`
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  //
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_33) {
  // переполнение плюс
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  // 13038434988312589819859583626
  src1.bits[0] = 0b00010100010100100100001010001010;
  src1.bits[1] = 0b00000001110010010010111111110100;
  src1.bits[2] = 0b00101010001000010010010000000001;
  src1.bits[3] = 0b00000000000000000000000000000000;
  // 4951760157794543045565218816
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00001001000100000000000000000000;
  src2.bits[2] = 0b00010000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 1;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_mul_34) {
  // отрицательное переполнение
  s21_decimal src1 = {0}, src2 = {0}, origin = {0}, result = {0};
  int value_type_result = 0, value_type_origin = 0;
  //
  src1.bits[0] = 0b00010010011010000001000100000000;
  src1.bits[1] = 0b00000010010001000010101100000000;
  src1.bits[2] = 0b00000100000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  //
  src2.bits[0] = 0b00001000010010001000100101001100;
  src2.bits[1] = 0b00000100000100100010000001111011;
  src2.bits[2] = 0b00010001000000000000000000010000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 2;
  //
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_1, result), 1);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result;
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal check = {{1, 1, 1, 0x80000000}};
  s21_decimal result;
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_negate_5) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src;
  s21_from_float_to_decimal(a, &src);
  s21_decimal res;
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value_2 = {{0, 0, 0, 0x80020000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_2 = {{1111000, 0, 0, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_set_degree(&value_2, 7);
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  s21_set_degree(&value_1, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  s21_set_degree(&value_1, 3);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_5) {
  s21_decimal src1;
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_6) {
  s21_decimal src1;
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal value_2 = {{17111000, 0, 0, 0}};
  s21_decimal result = {0};
  s21_set_degree(&value_2, 7);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_2 = {{22, 0, 0, 0}};
  s21_decimal result = {0};
  s21_set_degree(&value_2, 1);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal value_2 = {{15, 0, 0, pow(2, 16)}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal value_2 = {{15, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_degree(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_degree(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_degree(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_degree(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_11) {
  s21_decimal src1;
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_12) {
  s21_decimal src1;
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  s21_decimal result;
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_degree(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_degree(&value_1, 5);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od;
  s21_floor(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_1) {
//   float num = 10.1000004;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b00000110000001010010001101000100);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b00000000000001110000000000000000);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_2) {
//   float num = 8934.2783203;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b11001101001111101010111011100011);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000010100);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b00000000000001110000000000000000);
// }

// END_TEST

// START_TEST(s21_from_float_to_decimal_3) {
//   float num = -23423.8203125123;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b10001001101011110101010011110101);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000110110);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b10000000000001110000000000000000);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  float num = -27348;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_bits.bits[0], 0b00000000000000000110101011010100);
  ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  float num = 823923;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 823923);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_6) {
//   float num = -129312304;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq((int)res, 0);
//   ck_assert_int_eq((int)res_bits.bits[0], 129312304);
//   ck_assert_int_eq((int)res_bits.bits[1], 0);
//   ck_assert_int_eq((int)res_bits.bits[2], 0);
//   ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_7) {
//   float num = 23744.7792968750;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b01001000111111011100100101001001);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000110111);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b00000000000001110000000000000000);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_8) {
//   float num = -2393.8230212;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b10010010110101000110011011011101);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000101);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b10000000000001110000000000000000);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  float num = 912479.2;

  int res = s21_from_float_to_decimal(num, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  float num = -123234.000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_bits.bits[0], 0b00000000000000011110000101100010);
  ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_11) {
  float num = 1e-29;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_12) {
  float num = -23748280;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 23748280);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_13) {
  float num = 802000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 802000);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_14) {
//   float num = 1.333112552412212431124;
//   s21_decimal res_bits = {{0, 0, 0, 0}};

//   int res = s21_from_float_to_decimal(num, &res_bits);

//   ck_assert_int_eq(res, 0);
//   ck_assert_int_eq(res_bits.bits[0], 0b00000000110010110110101010110110);
//   ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
//   ck_assert_int_eq(res_bits.bits[3], 0b00000000000001110000000000000000);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_15) {
  float num = 0.5632482;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 5632482);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 458752);
}
END_TEST

START_TEST(s21_from_float_to_decimal_16) {
  float num = 0.5632482;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 5632482);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 458752);
}
END_TEST

START_TEST(s21_from_float_to_decimal_17) {
  float num = -0.6527385;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 6527385);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147024896);
}
END_TEST

START_TEST(s21_from_float_to_decimal_18) {
  float num = -12397620;
  s21_decimal res_bits = {{0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_bits.bits[0], 0b00000000101111010010110000110100);
  ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_19) {
  float num = 12397620;
  s21_decimal res_bits = {{0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_bits.bits[0], 0b00000000101111010010110000110100);
  ck_assert_int_eq(res_bits.bits[1], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[2], 0b00000000000000000000000000000000);
  ck_assert_int_eq(res_bits.bits[3], 0b00000000000000000000000000000000);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_20) {
//   s21_decimal dst = {0}, origin = {0};
//   float src = 36401984.2348234;
//   int dst_output = 0;
//   int result_output = 0;

//   origin.bits[0] = 0b00000010001010110111001101000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   result_output = s21_from_float_to_decimal(src, &dst);
//   ck_assert_int_eq(origin.bits[0], dst.bits[0]);
//   ck_assert_int_eq(origin.bits[1], dst.bits[1]);
//   ck_assert_int_eq(origin.bits[2], dst.bits[2]);
//   ck_assert_int_eq(origin.bits[3], dst.bits[3]);
//   ck_assert_int_eq(dst_output, result_output);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_21) {
  // NULL тест
  s21_decimal dst = {0}, origin = {0};
  float src = 1234.5;
  int dst_output = 0;
  int result_output = 0;
  origin.bits[0] = 0b00000000000000000011000000111001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000010000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_22) {
//   s21_decimal dst = {0}, origin = {0};
//   float src = 36401984.2348234;
//   int dst_output = 0;
//   int result_output = 0;

//   origin.bits[0] = 0b00000010001010110111001101000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   result_output = s21_from_float_to_decimal(src, &dst);
//   ck_assert_int_eq(origin.bits[0], dst.bits[0]);
//   ck_assert_int_eq(origin.bits[1], dst.bits[1]);
//   ck_assert_int_eq(origin.bits[2], dst.bits[2]);
//   ck_assert_int_eq(origin.bits[3], dst.bits[3]);
//   ck_assert_int_eq(dst_output, result_output);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_23) {
  s21_decimal dst = {0}, origin = {0};
  float src = 999999995;
  // 9999999|95.0
  // 10000000|00.0
  int dst_output = 0;
  int result_output = 0;
  origin.bits[0] = 0b00111011100110101100101000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

START_TEST(s21_from_float_to_decimal_24) {
  s21_decimal dst = {0}, origin = {0};
  float src = 0.00000000000000000000000000001f;
  int dst_output = 1;
  int result_output = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

START_TEST(s21_from_float_to_decimal_25) {
  s21_decimal dst = {0}, origin = {0};
  float src = 192836;
  // 192835.9|6
  // 192836.0|0
  int dst_output = 0;
  int result_output = 0;
  origin.bits[0] = 0b00000000000000101111000101000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

START_TEST(s21_from_float_to_decimal_26) {
  s21_decimal dst = {0}, origin = {0};
  float src = -192836;
  // 3552346|23461234.12353236
  // 3552346|00000000.0
  int dst_output = 0;
  int result_output = 0;
  origin.bits[0] = 0b00000000000000101111000101000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

START_TEST(s21_from_float_to_decimal_27) {
  s21_decimal dst = {0}, origin = {0};
  float src = 999999995;
  // 9999999|95.0
  // 10000000|00.0
  int dst_output = 0;
  int result_output = 0;
  origin.bits[0] = 0b00111011100110101100101000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

START_TEST(s21_from_float_to_decimal_28) {
  s21_decimal dst = {0}, origin = {0};
  float src = 0.00000000000000000000000000001f;
  int dst_output = 1;
  int result_output = 0;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  result_output = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(origin.bits[0], dst.bits[0]);
  ck_assert_int_eq(origin.bits[1], dst.bits[1]);
  ck_assert_int_eq(origin.bits[2], dst.bits[2]);
  ck_assert_int_eq(origin.bits[3], dst.bits[3]);
  ck_assert_int_eq(dst_output, result_output);
}
END_TEST

// s21_from_int_to_decimal

START_TEST(s21_from_int_to_decimal_1) {
  int src = -2147483647;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = 101;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  int src = -31325;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_5) {
  int src = 49135648;
  s21_decimal check = {{49135648, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_6) {
  int src = -49135648;
  s21_decimal check = {{49135648, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_7) {
  int src = -49135648;
  s21_decimal check = {{49135648, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST
// s21_from_decimal_to_int_1

START_TEST(s21_from_decimal_to_int_1) {
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 1, 0}};
  return_value = s21_from_decimal_to_int(value_1, &temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  int src = 0;
  int temp = 100;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  int src = 0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0x80000000, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  int src = 133;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0x85, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal value = {{49135648, 0, 0, 0}};
  s21_set_sign(&value, 1);
  s21_set_degree(&value, 1);
  int array;
  int check = -4913564;
  int return_value = s21_from_decimal_to_int(value, &array);
  ck_assert_int_eq(array, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal value = {{49135648, 0, 0, 0}};
  s21_set_degree(&value, 1);
  int array;
  int check = 4913564;
  int return_value = s21_from_decimal_to_int(value, &array);
  ck_assert_int_eq(array, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_7) {
  s21_decimal value = {{2, 3, 0, 0}};
  int array;
  int check = 1;
  int return_value = s21_from_decimal_to_int(value, &array);
  ck_assert_int_eq(array, check);
  ck_assert_int_eq(return_value, CONVERTING_ERROR);
}
END_TEST

// s21_from_decimal_to_float

START_TEST(s21_from_decimal_to_float_1) {
  float src = 0.00000000000;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs(src - temp) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float src = 0.01;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000000100000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float src = 0.00000123;
  float temp = 0;
  s21_decimal value_1 = {{123, 0, 0, 0b00000000000010000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  float src = -0.01;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0x80020000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal value = {{1812, 0, 0, 0}};
  s21_set_sign(&value, 1);
  float result;
  float check = -1812;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal value = {{18122, 0, 0, 0}};
  s21_set_degree(&value, 3);
  s21_set_sign(&value, 1);
  float result;
  float check = -18.122;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result;
  float check = 16777215;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float result;
  float check = 0xFFFFFFFFFFFFFFFF;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_float_9) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  // tcase_set_timeout(tc_core, 10);
  TCase *tc_is_greater_1;
  tc_is_greater_1 = tcase_create("s21_is_greater_1");
  suite_add_tcase(s, tc_is_greater_1);
  tcase_add_test(tc_is_greater_1, s21_is_greater_1);

  TCase *tc_is_greater_2;
  tc_is_greater_2 = tcase_create("s21_is_greater_2");
  suite_add_tcase(s, tc_is_greater_2);
  tcase_add_test(tc_is_greater_2, s21_is_greater_2);

  TCase *tc_is_greater_3;
  tc_is_greater_3 = tcase_create("s21_is_greater_3");
  suite_add_tcase(s, tc_is_greater_3);
  tcase_add_test(tc_is_greater_3, s21_is_greater_3);

  TCase *tc_is_greater_4;
  tc_is_greater_4 = tcase_create("s21_is_greater_4");
  suite_add_tcase(s, tc_is_greater_4);
  tcase_add_test(tc_is_greater_4, s21_is_greater_4);

  TCase *tc_is_greater_5;
  tc_is_greater_5 = tcase_create("s21_is_greater_5");
  suite_add_tcase(s, tc_is_greater_5);
  tcase_add_test(tc_is_greater_5, s21_is_greater_5);

  TCase *tc_is_greater_6;
  tc_is_greater_6 = tcase_create("s21_is_greater_6");
  suite_add_tcase(s, tc_is_greater_6);
  tcase_add_test(tc_is_greater_6, s21_is_greater_6);

  TCase *tc_is_greater_7;
  tc_is_greater_7 = tcase_create("s21_is_greater_7");
  suite_add_tcase(s, tc_is_greater_7);
  tcase_add_test(tc_is_greater_7, s21_is_greater_7);

  TCase *tc_is_greater_8;
  tc_is_greater_8 = tcase_create("s21_is_greater_8");
  suite_add_tcase(s, tc_is_greater_8);
  tcase_add_test(tc_is_greater_8, s21_is_greater_8);

  TCase *tc_is_greater_9;
  tc_is_greater_9 = tcase_create("s21_is_greater_9");
  suite_add_tcase(s, tc_is_greater_9);
  tcase_add_test(tc_is_greater_9, s21_is_greater_9);

  TCase *tc_is_greater_10;
  tc_is_greater_10 = tcase_create("s21_is_greater_10");
  suite_add_tcase(s, tc_is_greater_10);
  tcase_add_test(tc_is_greater_10, s21_is_greater_10);

  TCase *tc_is_greater_11;
  tc_is_greater_11 = tcase_create("s21_is_greater_11");
  suite_add_tcase(s, tc_is_greater_11);
  tcase_add_test(tc_is_greater_11, s21_is_greater_11);

  TCase *tc_is_greater_12;
  tc_is_greater_12 = tcase_create("s21_is_greater_12");
  suite_add_tcase(s, tc_is_greater_12);
  tcase_add_test(tc_is_greater_12, s21_is_greater_12);

  TCase *tc_is_greater_13;
  tc_is_greater_13 = tcase_create("s21_is_greater_13");
  suite_add_tcase(s, tc_is_greater_13);
  tcase_add_test(tc_is_greater_13, s21_is_greater_13);

  TCase *tc_is_greater_14;
  tc_is_greater_14 = tcase_create("s21_is_greater_14");
  suite_add_tcase(s, tc_is_greater_14);
  tcase_add_test(tc_is_greater_14, s21_is_greater_14);

  TCase *tc_is_greater_15;
  tc_is_greater_15 = tcase_create("s21_is_greater_15");
  suite_add_tcase(s, tc_is_greater_15);
  tcase_add_test(tc_is_greater_15, s21_is_greater_15);

  TCase *tc_is_greater_16;
  tc_is_greater_16 = tcase_create("s21_is_greater_16");
  suite_add_tcase(s, tc_is_greater_16);
  tcase_add_test(tc_is_greater_16, s21_is_greater_16);

  TCase *tc_is_equal_1;
  tc_is_equal_1 = tcase_create("s21_is_equal_1");
  suite_add_tcase(s, tc_is_equal_1);
  tcase_add_test(tc_is_equal_1, s21_is_equal_1);

  TCase *tc_is_equal_2;
  tc_is_equal_2 = tcase_create("s21_is_equal_2");
  suite_add_tcase(s, tc_is_equal_2);
  tcase_add_test(tc_is_equal_2, s21_is_equal_2);

  TCase *tc_is_equal_3;
  tc_is_equal_3 = tcase_create("s21_is_equal_3");
  suite_add_tcase(s, tc_is_equal_3);
  tcase_add_test(tc_is_equal_3, s21_is_equal_3);

  TCase *tc_is_equal_4;
  tc_is_equal_4 = tcase_create("s21_is_equal_4");
  suite_add_tcase(s, tc_is_equal_4);
  tcase_add_test(tc_is_equal_4, s21_is_equal_4);

  TCase *tc_is_equal_5;
  tc_is_equal_5 = tcase_create("s21_is_equal_5");
  suite_add_tcase(s, tc_is_equal_5);
  tcase_add_test(tc_is_equal_5, s21_is_equal_5);

  TCase *tc_is_equal_6;
  tc_is_equal_6 = tcase_create("s21_is_equal_6");
  suite_add_tcase(s, tc_is_equal_6);
  tcase_add_test(tc_is_equal_6, s21_is_equal_6);

  TCase *tc_is_equal_7;
  tc_is_equal_7 = tcase_create("s21_is_equal_7");
  suite_add_tcase(s, tc_is_equal_7);
  tcase_add_test(tc_is_equal_7, s21_is_equal_7);

  TCase *tc_is_equal_8;
  tc_is_equal_8 = tcase_create("s21_is_equal_8");
  suite_add_tcase(s, tc_is_equal_8);
  tcase_add_test(tc_is_equal_8, s21_is_equal_8);

  TCase *tc_is_equal_9;
  tc_is_equal_9 = tcase_create("s21_is_equal_9");
  suite_add_tcase(s, tc_is_equal_9);
  tcase_add_test(tc_is_equal_9, s21_is_equal_9);

  TCase *tc_is_greater_or_equal_1;
  tc_is_greater_or_equal_1 = tcase_create("s21_is_greater_or_equal_1");
  suite_add_tcase(s, tc_is_greater_or_equal_1);
  tcase_add_test(tc_is_greater_or_equal_1, s21_is_greater_or_equal_1);

  TCase *tc_is_greater_or_equal_2;
  tc_is_greater_or_equal_2 = tcase_create("s21_is_greater_or_equal_2");
  suite_add_tcase(s, tc_is_greater_or_equal_2);
  tcase_add_test(tc_is_greater_or_equal_2, s21_is_greater_or_equal_2);

  TCase *tc_is_greater_or_equal_3;
  tc_is_greater_or_equal_3 = tcase_create("s21_is_greater_or_equal_3");
  suite_add_tcase(s, tc_is_greater_or_equal_3);
  tcase_add_test(tc_is_greater_or_equal_3, s21_is_greater_or_equal_3);

  TCase *tc_is_greater_or_equal_4;
  tc_is_greater_or_equal_4 = tcase_create("s21_is_greater_or_equal_4");
  suite_add_tcase(s, tc_is_greater_or_equal_4);
  tcase_add_test(tc_is_greater_or_equal_4, s21_is_greater_or_equal_4);

  TCase *tc_is_greater_or_equal_5;
  tc_is_greater_or_equal_5 = tcase_create("s21_is_greater_or_equal_5");
  suite_add_tcase(s, tc_is_greater_or_equal_5);
  tcase_add_test(tc_is_greater_or_equal_5, s21_is_greater_or_equal_5);

  TCase *tc_is_greater_or_equal_6;
  tc_is_greater_or_equal_6 = tcase_create("s21_is_greater_or_equal_6");
  suite_add_tcase(s, tc_is_greater_or_equal_6);
  tcase_add_test(tc_is_greater_or_equal_6, s21_is_greater_or_equal_6);

  TCase *tc_is_greater_or_equal_7;
  tc_is_greater_or_equal_7 = tcase_create("s21_is_greater_or_equal_7");
  suite_add_tcase(s, tc_is_greater_or_equal_7);
  tcase_add_test(tc_is_greater_or_equal_7, s21_is_greater_or_equal_7);

  TCase *tc_is_greater_or_equal_8;
  tc_is_greater_or_equal_8 = tcase_create("s21_is_greater_or_equal_8");
  suite_add_tcase(s, tc_is_greater_or_equal_8);
  tcase_add_test(tc_is_greater_or_equal_8, s21_is_greater_or_equal_8);

  TCase *tc_is_greater_or_equal_9;
  tc_is_greater_or_equal_9 = tcase_create("s21_is_greater_or_equal_9");
  suite_add_tcase(s, tc_is_greater_or_equal_9);
  tcase_add_test(tc_is_greater_or_equal_9, s21_is_greater_or_equal_9);

  TCase *tc_is_greater_or_equal_10;
  tc_is_greater_or_equal_10 = tcase_create("s21_is_greater_or_equal_10");
  suite_add_tcase(s, tc_is_greater_or_equal_10);
  tcase_add_test(tc_is_greater_or_equal_10, s21_is_greater_or_equal_10);

  TCase *tc_is_greater_or_equal_11;
  tc_is_greater_or_equal_11 = tcase_create("s21_is_greater_or_equal_11");
  suite_add_tcase(s, tc_is_greater_or_equal_11);
  tcase_add_test(tc_is_greater_or_equal_11, s21_is_greater_or_equal_11);

  TCase *tc_is_greater_or_equal_12;
  tc_is_greater_or_equal_12 = tcase_create("s21_is_greater_or_equal_12");
  suite_add_tcase(s, tc_is_greater_or_equal_12);
  tcase_add_test(tc_is_greater_or_equal_12, s21_is_greater_or_equal_12);

  TCase *tc_is_greater_or_equal_13;
  tc_is_greater_or_equal_13 = tcase_create("s21_is_greater_or_equal_13");
  suite_add_tcase(s, tc_is_greater_or_equal_13);
  tcase_add_test(tc_is_greater_or_equal_13, s21_is_greater_or_equal_13);

  TCase *tc_is_greater_or_equal_14;
  tc_is_greater_or_equal_14 = tcase_create("s21_is_greater_or_equal_14");
  suite_add_tcase(s, tc_is_greater_or_equal_14);
  tcase_add_test(tc_is_greater_or_equal_14, s21_is_greater_or_equal_14);

  TCase *tc_is_greater_or_equal_15;
  tc_is_greater_or_equal_15 = tcase_create("s21_is_greater_or_equal_15");
  suite_add_tcase(s, tc_is_greater_or_equal_15);
  tcase_add_test(tc_is_greater_or_equal_15, s21_is_greater_or_equal_15);

  TCase *tc_is_less_1;
  tc_is_less_1 = tcase_create("s21_is_less_1");
  suite_add_tcase(s, tc_is_less_1);
  tcase_add_test(tc_is_less_1, s21_is_less_1);

  TCase *tc_is_less_2;
  tc_is_less_2 = tcase_create("s21_is_less_2");
  suite_add_tcase(s, tc_is_less_2);
  tcase_add_test(tc_is_less_2, s21_is_less_2);

  TCase *tc_is_less_3;
  tc_is_less_3 = tcase_create("s21_is_less_3");
  suite_add_tcase(s, tc_is_less_3);
  tcase_add_test(tc_is_less_3, s21_is_less_3);

  TCase *tc_is_less_4;
  tc_is_less_4 = tcase_create("s21_is_less_4");
  suite_add_tcase(s, tc_is_less_4);
  tcase_add_test(tc_is_less_4, s21_is_less_4);

  TCase *tc_is_less_5;
  tc_is_less_5 = tcase_create("s21_is_less_5");
  suite_add_tcase(s, tc_is_less_5);
  tcase_add_test(tc_is_less_5, s21_is_less_5);

  TCase *tc_is_less_6;
  tc_is_less_6 = tcase_create("s21_is_less_6");
  suite_add_tcase(s, tc_is_less_6);
  tcase_add_test(tc_is_less_6, s21_is_less_6);

  TCase *tc_is_less_7;
  tc_is_less_7 = tcase_create("s21_is_less_7");
  suite_add_tcase(s, tc_is_less_7);
  tcase_add_test(tc_is_less_7, s21_is_less_7);

  TCase *tc_is_less_8;
  tc_is_less_8 = tcase_create("s21_is_less_8");
  suite_add_tcase(s, tc_is_less_8);
  tcase_add_test(tc_is_less_8, s21_is_less_8);

  TCase *tc_is_less_9;
  tc_is_less_9 = tcase_create("s21_is_less_9");
  suite_add_tcase(s, tc_is_less_9);
  tcase_add_test(tc_is_less_9, s21_is_less_9);

  TCase *tc_is_less_10;
  tc_is_less_10 = tcase_create("s21_is_less_10");
  suite_add_tcase(s, tc_is_less_10);
  tcase_add_test(tc_is_less_10, s21_is_less_10);

  TCase *tc_is_less_11;
  tc_is_less_11 = tcase_create("s21_is_less_11");
  suite_add_tcase(s, tc_is_less_11);
  tcase_add_test(tc_is_less_11, s21_is_less_11);

  TCase *tc_is_less_12;
  tc_is_less_12 = tcase_create("s21_is_less_12");
  suite_add_tcase(s, tc_is_less_12);
  tcase_add_test(tc_is_less_12, s21_is_less_12);

  TCase *tc_is_less_13;
  tc_is_less_13 = tcase_create("s21_is_less_13");
  suite_add_tcase(s, tc_is_less_13);
  tcase_add_test(tc_is_less_13, s21_is_less_13);

  TCase *tc_is_less_or_equal_1;
  tc_is_less_or_equal_1 = tcase_create("s21_is_less_or_equal_1");
  suite_add_tcase(s, tc_is_less_or_equal_1);
  tcase_add_test(tc_is_less_or_equal_1, s21_is_less_or_equal_1);

  TCase *tc_is_less_or_equal_2;
  tc_is_less_or_equal_2 = tcase_create("s21_is_less_or_equal_2");
  suite_add_tcase(s, tc_is_less_or_equal_2);
  tcase_add_test(tc_is_less_or_equal_2, s21_is_less_or_equal_2);

  TCase *tc_is_less_or_equal_3;
  tc_is_less_or_equal_3 = tcase_create("s21_is_less_or_equal_3");
  suite_add_tcase(s, tc_is_less_or_equal_3);
  tcase_add_test(tc_is_less_or_equal_3, s21_is_less_or_equal_3);

  TCase *tc_is_less_or_equal_4;
  tc_is_less_or_equal_4 = tcase_create("s21_is_less_or_equal_4");
  suite_add_tcase(s, tc_is_less_or_equal_4);
  tcase_add_test(tc_is_less_or_equal_4, s21_is_less_or_equal_4);

  TCase *tc_is_less_or_equal_5;
  tc_is_less_or_equal_5 = tcase_create("s21_is_less_or_equal_5");
  suite_add_tcase(s, tc_is_less_or_equal_5);
  tcase_add_test(tc_is_less_or_equal_5, s21_is_less_or_equal_5);

  TCase *tc_is_less_or_equal_6;
  tc_is_less_or_equal_6 = tcase_create("s21_is_less_or_equal_6");
  suite_add_tcase(s, tc_is_less_or_equal_6);
  tcase_add_test(tc_is_less_or_equal_6, s21_is_less_or_equal_6);

  TCase *tc_is_less_or_equal_7;
  tc_is_less_or_equal_7 = tcase_create("s21_is_less_or_equal_7");
  suite_add_tcase(s, tc_is_less_or_equal_7);
  tcase_add_test(tc_is_less_or_equal_7, s21_is_less_or_equal_7);

  TCase *tc_is_less_or_equal_8;
  tc_is_less_or_equal_8 = tcase_create("s21_is_less_or_equal_8");
  suite_add_tcase(s, tc_is_less_or_equal_8);
  tcase_add_test(tc_is_less_or_equal_8, s21_is_less_or_equal_8);

  TCase *tc_is_less_or_equal_9;
  tc_is_less_or_equal_9 = tcase_create("s21_is_less_or_equal_9");
  suite_add_tcase(s, tc_is_less_or_equal_9);
  tcase_add_test(tc_is_less_or_equal_9, s21_is_less_or_equal_9);

  TCase *tc_is_less_or_equal_10;
  tc_is_less_or_equal_10 = tcase_create("s21_is_less_or_equal_10");
  suite_add_tcase(s, tc_is_less_or_equal_10);
  tcase_add_test(tc_is_less_or_equal_10, s21_is_less_or_equal_10);

  TCase *tc_is_less_or_equal_11;
  tc_is_less_or_equal_11 = tcase_create("s21_is_less_or_equal_11");
  suite_add_tcase(s, tc_is_less_or_equal_11);
  tcase_add_test(tc_is_less_or_equal_11, s21_is_less_or_equal_11);

  TCase *tc_is_less_or_equal_12;
  tc_is_less_or_equal_12 = tcase_create("s21_is_less_or_equal_12");
  suite_add_tcase(s, tc_is_less_or_equal_12);
  tcase_add_test(tc_is_less_or_equal_12, s21_is_less_or_equal_12);

  TCase *tc_is_less_or_equal_13;
  tc_is_less_or_equal_13 = tcase_create("s21_is_less_or_equal_13");
  suite_add_tcase(s, tc_is_less_or_equal_13);
  tcase_add_test(tc_is_less_or_equal_13, s21_is_less_or_equal_13);

  TCase *tc_is_less_or_equal_14;
  tc_is_less_or_equal_14 = tcase_create("s21_is_less_or_equal_14");
  suite_add_tcase(s, tc_is_less_or_equal_14);
  tcase_add_test(tc_is_less_or_equal_14, s21_is_less_or_equal_14);

  TCase *tc_is_less_or_equal_15;
  tc_is_less_or_equal_15 = tcase_create("s21_is_less_or_equal_15");
  suite_add_tcase(s, tc_is_less_or_equal_15);
  tcase_add_test(tc_is_less_or_equal_15, s21_is_less_or_equal_15);

  TCase *tc_is_less_or_equal_16;
  tc_is_less_or_equal_16 = tcase_create("s21_is_less_or_equal_16");
  suite_add_tcase(s, tc_is_less_or_equal_16);
  tcase_add_test(tc_is_less_or_equal_16, s21_is_less_or_equal_16);

  TCase *tc_is_not_equal_1;
  tc_is_not_equal_1 = tcase_create("s21_is_not_equal_1");
  suite_add_tcase(s, tc_is_not_equal_1);
  tcase_add_test(tc_is_not_equal_1, s21_is_not_equal_1);

  TCase *tc_is_not_equal_2;
  tc_is_not_equal_2 = tcase_create("s21_is_not_equal_2");
  suite_add_tcase(s, tc_is_not_equal_2);
  tcase_add_test(tc_is_not_equal_2, s21_is_not_equal_2);

  TCase *tc_is_not_equal_3;
  tc_is_not_equal_3 = tcase_create("s21_is_not_equal_3");
  suite_add_tcase(s, tc_is_not_equal_3);
  tcase_add_test(tc_is_not_equal_3, s21_is_not_equal_3);

  TCase *tc_is_not_equal_4;
  tc_is_not_equal_4 = tcase_create("s21_is_not_equal_4");
  suite_add_tcase(s, tc_is_not_equal_4);
  tcase_add_test(tc_is_not_equal_4, s21_is_not_equal_4);

  TCase *tc_is_not_equal_5;
  tc_is_not_equal_5 = tcase_create("s21_is_not_equal_5");
  suite_add_tcase(s, tc_is_not_equal_5);
  tcase_add_test(tc_is_not_equal_5, s21_is_not_equal_5);

  TCase *tc_is_not_equal_6;
  tc_is_not_equal_6 = tcase_create("s21_is_not_equal_6");
  suite_add_tcase(s, tc_is_not_equal_6);
  tcase_add_test(tc_is_not_equal_6, s21_is_not_equal_6);

  TCase *tc_is_not_equal_7;
  tc_is_not_equal_7 = tcase_create("s21_is_not_equal_7");
  suite_add_tcase(s, tc_is_not_equal_7);
  tcase_add_test(tc_is_not_equal_7, s21_is_not_equal_7);

  TCase *tc_is_not_equal_8;
  tc_is_not_equal_8 = tcase_create("s21_is_not_equal_8");
  suite_add_tcase(s, tc_is_not_equal_8);
  tcase_add_test(tc_is_not_equal_8, s21_is_not_equal_8);

  TCase *tc_add_1;
  tc_add_1 = tcase_create("s21_add_1");
  suite_add_tcase(s, tc_add_1);
  tcase_add_test(tc_add_1, s21_add_1);

  TCase *tc_add_2;
  tc_add_2 = tcase_create("s21_add_2");
  suite_add_tcase(s, tc_add_2);
  tcase_add_test(tc_add_2, s21_add_2);

  TCase *tc_add_3;
  tc_add_3 = tcase_create("s21_add_3");
  suite_add_tcase(s, tc_add_3);
  tcase_add_test(tc_add_3, s21_add_3);

  TCase *tc_add_4;
  tc_add_4 = tcase_create("s21_add_4");
  suite_add_tcase(s, tc_add_4);
  tcase_add_test(tc_add_4, s21_add_4);

  TCase *tc_add_5;
  tc_add_5 = tcase_create("s21_add_5");
  suite_add_tcase(s, tc_add_5);
  tcase_add_test(tc_add_5, s21_add_5);

  TCase *tc_add_6;
  tc_add_6 = tcase_create("s21_add_6");
  suite_add_tcase(s, tc_add_6);
  tcase_add_test(tc_add_6, s21_add_6);

  TCase *tc_add_7;
  tc_add_7 = tcase_create("s21_add_7");
  suite_add_tcase(s, tc_add_7);
  tcase_add_test(tc_add_7, s21_add_7);

  TCase *tc_add_8;
  tc_add_8 = tcase_create("s21_add_8");
  suite_add_tcase(s, tc_add_8);
  tcase_add_test(tc_add_8, s21_add_8);

  TCase *tc_add_9;
  tc_add_9 = tcase_create("s21_add_9");
  suite_add_tcase(s, tc_add_9);
  tcase_add_test(tc_add_9, s21_add_9);

  TCase *tc_add_10;
  tc_add_10 = tcase_create("s21_add_10");
  suite_add_tcase(s, tc_add_10);
  tcase_add_test(tc_add_10, s21_add_10);

  TCase *tc_add_11;
  tc_add_11 = tcase_create("s21_add_11");
  suite_add_tcase(s, tc_add_11);
  tcase_add_test(tc_add_11, s21_add_11);

  TCase *tc_add_12;
  tc_add_12 = tcase_create("s21_add_12");
  suite_add_tcase(s, tc_add_12);
  tcase_add_test(tc_add_12, s21_add_12);

  TCase *tc_add_13;
  tc_add_13 = tcase_create("s21_add_13");
  suite_add_tcase(s, tc_add_13);
  tcase_add_test(tc_add_13, s21_add_13);

  TCase *tc_add_14;
  tc_add_14 = tcase_create("s21_add_14");
  suite_add_tcase(s, tc_add_14);
  tcase_add_test(tc_add_14, s21_add_14);

  TCase *tc_add_15;
  tc_add_15 = tcase_create("s21_add_15");
  suite_add_tcase(s, tc_add_15);
  tcase_add_test(tc_add_15, s21_add_15);

  TCase *tc_add_16;
  tc_add_16 = tcase_create("s21_add_16");
  suite_add_tcase(s, tc_add_16);
  tcase_add_test(tc_add_16, s21_add_16);

  TCase *tc_add_17;
  tc_add_17 = tcase_create("s21_add_17");
  suite_add_tcase(s, tc_add_17);
  tcase_add_test(tc_add_17, s21_add_17);

  TCase *tc_add_18;
  tc_add_18 = tcase_create("s21_add_18");
  suite_add_tcase(s, tc_add_18);
  tcase_add_test(tc_add_18, s21_add_18);

  TCase *tc_add_19;
  tc_add_19 = tcase_create("s21_add_19");
  suite_add_tcase(s, tc_add_19);
  tcase_add_test(tc_add_19, s21_add_19);

  TCase *tc_add_20;
  tc_add_20 = tcase_create("s21_add_20");
  suite_add_tcase(s, tc_add_20);
  tcase_add_test(tc_add_20, s21_add_20);

  TCase *tc_add_21;
  tc_add_21 = tcase_create("s21_add_21");
  suite_add_tcase(s, tc_add_21);
  tcase_add_test(tc_add_21, s21_add_21);

  TCase *tc_add_22;
  tc_add_22 = tcase_create("s21_add_22");
  suite_add_tcase(s, tc_add_22);
  tcase_add_test(tc_add_22, s21_add_22);

  TCase *tc_add_23;
  tc_add_23 = tcase_create("s21_add_23");
  suite_add_tcase(s, tc_add_23);
  tcase_add_test(tc_add_23, s21_add_23);

  TCase *tc_add_24;
  tc_add_24 = tcase_create("s21_add_24");
  suite_add_tcase(s, tc_add_24);
  tcase_add_test(tc_add_24, s21_add_24);

  TCase *tc_add_25;
  tc_add_25 = tcase_create("s21_add_25");
  suite_add_tcase(s, tc_add_25);
  tcase_add_test(tc_add_25, s21_add_25);

  TCase *tc_add_26;
  tc_add_26 = tcase_create("s21_add_26");
  suite_add_tcase(s, tc_add_26);
  tcase_add_test(tc_add_26, s21_add_26);

  TCase *tc_add_27;
  tc_add_27 = tcase_create("s21_add_27");
  suite_add_tcase(s, tc_add_27);
  tcase_add_test(tc_add_27, s21_add_27);

  TCase *tc_add_28;
  tc_add_28 = tcase_create("s21_add_28");
  suite_add_tcase(s, tc_add_28);
  tcase_add_test(tc_add_28, s21_add_28);

  TCase *tc_add_29;
  tc_add_29 = tcase_create("s21_add_29");
  suite_add_tcase(s, tc_add_29);
  tcase_add_test(tc_add_29, s21_add_29);

  TCase *tc_add_30;
  tc_add_30 = tcase_create("s21_add_30");
  suite_add_tcase(s, tc_add_30);
  tcase_add_test(tc_add_30, s21_add_30);

  TCase *tc_add_31;
  tc_add_31 = tcase_create("s21_add_31");
  suite_add_tcase(s, tc_add_31);
  tcase_add_test(tc_add_31, s21_add_31);

  TCase *tc_add_32;
  tc_add_32 = tcase_create("s21_add_32");
  suite_add_tcase(s, tc_add_32);
  tcase_add_test(tc_add_32, s21_add_32);

  TCase *tc_add_33;
  tc_add_33 = tcase_create("s21_add_33");
  suite_add_tcase(s, tc_add_33);
  tcase_add_test(tc_add_33, s21_add_33);

  TCase *tc_add_34;
  tc_add_34 = tcase_create("s21_add_34");
  suite_add_tcase(s, tc_add_34);
  tcase_add_test(tc_add_34, s21_add_34);

  TCase *tc_add_35;
  tc_add_35 = tcase_create("s21_add_35");
  suite_add_tcase(s, tc_add_35);
  tcase_add_test(tc_add_35, s21_add_35);

  TCase *tc_add_36;
  tc_add_36 = tcase_create("s21_add_36");
  suite_add_tcase(s, tc_add_36);
  tcase_add_test(tc_add_36, s21_add_36);

  TCase *tc_add_37;
  tc_add_37 = tcase_create("s21_add_37");
  suite_add_tcase(s, tc_add_37);
  tcase_add_test(tc_add_37, s21_add_37);

  TCase *tc_add_38;
  tc_add_38 = tcase_create("s21_add_38");
  suite_add_tcase(s, tc_add_38);
  tcase_add_test(tc_add_38, s21_add_38);

  TCase *tc_add_39;
  tc_add_39 = tcase_create("s21_add_39");
  suite_add_tcase(s, tc_add_39);
  tcase_add_test(tc_add_39, s21_add_39);

  TCase *tc_add_40;
  tc_add_40 = tcase_create("s21_add_40");
  suite_add_tcase(s, tc_add_40);
  tcase_add_test(tc_add_40, s21_add_40);

  TCase *tc_add_41;
  tc_add_41 = tcase_create("s21_add_41");
  suite_add_tcase(s, tc_add_41);
  tcase_add_test(tc_add_41, s21_add_41);

  TCase *tc_add_42;
  tc_add_42 = tcase_create("s21_add_42");
  suite_add_tcase(s, tc_add_42);
  tcase_add_test(tc_add_42, s21_add_42);

  TCase *tc_add_43;
  tc_add_43 = tcase_create("s21_add_43");
  suite_add_tcase(s, tc_add_43);
  tcase_add_test(tc_add_43, s21_add_43);

  TCase *tc_add_44;
  tc_add_44 = tcase_create("s21_add_44");
  suite_add_tcase(s, tc_add_44);
  tcase_add_test(tc_add_44, s21_add_44);

  TCase *tc_add_45;
  tc_add_45 = tcase_create("s21_add_45");
  suite_add_tcase(s, tc_add_45);
  tcase_add_test(tc_add_45, s21_add_45);

  TCase *tc_add_46;
  tc_add_46 = tcase_create("s21_add_46");
  suite_add_tcase(s, tc_add_46);
  tcase_add_test(tc_add_46, s21_add_46);

  TCase *tc_sub_111;
  tc_sub_111 = tcase_create("s21_sub_111");
  suite_add_tcase(s, tc_sub_111);
  tcase_add_test(tc_sub_111, s21_sub_111);

  TCase *tc_sub_2;
  tc_sub_2 = tcase_create("s21_sub__2");
  suite_add_tcase(s, tc_sub_2);
  tcase_add_test(tc_sub_2, s21_sub__2);

  TCase *tc_sub_3;
  tc_sub_3 = tcase_create("s21_sub_3");
  suite_add_tcase(s, tc_sub_3);
  tcase_add_test(tc_sub_3, s21_sub_3);

  TCase *tc_sub_4;
  tc_sub_4 = tcase_create("s21_sub_4");
  suite_add_tcase(s, tc_sub_4);
  tcase_add_test(tc_sub_4, s21_sub_4);

  TCase *tc_sub_5;
  tc_sub_5 = tcase_create("s21_sub_5");
  suite_add_tcase(s, tc_sub_5);
  tcase_add_test(tc_sub_5, s21_sub_5);

  TCase *tc_sub_6;
  tc_sub_6 = tcase_create("s21_sub_6");
  suite_add_tcase(s, tc_sub_6);
  tcase_add_test(tc_sub_6, s21_sub_6);

  TCase *tc_sub_7;
  tc_sub_7 = tcase_create("s21_sub_7");
  suite_add_tcase(s, tc_sub_7);
  tcase_add_test(tc_sub_7, s21_sub_7);

  TCase *tc_sub_8;
  tc_sub_8 = tcase_create("s21_sub_8");
  suite_add_tcase(s, tc_sub_8);
  tcase_add_test(tc_sub_8, s21_sub_8);

  TCase *tc_sub_9;
  tc_sub_9 = tcase_create("s21_sub_9");
  suite_add_tcase(s, tc_sub_9);
  tcase_add_test(tc_sub_9, s21_sub_9);

  TCase *tc_sub_10;
  tc_sub_10 = tcase_create("s21_sub_10");
  suite_add_tcase(s, tc_sub_10);
  tcase_add_test(tc_sub_10, s21_sub_10);

  TCase *tc_sub_11;
  tc_sub_11 = tcase_create("s21_sub_11");
  suite_add_tcase(s, tc_sub_11);
  tcase_add_test(tc_sub_11, s21_sub_11);

  TCase *tc_sub_12;
  tc_sub_12 = tcase_create("s21_sub_12");
  suite_add_tcase(s, tc_sub_12);
  tcase_add_test(tc_sub_12, s21_sub_12);

  TCase *tc_sub_13;
  tc_sub_13 = tcase_create("s21_sub_13");
  suite_add_tcase(s, tc_sub_13);
  tcase_add_test(tc_sub_13, s21_sub_13);

  TCase *tc_sub_14;
  tc_sub_14 = tcase_create("s21_sub_14");
  suite_add_tcase(s, tc_sub_14);
  tcase_add_test(tc_sub_14, s21_sub_14);

  TCase *tc_sub_15;
  tc_sub_15 = tcase_create("s21_sub_15");
  suite_add_tcase(s, tc_sub_15);
  tcase_add_test(tc_sub_15, s21_sub_15);

  TCase *tc_sub_16;
  tc_sub_16 = tcase_create("s21_sub_16");
  suite_add_tcase(s, tc_sub_16);
  tcase_add_test(tc_sub_16, s21_sub_16);

  TCase *tc_sub_17;
  tc_sub_17 = tcase_create("s21_sub_17");
  suite_add_tcase(s, tc_sub_17);
  tcase_add_test(tc_sub_17, s21_sub_17);

  TCase *tc_sub_18;
  tc_sub_18 = tcase_create("s21_sub_18");
  suite_add_tcase(s, tc_sub_18);
  tcase_add_test(tc_sub_18, s21_sub_18);

  TCase *tc_sub_19;
  tc_sub_19 = tcase_create("s21_sub_19");
  suite_add_tcase(s, tc_sub_19);
  tcase_add_test(tc_sub_19, s21_sub_19);

  TCase *tc_sub_20;
  tc_sub_20 = tcase_create("s21_sub_20");
  suite_add_tcase(s, tc_sub_20);
  tcase_add_test(tc_sub_20, s21_sub_20);

  TCase *tc_div_1;
  tc_div_1 = tcase_create("s21_div_1");
  suite_add_tcase(s, tc_div_1);
  tcase_add_test(tc_div_1, s21_div_1);

  TCase *tc_div_2;
  tc_div_2 = tcase_create("s21_div_2");
  suite_add_tcase(s, tc_div_2);
  tcase_add_test(tc_div_2, s21_div_2);

  TCase *tc_div_3;
  tc_div_3 = tcase_create("s21_div_3");
  suite_add_tcase(s, tc_div_3);
  tcase_add_test(tc_div_3, s21_div_3);

  TCase *tc_div_4;
  tc_div_4 = tcase_create("s21_div_4");
  suite_add_tcase(s, tc_div_4);
  tcase_add_test(tc_div_4, s21_div_4);

  TCase *tc_div_5;
  tc_div_5 = tcase_create("s21_div_5");
  suite_add_tcase(s, tc_div_5);
  tcase_add_test(tc_div_5, s21_div_5);

  TCase *tc_div_6;
  tc_div_6 = tcase_create("s21_div_6");
  suite_add_tcase(s, tc_div_6);
  tcase_add_test(tc_div_6, s21_div_6);

  TCase *tc_div_8;
  tc_div_8 = tcase_create("s21_div_8");
  suite_add_tcase(s, tc_div_8);
  tcase_add_test(tc_div_8, s21_div_8);

  TCase *tc_div_9;
  tc_div_9 = tcase_create("s21_div_9");
  suite_add_tcase(s, tc_div_9);
  tcase_add_test(tc_div_9, s21_div_9);

  TCase *tc_div_10;
  tc_div_10 = tcase_create("s21_div_10");
  suite_add_tcase(s, tc_div_10);
  tcase_add_test(tc_div_10, s21_div_10);

  TCase *tc_div_11;
  tc_div_11 = tcase_create("s21_div_11");
  suite_add_tcase(s, tc_div_11);
  tcase_add_test(tc_div_11, s21_div_11);

  TCase *tc_div_12;
  tc_div_12 = tcase_create("s21_div_12");
  suite_add_tcase(s, tc_div_12);
  tcase_add_test(tc_div_12, s21_div_12);

  TCase *tc_div_13;
  tc_div_13 = tcase_create("s21_div_13");
  suite_add_tcase(s, tc_div_13);
  tcase_add_test(tc_div_13, s21_div_13);

  TCase *tc_div_14;
  tc_div_14 = tcase_create("s21_div_14");
  suite_add_tcase(s, tc_div_14);
  tcase_add_test(tc_div_14, s21_div_14);

  TCase *tc_div_15;
  tc_div_15 = tcase_create("s21_div_15");
  suite_add_tcase(s, tc_div_15);
  tcase_add_test(tc_div_15, s21_div_15);

  TCase *tc_div_16;
  tc_div_16 = tcase_create("s21_div_16");
  suite_add_tcase(s, tc_div_16);
  tcase_add_test(tc_div_16, s21_div_16);

  TCase *tc_div_17;
  tc_div_17 = tcase_create("s21_div_17");
  suite_add_tcase(s, tc_div_17);
  tcase_add_test(tc_div_17, s21_div_17);

  TCase *tc_div_18;
  tc_div_18 = tcase_create("s21_div_18");
  suite_add_tcase(s, tc_div_18);
  tcase_add_test(tc_div_18, s21_div_18);

  TCase *tc_div_19;
  tc_div_19 = tcase_create("s21_div_19");
  suite_add_tcase(s, tc_div_19);
  tcase_add_test(tc_div_19, s21_div_19);

  TCase *tc_mul_1;
  tc_mul_1 = tcase_create("s21_mul_1");
  suite_add_tcase(s, tc_mul_1);
  tcase_add_test(tc_mul_1, s21_mul_1);

  TCase *tc_mul_2;
  tc_mul_2 = tcase_create("s21_mul_2");
  suite_add_tcase(s, tc_mul_2);
  tcase_add_test(tc_mul_2, s21_mul_2);

  TCase *tc_mul_3;
  tc_mul_3 = tcase_create("s21_mul_3");
  suite_add_tcase(s, tc_mul_3);
  tcase_add_test(tc_mul_3, s21_mul_3);

  TCase *tc_mul_4;
  tc_mul_4 = tcase_create("s21_mul_4");
  suite_add_tcase(s, tc_mul_4);
  tcase_add_test(tc_mul_4, s21_mul_4);

  TCase *tc_mul_5;
  tc_mul_5 = tcase_create("s21_mul_5");
  suite_add_tcase(s, tc_mul_5);
  tcase_add_test(tc_mul_5, s21_mul_5);

  TCase *tc_mul_6;
  tc_mul_6 = tcase_create("s21_mul_6");
  suite_add_tcase(s, tc_mul_6);
  tcase_add_test(tc_mul_6, s21_mul_6);

  TCase *tc_mul_7;
  tc_mul_7 = tcase_create("s21_mul_7");
  suite_add_tcase(s, tc_mul_7);
  tcase_add_test(tc_mul_7, s21_mul_7);

  TCase *tc_mul_8;
  tc_mul_8 = tcase_create("s21_mul_8");
  suite_add_tcase(s, tc_mul_8);
  tcase_add_test(tc_mul_8, s21_mul_8);

  TCase *tc_mul_9;
  tc_mul_9 = tcase_create("s21_mul_9");
  suite_add_tcase(s, tc_mul_9);
  tcase_add_test(tc_mul_9, s21_mul_9);

  TCase *tc_mul_10;
  tc_mul_10 = tcase_create("s21_mul_10");
  suite_add_tcase(s, tc_mul_10);
  tcase_add_test(tc_mul_10, s21_mul_10);

  TCase *tc_mul_11;
  tc_mul_11 = tcase_create("s21_mul_11");
  suite_add_tcase(s, tc_mul_11);
  tcase_add_test(tc_mul_11, s21_mul_11);

  TCase *tc_mul_12;
  tc_mul_12 = tcase_create("s21_mul_12");
  suite_add_tcase(s, tc_mul_12);
  tcase_add_test(tc_mul_12, s21_mul_12);

  TCase *tc_mul_13;
  tc_mul_13 = tcase_create("s21_mul_13");
  suite_add_tcase(s, tc_mul_13);
  tcase_add_test(tc_mul_13, s21_mul_13);

  TCase *tc_mul_14;
  tc_mul_14 = tcase_create("s21_mul_14");
  suite_add_tcase(s, tc_mul_14);
  tcase_add_test(tc_mul_14, s21_mul_14);

  TCase *tc_mul_15;
  tc_mul_15 = tcase_create("s21_mul_15");
  suite_add_tcase(s, tc_mul_15);
  tcase_add_test(tc_mul_15, s21_mul_15);

  TCase *tc_mul_16;
  tc_mul_16 = tcase_create("s21_mul_16");
  suite_add_tcase(s, tc_mul_16);
  tcase_add_test(tc_mul_16, s21_mul_16);

  TCase *tc_mul_17;
  tc_mul_17 = tcase_create("s21_mul_17");
  suite_add_tcase(s, tc_mul_17);
  tcase_add_test(tc_mul_17, s21_mul_17);

  TCase *tc_mul_18;
  tc_mul_18 = tcase_create("s21_mul_18");
  suite_add_tcase(s, tc_mul_18);
  tcase_add_test(tc_mul_18, s21_mul_18);

  TCase *tc_mul_19;
  tc_mul_19 = tcase_create("s21_mul_19");
  suite_add_tcase(s, tc_mul_19);
  tcase_add_test(tc_mul_19, s21_mul_19);

  TCase *tc_mul_20;
  tc_mul_20 = tcase_create("s21_mul_20");
  suite_add_tcase(s, tc_mul_20);
  tcase_add_test(tc_mul_20, s21_mul_20);

  TCase *tc_mul_21;
  tc_mul_21 = tcase_create("s21_mul_21");
  suite_add_tcase(s, tc_mul_21);
  tcase_add_test(tc_mul_21, s21_mul_21);

  TCase *tc_mul_22;
  tc_mul_22 = tcase_create("s21_mul_22");
  suite_add_tcase(s, tc_mul_22);
  tcase_add_test(tc_mul_22, s21_mul_22);

  TCase *tc_mul_23;
  tc_mul_23 = tcase_create("s21_mul_23");
  suite_add_tcase(s, tc_mul_23);
  tcase_add_test(tc_mul_23, s21_mul_23);

  TCase *tc_mul_24;
  tc_mul_24 = tcase_create("s21_mul_24");
  suite_add_tcase(s, tc_mul_24);
  tcase_add_test(tc_mul_24, s21_mul_24);

  TCase *tc_mul_25;
  tc_mul_25 = tcase_create("s21_mul_25");
  suite_add_tcase(s, tc_mul_25);
  tcase_add_test(tc_mul_25, s21_mul_25);

  TCase *tc_mul_26;
  tc_mul_26 = tcase_create("s21_mul_26");
  suite_add_tcase(s, tc_mul_26);
  tcase_add_test(tc_mul_26, s21_mul_26);

  TCase *tc_mul_27;
  tc_mul_27 = tcase_create("s21_mul_27");
  suite_add_tcase(s, tc_mul_27);
  tcase_add_test(tc_mul_27, s21_mul_27);

  TCase *tc_mul_28;
  tc_mul_28 = tcase_create("s21_mul_28");
  suite_add_tcase(s, tc_mul_28);
  tcase_add_test(tc_mul_28, s21_mul_28);

  TCase *tc_mul_29;
  tc_mul_29 = tcase_create("s21_mul_29");
  suite_add_tcase(s, tc_mul_29);
  tcase_add_test(tc_mul_29, s21_mul_29);

  TCase *tc_mul_30;
  tc_mul_30 = tcase_create("s21_mul_30");
  suite_add_tcase(s, tc_mul_30);
  tcase_add_test(tc_mul_30, s21_mul_30);

  TCase *tc_mul_31;
  tc_mul_31 = tcase_create("s21_mul_31");
  suite_add_tcase(s, tc_mul_31);
  tcase_add_test(tc_mul_31, s21_mul_31);

  TCase *tc_mul_32;
  tc_mul_32 = tcase_create("s21_mul_32");
  suite_add_tcase(s, tc_mul_32);
  tcase_add_test(tc_mul_32, s21_mul_32);

  TCase *tc_mul_33;
  tc_mul_33 = tcase_create("s21_mul_33");
  suite_add_tcase(s, tc_mul_33);
  tcase_add_test(tc_mul_33, s21_mul_33);

  TCase *tc_mul_34;
  tc_mul_34 = tcase_create("s21_mul_34");
  suite_add_tcase(s, tc_mul_34);
  tcase_add_test(tc_mul_34, s21_mul_34);

  TCase *o;
  o = tcase_create("mul");
  suite_add_tcase(s, o);
  tcase_add_test(o, s21_mul_test_1);
  tcase_add_test(o, s21_mul_test_2);
  tcase_add_test(o, s21_mul_test_3);
  tcase_add_test(o, s21_mul_test_4);
  tcase_add_test(o, s21_mul_test_5);
  tcase_add_test(o, s21_mul_test_6);
  tcase_add_test(o, s21_mul_test_7);
  tcase_add_test(o, s21_mul_test_8);
  tcase_add_test(o, s21_mul_test_9);
  tcase_add_test(o, s21_mul_test_10);
  tcase_add_test(o, s21_mul_test_11);
  tcase_add_test(o, s21_mul_test_12);
  tcase_add_test(o, s21_mul_test_13);
  // tcase_add_test(o, s21_mul_test_14);
  tcase_add_test(o, s21_mul_test_15);
  tcase_add_test(o, s21_mul_test_16);
  // tcase_add_test(o, s21_mul_test_17);
  // tcase_add_test(o, s21_mul_test_18);
  // tcase_add_test(o, s21_mul_test_19);
  // tcase_add_test(o, s21_mul_test_20);
  tcase_add_test(o, s21_mul_test_21);
  // tcase_add_test(o, s21_mul_test_22);
  tcase_add_test(o, s21_mul_test_23);
  tcase_add_test(o, s21_mul_test_24);
  tcase_add_test(o, s21_mul_test_25);
  tcase_add_test(o, s21_mul_test_26);
  tcase_add_test(o, s21_mul_test_27);
  tcase_add_test(o, s21_mul_test_28);
  tcase_add_test(o, s21_mul_test_29);
  tcase_add_test(o, s21_mul_test_30);
  tcase_add_test(o, s21_mul_test_31);
  tcase_add_test(o, s21_mul_test_32);
  tcase_add_test(o, s21_mul_test_33);
  tcase_add_test(o, s21_mul_test_34);
  tcase_add_test(o, s21_mul_test_35);
  tcase_add_test(o, s21_mul_test_36);
  tcase_add_test(o, s21_mul_test_37);

  TCase *tc_negate_1;
  tc_negate_1 = tcase_create("s21_negate_1");
  suite_add_tcase(s, tc_negate_1);
  tcase_add_test(tc_negate_1, s21_negate_1);

  TCase *tc_negate_2;
  tc_negate_2 = tcase_create("s21_negate_2");
  suite_add_tcase(s, tc_negate_2);
  tcase_add_test(tc_negate_2, s21_negate_2);

  TCase *tc_negate_3;
  tc_negate_3 = tcase_create("s21_negate_3");
  suite_add_tcase(s, tc_negate_3);
  tcase_add_test(tc_negate_3, s21_negate_3);

  TCase *tc_negate_4;
  tc_negate_4 = tcase_create("s21_negate_4");
  suite_add_tcase(s, tc_negate_4);
  tcase_add_test(tc_negate_4, s21_negate_4);

  TCase *tc_negate_5;
  tc_negate_5 = tcase_create("s21_negate_5");
  suite_add_tcase(s, tc_negate_5);
  tcase_add_test(tc_negate_5, s21_negate_5);

  TCase *tc_truncate_1;
  tc_truncate_1 = tcase_create("s21_truncate_1");
  suite_add_tcase(s, tc_truncate_1);
  tcase_add_test(tc_truncate_1, s21_truncate_1);

  TCase *tc_truncate_2;
  tc_truncate_2 = tcase_create("s21_truncate_2");
  suite_add_tcase(s, tc_truncate_2);
  tcase_add_test(tc_truncate_2, s21_truncate_2);

  TCase *tc_truncate_3;
  tc_truncate_3 = tcase_create("s21_truncate_3");
  suite_add_tcase(s, tc_truncate_3);
  tcase_add_test(tc_truncate_3, s21_truncate_3);

  TCase *tc_truncate_4;
  tc_truncate_4 = tcase_create("s21_truncate_4");
  suite_add_tcase(s, tc_truncate_4);
  tcase_add_test(tc_truncate_4, s21_truncate_4);

  TCase *tc_truncate_5;
  tc_truncate_5 = tcase_create("s21_truncate_5");
  suite_add_tcase(s, tc_truncate_5);
  tcase_add_test(tc_truncate_5, s21_truncate_5);

  TCase *tc_truncate_6;
  tc_truncate_6 = tcase_create("s21_truncate_6");
  suite_add_tcase(s, tc_truncate_6);
  tcase_add_test(tc_truncate_6, s21_truncate_6);

  TCase *tc_round_1;
  tc_round_1 = tcase_create("s21_round_1");
  suite_add_tcase(s, tc_round_1);
  tcase_add_test(tc_round_1, s21_round_1);

  TCase *tc_round_2;
  tc_round_2 = tcase_create("s21_round_2");
  suite_add_tcase(s, tc_round_2);
  tcase_add_test(tc_round_2, s21_round_2);

  TCase *tc_round_3;
  tc_round_3 = tcase_create("s21_round_3");
  suite_add_tcase(s, tc_round_3);
  tcase_add_test(tc_round_3, s21_round_3);

  TCase *tc_round_4;
  tc_round_4 = tcase_create("s21_round_4");
  suite_add_tcase(s, tc_round_4);
  tcase_add_test(tc_round_4, s21_round_4);

  TCase *tc_round_5;
  tc_round_5 = tcase_create("s21_round_5");
  suite_add_tcase(s, tc_round_5);
  tcase_add_test(tc_round_5, s21_round_5);

  TCase *tc_round_6;
  tc_round_6 = tcase_create("s21_round_6");
  suite_add_tcase(s, tc_round_6);
  tcase_add_test(tc_round_6, s21_round_6);

  TCase *tc_round_7;
  tc_round_7 = tcase_create("s21_round_7");
  suite_add_tcase(s, tc_round_7);
  tcase_add_test(tc_round_7, s21_round_7);

  TCase *tc_round_8;
  tc_round_8 = tcase_create("s21_round_8");
  suite_add_tcase(s, tc_round_8);
  tcase_add_test(tc_round_8, s21_round_8);

  TCase *tc_round_9;
  tc_round_9 = tcase_create("s21_round_9");
  suite_add_tcase(s, tc_round_9);
  tcase_add_test(tc_round_9, s21_round_9);

  TCase *tc_round_10;
  tc_round_10 = tcase_create("s21_round_10");
  suite_add_tcase(s, tc_round_10);
  tcase_add_test(tc_round_10, s21_round_10);

  TCase *tc_round_11;
  tc_round_11 = tcase_create("s21_round_11");
  suite_add_tcase(s, tc_round_11);
  tcase_add_test(tc_round_11, s21_round_11);

  TCase *tc_round_12;
  tc_round_12 = tcase_create("s21_round_12");
  suite_add_tcase(s, tc_round_12);
  tcase_add_test(tc_round_12, s21_round_12);

  TCase *tc_floor_1;
  tc_floor_1 = tcase_create("s21_floor_1");
  suite_add_tcase(s, tc_floor_1);
  tcase_add_test(tc_floor_1, s21_floor_1);

  TCase *tc_floor_2;
  tc_floor_2 = tcase_create("s21_floor_2");
  suite_add_tcase(s, tc_floor_2);
  tcase_add_test(tc_floor_2, s21_floor_2);

  TCase *tc_floor_3;
  tc_floor_3 = tcase_create("s21_floor_3");
  suite_add_tcase(s, tc_floor_3);
  tcase_add_test(tc_floor_3, s21_floor_3);

  TCase *tc_floor_4;
  tc_floor_4 = tcase_create("s21_floor_4");
  suite_add_tcase(s, tc_floor_4);
  tcase_add_test(tc_floor_4, s21_floor_4);

  TCase *tc_floor_5;
  tc_floor_5 = tcase_create("s21_floor_5");
  suite_add_tcase(s, tc_floor_5);
  tcase_add_test(tc_floor_5, s21_floor_5);

  TCase *tc_floor_6;
  tc_floor_6 = tcase_create("s21_floor_6");
  suite_add_tcase(s, tc_floor_6);
  tcase_add_test(tc_floor_6, s21_floor_6);

  TCase *tc_floor_7;
  tc_floor_7 = tcase_create("s21_floor_7");
  suite_add_tcase(s, tc_floor_7);
  tcase_add_test(tc_floor_7, s21_floor_7);

  // TCase *tc_from_float_to_decimal_1;
  // tc_from_float_to_decimal_1 = tcase_create("s21_from_float_to_decimal_1");
  // suite_add_tcase(s, tc_from_float_to_decimal_1);
  // tcase_add_test(tc_from_float_to_decimal_1, s21_from_float_to_decimal_1);

  // TCase *tc_from_float_to_decimal_2;
  // tc_from_float_to_decimal_2 = tcase_create("s21_from_float_to_decimal_2");
  // suite_add_tcase(s, tc_from_float_to_decimal_2);
  // tcase_add_test(tc_from_float_to_decimal_2, s21_from_float_to_decimal_2);

  // TCase *tc_from_float_to_decimal_3;
  // tc_from_float_to_decimal_3 = tcase_create("s21_from_float_to_decimal_3");
  // suite_add_tcase(s, tc_from_float_to_decimal_3);
  // tcase_add_test(tc_from_float_to_decimal_3, s21_from_float_to_decimal_3);

  TCase *tc_from_float_to_decimal_4;

  tc_from_float_to_decimal_4 = tcase_create("s21_from_float_to_decimal_4");
  suite_add_tcase(s, tc_from_float_to_decimal_4);
  tcase_add_test(tc_from_float_to_decimal_4, s21_from_float_to_decimal_4);

  TCase *tc_from_float_to_decimal_5;

  tc_from_float_to_decimal_5 = tcase_create("s21_from_float_to_decimal_5");
  suite_add_tcase(s, tc_from_float_to_decimal_5);
  tcase_add_test(tc_from_float_to_decimal_5, s21_from_float_to_decimal_5);

  // TCase *tc_from_float_to_decimal_6;
  // tc_from_float_to_decimal_6 = tcase_create("s21_from_float_to_decimal_6");
  // suite_add_tcase(s, tc_from_float_to_decimal_6);
  // tcase_add_test(tc_from_float_to_decimal_6, s21_from_float_to_decimal_6);

  // TCase *tc_from_float_to_decimal_7;

  // tc_from_float_to_decimal_7 = tcase_create("s21_from_float_to_decimal_7");
  // suite_add_tcase(s, tc_from_float_to_decimal_7);
  // tcase_add_test(tc_from_float_to_decimal_7, s21_from_float_to_decimal_7);

  // TCase *tc_from_float_to_decimal_8;
  // tc_from_float_to_decimal_8 = tcase_create("s21_from_float_to_decimal_8");
  // suite_add_tcase(s, tc_from_float_to_decimal_8);
  // tcase_add_test(tc_from_float_to_decimal_8, s21_from_float_to_decimal_8);

  TCase *tc_from_float_to_decimal_9;

  tc_from_float_to_decimal_9 = tcase_create("s21_from_float_to_decimal_9");
  suite_add_tcase(s, tc_from_float_to_decimal_9);
  tcase_add_test(tc_from_float_to_decimal_9, s21_from_float_to_decimal_9);

  TCase *tc_from_float_to_decimal_10;

  tc_from_float_to_decimal_10 = tcase_create("s21_from_float_to_decimal_10");
  suite_add_tcase(s, tc_from_float_to_decimal_10);
  tcase_add_test(tc_from_float_to_decimal_10, s21_from_float_to_decimal_10);

  TCase *tc_from_float_to_decimal_11;

  tc_from_float_to_decimal_11 = tcase_create("s21_from_float_to_decimal_11");
  suite_add_tcase(s, tc_from_float_to_decimal_11);
  tcase_add_test(tc_from_float_to_decimal_11, s21_from_float_to_decimal_11);

  TCase *tc_from_float_to_decimal_12;

  tc_from_float_to_decimal_12 = tcase_create("s21_from_float_to_decimal_12");
  suite_add_tcase(s, tc_from_float_to_decimal_12);
  tcase_add_test(tc_from_float_to_decimal_12, s21_from_float_to_decimal_12);

  TCase *tc_from_float_to_decimal_13;

  tc_from_float_to_decimal_13 = tcase_create("s21_from_float_to_decimal_13");
  suite_add_tcase(s, tc_from_float_to_decimal_13);
  tcase_add_test(tc_from_float_to_decimal_13, s21_from_float_to_decimal_13);

  // TCase *tc_from_float_to_decimal_14;

  // tc_from_float_to_decimal_14 = tcase_create("s21_from_float_to_decimal_14");
  // suite_add_tcase(s, tc_from_float_to_decimal_14);
  // tcase_add_test(tc_from_float_to_decimal_14, s21_from_float_to_decimal_14);

  TCase *tc_from_float_to_decimal_15;

  tc_from_float_to_decimal_15 = tcase_create("s21_from_float_to_decimal_15");
  suite_add_tcase(s, tc_from_float_to_decimal_15);
  tcase_add_test(tc_from_float_to_decimal_15, s21_from_float_to_decimal_15);

  TCase *tc_from_float_to_decimal_16;

  tc_from_float_to_decimal_16 = tcase_create("s21_from_float_to_decimal_16");
  suite_add_tcase(s, tc_from_float_to_decimal_16);
  tcase_add_test(tc_from_float_to_decimal_16, s21_from_float_to_decimal_16);

  TCase *tc_from_float_to_decimal_17;

  tc_from_float_to_decimal_17 = tcase_create("s21_from_float_to_decimal_17");
  suite_add_tcase(s, tc_from_float_to_decimal_17);
  tcase_add_test(tc_from_float_to_decimal_17, s21_from_float_to_decimal_17);

  TCase *tc_from_float_to_decimal_18;

  tc_from_float_to_decimal_18 = tcase_create("s21_from_float_to_decimal_18");
  suite_add_tcase(s, tc_from_float_to_decimal_18);
  tcase_add_test(tc_from_float_to_decimal_18, s21_from_float_to_decimal_18);

  TCase *tc_from_float_to_decimal_19;

  tc_from_float_to_decimal_19 = tcase_create("s21_from_float_to_decimal_19");
  suite_add_tcase(s, tc_from_float_to_decimal_19);
  tcase_add_test(tc_from_float_to_decimal_19, s21_from_float_to_decimal_19);

  // TCase *tc_from_float_to_decimal_20;

  // tc_from_float_to_decimal_20 = tcase_create("s21_from_float_to_decimal_20");
  // suite_add_tcase(s, tc_from_float_to_decimal_20);
  // tcase_add_test(tc_from_float_to_decimal_20, s21_from_float_to_decimal_20);

  TCase *tc_from_float_to_decimal_21;

  tc_from_float_to_decimal_21 = tcase_create("s21_from_float_to_decimal_21");
  suite_add_tcase(s, tc_from_float_to_decimal_21);
  tcase_add_test(tc_from_float_to_decimal_21, s21_from_float_to_decimal_21);

  // TCase *tc_from_float_to_decimal_22;

  // tc_from_float_to_decimal_22 = tcase_create("s21_from_float_to_decimal_22");
  // suite_add_tcase(s, tc_from_float_to_decimal_22);
  // tcase_add_test(tc_from_float_to_decimal_22, s21_from_float_to_decimal_22);

  TCase *tc_from_float_to_decimal_23;

  tc_from_float_to_decimal_23 = tcase_create("s21_from_float_to_decimal_23");
  suite_add_tcase(s, tc_from_float_to_decimal_23);
  tcase_add_test(tc_from_float_to_decimal_23, s21_from_float_to_decimal_23);

  TCase *tc_from_float_to_decimal_24;

  tc_from_float_to_decimal_24 = tcase_create("s21_from_float_to_decimal_24");
  suite_add_tcase(s, tc_from_float_to_decimal_24);
  tcase_add_test(tc_from_float_to_decimal_24, s21_from_float_to_decimal_24);

  TCase *tc_from_float_to_decimal_25;

  tc_from_float_to_decimal_25 = tcase_create("s21_from_float_to_decimal_25");
  suite_add_tcase(s, tc_from_float_to_decimal_25);
  tcase_add_test(tc_from_float_to_decimal_25, s21_from_float_to_decimal_25);

  TCase *tc_from_float_to_decimal_26;

  tc_from_float_to_decimal_26 = tcase_create("s21_from_float_to_decimal_26");
  suite_add_tcase(s, tc_from_float_to_decimal_26);
  tcase_add_test(tc_from_float_to_decimal_26, s21_from_float_to_decimal_26);

  TCase *tc_from_float_to_decimal_27;

  tc_from_float_to_decimal_27 = tcase_create("s21_from_float_to_decimal_27");
  suite_add_tcase(s, tc_from_float_to_decimal_27);
  tcase_add_test(tc_from_float_to_decimal_27, s21_from_float_to_decimal_27);

  TCase *tc_from_float_to_decimal_28;

  tc_from_float_to_decimal_28 = tcase_create("s21_from_float_to_decimal_28");
  suite_add_tcase(s, tc_from_float_to_decimal_28);
  tcase_add_test(tc_from_float_to_decimal_28, s21_from_float_to_decimal_28);

  // s21_from_int_to_decimal_1

  TCase *tc_from_int_to_decimal_1;
  tc_from_int_to_decimal_1 = tcase_create("s21_from_int_to_decimal_1");
  suite_add_tcase(s, tc_from_int_to_decimal_1);
  tcase_add_test(tc_from_int_to_decimal_1, s21_from_int_to_decimal_1);

  TCase *tc_from_int_to_decimal_2;
  tc_from_int_to_decimal_2 = tcase_create("s21_from_int_to_decimal_2");
  suite_add_tcase(s, tc_from_int_to_decimal_2);
  tcase_add_test(tc_from_int_to_decimal_2, s21_from_int_to_decimal_2);

  TCase *tc_from_int_to_decimal_3;
  tc_from_int_to_decimal_3 = tcase_create("s21_from_int_to_decimal_3");
  suite_add_tcase(s, tc_from_int_to_decimal_3);
  tcase_add_test(tc_from_int_to_decimal_3, s21_from_int_to_decimal_3);

  TCase *tc_from_int_to_decimal_4;
  tc_from_int_to_decimal_4 = tcase_create("s21_from_int_to_decimal_4");
  suite_add_tcase(s, tc_from_int_to_decimal_4);
  tcase_add_test(tc_from_int_to_decimal_4, s21_from_int_to_decimal_4);

  TCase *tc_from_int_to_decimal_5;
  tc_from_int_to_decimal_5 = tcase_create("s21_from_int_to_decimal_5");
  suite_add_tcase(s, tc_from_int_to_decimal_5);
  tcase_add_test(tc_from_int_to_decimal_5, s21_from_int_to_decimal_5);

  TCase *tc_from_int_to_decimal_6;
  tc_from_int_to_decimal_6 = tcase_create("s21_from_int_to_decimal_6");
  suite_add_tcase(s, tc_from_int_to_decimal_6);
  tcase_add_test(tc_from_int_to_decimal_6, s21_from_int_to_decimal_6);

  TCase *tc_from_int_to_decimal_7;
  tc_from_int_to_decimal_7 = tcase_create("s21_from_int_to_decimal_7");
  suite_add_tcase(s, tc_from_int_to_decimal_7);
  tcase_add_test(tc_from_int_to_decimal_7, s21_from_int_to_decimal_7);

  // s21_from_decimal_to_int_1

  TCase *tc_from_decimal_to_int_1;
  tc_from_decimal_to_int_1 = tcase_create("s21_from_decimal_to_int_1");
  suite_add_tcase(s, tc_from_decimal_to_int_1);
  tcase_add_test(tc_from_decimal_to_int_1, s21_from_decimal_to_int_1);

  TCase *tc_from_decimal_to_int_2;
  tc_from_decimal_to_int_2 = tcase_create("s21_from_decimal_to_int_2");
  suite_add_tcase(s, tc_from_decimal_to_int_2);
  tcase_add_test(tc_from_decimal_to_int_2, s21_from_decimal_to_int_2);

  TCase *tc_from_decimal_to_int_3;
  tc_from_decimal_to_int_3 = tcase_create("s21_from_decimal_to_int_3");
  suite_add_tcase(s, tc_from_decimal_to_int_3);
  tcase_add_test(tc_from_decimal_to_int_3, s21_from_decimal_to_int_3);

  TCase *tc_from_decimal_to_int_4;
  tc_from_decimal_to_int_4 = tcase_create("s21_from_decimal_to_int_4");
  suite_add_tcase(s, tc_from_decimal_to_int_4);
  tcase_add_test(tc_from_decimal_to_int_4, s21_from_decimal_to_int_4);

  TCase *tc_from_decimal_to_int_5;
  tc_from_decimal_to_int_5 = tcase_create("s21_from_decimal_to_int_5");
  suite_add_tcase(s, tc_from_decimal_to_int_5);
  tcase_add_test(tc_from_decimal_to_int_5, s21_from_decimal_to_int_5);

  TCase *tc_from_decimal_to_int_6;
  tc_from_decimal_to_int_6 = tcase_create("s21_from_decimal_to_int_6");
  suite_add_tcase(s, tc_from_decimal_to_int_6);
  tcase_add_test(tc_from_decimal_to_int_6, s21_from_decimal_to_int_6);

  TCase *tc_from_decimal_to_int_7;
  tc_from_decimal_to_int_7 = tcase_create("s21_from_decimal_to_int_7");
  suite_add_tcase(s, tc_from_decimal_to_int_7);
  tcase_add_test(tc_from_decimal_to_int_7, s21_from_decimal_to_int_7);

  // s21_from_decimal_to_float

  TCase *tc_from_decimal_to_float_1;
  tc_from_decimal_to_float_1 = tcase_create("s21_from_decimal_to_float_1");
  suite_add_tcase(s, tc_from_decimal_to_float_1);
  tcase_add_test(tc_from_decimal_to_float_1, s21_from_decimal_to_float_1);

  TCase *tc_from_decimal_to_float_2;
  tc_from_decimal_to_float_2 = tcase_create("s21_from_decimal_to_float_2");
  suite_add_tcase(s, tc_from_decimal_to_float_2);
  tcase_add_test(tc_from_decimal_to_float_2, s21_from_decimal_to_float_2);

  TCase *tc_from_decimal_to_float_3;
  tc_from_decimal_to_float_3 = tcase_create("s21_from_decimal_to_float_3");
  suite_add_tcase(s, tc_from_decimal_to_float_3);
  tcase_add_test(tc_from_decimal_to_float_3, s21_from_decimal_to_float_3);

  TCase *tc_from_decimal_to_float_4;
  tc_from_decimal_to_float_4 = tcase_create("s21_from_decimal_to_float_4");
  suite_add_tcase(s, tc_from_decimal_to_float_4);
  tcase_add_test(tc_from_decimal_to_float_4, s21_from_decimal_to_float_4);

  TCase *tc_from_decimal_to_float_5;
  tc_from_decimal_to_float_5 = tcase_create("s21_from_decimal_to_float_5");
  suite_add_tcase(s, tc_from_decimal_to_float_5);
  tcase_add_test(tc_from_decimal_to_float_5, s21_from_decimal_to_float_5);

  TCase *tc_from_decimal_to_float_6;
  tc_from_decimal_to_float_6 = tcase_create("s21_from_decimal_to_float_6");
  suite_add_tcase(s, tc_from_decimal_to_float_6);
  tcase_add_test(tc_from_decimal_to_float_6, s21_from_decimal_to_float_6);

  TCase *tc_from_decimal_to_float_7;
  tc_from_decimal_to_float_7 = tcase_create("s21_from_decimal_to_float_7");
  suite_add_tcase(s, tc_from_decimal_to_float_7);
  tcase_add_test(tc_from_decimal_to_float_7, s21_from_decimal_to_float_7);

  TCase *tc_from_decimal_to_float_8;
  tc_from_decimal_to_float_8 = tcase_create("s21_from_decimal_to_float_8");
  suite_add_tcase(s, tc_from_decimal_to_float_8);
  tcase_add_test(tc_from_decimal_to_float_8, s21_from_decimal_to_float_8);

  TCase *tc_from_decimal_to_float_9;
  tc_from_decimal_to_float_9 = tcase_create("s21_from_decimal_to_float_9");
  suite_add_tcase(s, tc_from_decimal_to_float_9);
  tcase_add_test(tc_from_decimal_to_float_9, s21_from_decimal_to_float_9);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, 2);
  srunner_free(sr);
  return 0;
}
