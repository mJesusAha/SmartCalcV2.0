#ifndef S21_CONTROLLER_CREDIT_H
#define S21_CONTROLLER_CREDIT_H

#include "../model/s21_credits.h"

namespace s21 {
class controller_cred {
 public:
  controller_cred() {}
  controller_cred(bool type_, double sum_, double procent_, double years_)
      : controller_cred() {
    s21::credit_calc N(type_);
    N.SetSum(sum_);
    N.SetProcent(procent_);
    N.SetYears(years_);
    N.Creds();
    all_pay = N.GetAllPay();
    perepl = N.GetPerepl();
    sum_last = N.GetSumLast();
    sum_first = N.GetSumFirst();
  }
  char* GetAllPay() { return all_pay.data(); }
  char* GetPerepl() { return perepl.data(); }
  char* GetSumLast() { return sum_last.data(); }
  char* GetSumFirst() { return sum_first.data(); }

 private:
  std::string all_pay;
  std::string perepl;
  std::string sum_last;
  std::string sum_first;
};

}  // namespace s21
#endif  // S21_CONTROLLER_CREDIT_H
