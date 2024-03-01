#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <tgmath.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX 500
namespace s21 {
class calc_str {
 public:
  char *S21Result(double x);

 private:
  void Calculation();

  int WorkUnaryFunc(int i);

  int WorkDigitS(int i);

  int WorkBackSpace();

  int WorkBinaryFunc(int i);

  void ConvertAdressToNum(int i, double c);
  // переведет индекс адреса в строку и закинет

  double PreparingTheNum(char *str, const double *result);
  // Готовит число к переводу в цифру (адрес = -1)
  // Ecли встретился адрес, то результат положителен.
  // По итогу возвращает число или по адресу или как есть

  void RewiriteArray(const char *count,
                     char *string);  // {  // из count в sfring

  void CleanArrayAfterFunc();

  int ReadSimbols(int i);

  int FunkcionUn(int i);

  void CleanArray(char *str, int max);

  double BinaryFunction(double A, double B,
                        char znak);  //{  // Возвращает вычисление

  double UnaryFunction(double A, char znak);  // {  // Возвращает вычисление

  double MyAtof(char *s);  // {
 private:
  typedef struct {
    char string_out[MAX];
    double X;  // x от пользователя
    int errors;
    char result[MAX];
  } str;

  typedef struct {
    int flag1;
    int flag2;
    char str_a[MAX];
    char str_b[MAX];
    double result[250];
    double res;
    char string_out[MAX];
    int result_j;

  } calc;

  calc count;
  str string;

 public:
  calc_str();
  calc_str(std::string str_);

};  // validation_str *str;
}  // namespace s21

#endif  // SRC_S21_CALC_H_
