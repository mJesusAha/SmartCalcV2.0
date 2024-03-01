#include "s21_credits.h"

namespace s21 {

credit_calc::credit_calc() {
  calc.sum = calc.procent = calc.sum_pl_firsth = calc.sum_pl_last =
      calc.perepl = calc.all = 0;
  calc.years = 0;
}

credit_calc::credit_calc(bool type) : credit_calc() { calc.type = type; }

int credit_calc::Creds() {
  if (calc.type == 1) {
    Annuent();
  }  // ежемесячный платеж фиксированный
  else {
    Diff();
  }  // когда процент постепенно уменьшается

  snprintf(calc.sum_pl_firsth_t, sizeof(calc.sum_pl_firsth_t), "%.2f",
           calc.sum_pl_firsth);
  snprintf(calc.sum_pl_last_t, sizeof(calc.sum_pl_last_t), "%.2f",
           calc.sum_pl_last);
  snprintf(calc.perepl_t, sizeof(calc.perepl_t), "%.2f", calc.perepl);
  snprintf(calc.all_t, sizeof(calc.all_t), "%.2f", calc.all);
  return 0;
}

int credit_calc::Annuent() {
  Okr(&calc.sum);
  Okr(&calc.procent);
  double m = (calc.procent / 12) / 100;
  double t = m * (pow(1 + m, calc.years)) / (pow(1 + m, calc.years) - 1);
  double s = calc.sum * t;
  s = Okr(&s);
  calc.sum_pl_firsth = s;
  calc.sum_pl_last = calc.sum_pl_firsth;
  calc.perepl = (calc.sum_pl_firsth * calc.years) - calc.sum;
  calc.perepl = Okr(&calc.perepl);
  calc.all = calc.sum + calc.perepl;
  return 0;
}

double credit_calc::Okr(double* t) {
  double p = (*t * 100);
  *t = round(p) / 100;
  return *t;
}

int credit_calc::Diff() {
  int t = calc.years;

  double s = calc.sum;

  double OsnDolg = calc.sum / calc.years;

  double summaD = calc.sum;
  double summa = 0;
  while (t != 0) {
    double NacProc = calc.sum * (calc.procent / (12 * 100));

    double sumUplat = OsnDolg + NacProc;

    if (t == calc.years) {
      calc.sum_pl_firsth = sumUplat;
    }
    if (t == 1) {
      { calc.sum_pl_last = sumUplat; }
    }
    summaD = summaD - OsnDolg;
    summa = summa + sumUplat;
    calc.sum = calc.sum - OsnDolg;

    t--;
  }
  calc.all = summa;
  calc.all = Okr(&calc.all);  /////?
  calc.perepl = summa - s;
  calc.perepl = Okr(&calc.perepl);  ////?

  return 0;
}

}  // namespace s21
