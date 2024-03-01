#ifndef SRC_S21_VALID_H_
#define SRC_S21_VALID_H_

#include <cstring>
#include <iostream>
#define MAX 500
namespace s21 {
class validation_str {
 public:
  validation_str();
  validation_str(const char *a);

 public:
  std::string CheckValid();

 private:
  void NewStr();
  int ValidSignAll(int i);
  void UnoMinus();
  void DeleteBackspace(int *n);
  void DeleteBackspaceAll();
  void DubleSign();
  void DubleMinus();
  int CheckingTheFunction(const char *func, int n, char simbol, int i);
  void FuncOneSimvol();
  void ReadFunc(int i);
  void CheckBrackets(int i, int *flag);
  void StrErrorPrint();
  void Exponent();
  void ValidationMult();

 public:
  char str_[MAX];

 private:
  size_t error_sign;
  size_t error_func;
};  // validation_str *str;
}  // namespace s21

#endif  // SRC_S21_VALID_H_
// #include "val.tpp"
