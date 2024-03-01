#ifndef SRC_S21_Sort_H_
#define SRC_S21_Sort_H_
#include <cstring>
#include <iostream>
#include <string>
#define MAX 500
namespace s21 {
class pol_nat {
 public:
  pol_nat();
  pol_nat(const std::string string_);

  std::string Polish();

 private:
  void Sort(int i);
  int CheckNat(char* str);
  int TransferringSimbolToStrOut();
  int ForBracket(int i);
  int FunctionPriority(char* string, int i);
  int TransferringSimbolToSteck(int i);
  int TransferringNumberToString(int i);
  void StrErrorPrint();

 private:
  typedef struct {
    char string_out[MAX];
    char stek[MAX];
    int flagNum;
    double X;  // x от пользователя
    int errors;
  } str;
  char string[260];
  str text;
};
}  // namespace s21
#endif  // SRC_S21_Sort_H_
