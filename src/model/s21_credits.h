// calcus.ru
#ifndef CREDITS_H
#define CREDITS_H
#include <cmath>
#include <iostream>
namespace s21 {
class credit_calc {
 public:
  void SetSum(double sum) { calc.sum = sum; }
  void SetYears(double years) { calc.years = years; }
  void SetProcent(double procent) { calc.procent = procent; }

  char* GetPerepl() { return calc.perepl_t; }
  char* GetAllPay() { return calc.all_t; }
  char* GetSumFirst() { return calc.sum_pl_firsth_t; }
  char* GetSumLast() { return calc.sum_pl_last_t; }

  int Creds();

 private:
  int Annuent();
  double Okr(double* t);
  int Diff();

 private:
  typedef struct {
    double sum;            // общая сумма кредита
    int years;             // срок
    double procent;        // процентная ставка
    bool type;             // тип платежа
    double sum_pl_firsth;  // cумма платежа
    double sum_pl_last;
    double perepl;  // переплата по кредиту
    double all;     // общая выплата
    char all_t[100];
    char perepl_t[100];
    char sum_pl_firsth_t[100];
    char sum_pl_last_t[100];
  } cred;
  cred calc;

 public:
  credit_calc();
  credit_calc(bool type);
};

}  // namespace s21

#endif  // CREDITS_H
