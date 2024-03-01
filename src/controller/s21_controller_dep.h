#ifndef S21_CONTROLLER_DEP_H
#define S21_CONTROLLER_DEP_H

#include "../model/s21_deposid.h"

namespace s21 {

class controller_dep {
 public:
  controller_dep() {}

  ~controller_dep() { n.~depos_calc(); }
  void SetMonthSumJ(int i, double month_sum) { n.SetMonthSumJ(i, month_sum); }
  double GetMonthSumJ(int i) { return n.GetMonthSumJ(i); }
  void SetPopMonth(char* i1, char* i2, char* i3, char* i4, char* i5) {
    n.SetSumJ(0, i1);
    n.SetSumJ(1, i2);
    n.SetSumJ(2, i3);
    n.SetSumJ(3, i4);
    n.SetSumJ(4, i5);
  }
  void SetSnyatMonth(char* i1, char* i2, char* i3, char* i4, char* i5) {
    n.SetSumJ(5, i1);
    n.SetSumJ(6, i2);
    n.SetSumJ(7, i3);
    n.SetSumJ(8, i4);
    n.SetSumJ(9, i5);
  }

  void SetFlags(int set_flaf_month, int set_cap, double set_period) {
    n.SetFlagMonth(set_flaf_month);
    n.SetPeriodPl(set_period);
    n.SetCapital(set_cap);
  }
  void SetOsn(char* sum, char* procent, char* srok) {
    n.SetSum(atof(sum));
    n.SetProcent(atof(procent));
    n.SetSrock(atof(srok));
  }
  char* GetItog() { return n.GetItog(); }
  char* GetProcent() { return n.GetProcent(); }
  char* GetNalog() { return n.GetNalog(); }
  void Start() { n.DeposidCalc(); }

 private:
  s21::depos_calc n;
};

}  // namespace s21
#endif  // S21_CONTROLLER_DEP_H
