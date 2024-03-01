#include "s21_deposid.h"
namespace s21 {
depos_calc::depos_calc() {
  n.sum = n.srok = n.procent_st = n.nalog_st = n.period_pl = 0;
  n.cap_proc = n.spis_pop = n.spis_sn = n.proc = n.sum_nalog = n.itog = 0;
  n.flag_month = n.day_o = n.month_o = n.years_o = 0;
  for (int i = 0; i < 100; ++i)
    n.sum_nalog_t[i] = n.itog_t[i] = n.proc_t[i] = 0;
  for (int i = 0; i < 10; ++i) {
    n.sum_j[i] = 0;
    n.month_sum_j[i] = 0;
  }
}
depos_calc::~depos_calc() {
  n.sum = n.srok = n.procent_st = n.nalog_st = n.period_pl = 0;
  n.cap_proc = n.spis_pop = n.spis_sn = n.proc = n.sum_nalog = n.itog = 0;
  n.day_o = n.month_o = n.years_o = 0;
  for (int i = 0; i < 100; ++i)
    n.sum_nalog_t[i] = n.itog_t[i] = n.proc_t[i] = 0;
  for (int i = 0; i < 10; ++i) {
    n.sum_j[i] = 0;
    n.month_sum_j[i] = 0;
  }
}

void depos_calc::SetSum(double sum) { n.sum = sum; }
void depos_calc::SetProcent(double procent_st) { n.procent_st = procent_st; }
void depos_calc::SetSrock(double srok) { n.srok = srok; }
void depos_calc::SetSumNalog(double sum_nalog) { n.sum_nalog = sum_nalog; }
void depos_calc::SetItog(double itog) { n.itog = itog; }
void depos_calc::SetCapital(double capital) { n.cap_proc = capital; }
void depos_calc::SetNalogSt(double nal_st) { n.nalog_st = nal_st; }
void depos_calc::SetPeriodPl(double period_pl) { n.period_pl = period_pl; }
void depos_calc::SetSpisPop(double spis_pop) {
  n.spis_pop = spis_pop;  // список пополнений+
}
void depos_calc::SetSpisSn(double spis_sn) {
  n.spis_sn = spis_sn;  // список частичных снятий+
}
void depos_calc::SetFlagMonth(int flag_month) {
  n.flag_month = flag_month;  // вклад в месяцах == 1+ а в годах 0;
}
void depos_calc::SetSumJ(int i, char* sum_j) {
  double sum_ = atof(sum_j);
  if (i > 9) i = 9;
  if (i < 0) i = 0;
  n.sum_j[i] = sum_;
}
void depos_calc::SetMonthSumJ(int i, double month_sum_j) {
  if (i > 9) i = 9;
  if (i < 0) i = 0;
  n.month_sum_j[i] = month_sum_j;
}
char* depos_calc::GetProcent() { return n.proc_t; }
int depos_calc::GetYearsO() { return n.years_o; }
int depos_calc::GetMonthO() { return n.month_o; }
int depos_calc::GetDayO() { return n.day_o; }
double depos_calc::GetSum() { return n.sum; }
char* depos_calc::GetItog() { return n.itog_t; }
char* depos_calc::GetNalog() { return n.sum_nalog_t; }
double depos_calc::GetSumJ(int i) { return n.sum_j[i]; }
double depos_calc::GetMonthSumJ(int i) { return n.month_sum_j[i]; }

void depos_calc::Minus() {
  if (n.sum < 0) {
    n.sum = 0;
  }
  if (n.srok < 0) {
    n.srok = 0;
  }
  if (n.procent_st < 0) {
    n.procent_st = 0;
  }
  for (int i = 0; i < 10; i++) {
    if (n.sum_j[i] < 0) {
      n.sum_j[i] = 0;
    }
  }
}
int depos_calc::DeposidCalc() {
  Minus();
  if (n.sum > 0 && n.srok > 0 && n.procent_st > 0 &&
      (n.cap_proc == 0 && n.spis_pop == 0 &&
       n.spis_sn == 0 /* && n.period_pl==0*/)) {
    // если без капитализации, пополнений и снятий
    Prost();
  } else if (n.sum > 0 && n.srok > 0 && n.procent_st > 0 && n.cap_proc == 1 &&
             (n.spis_pop == 0 && n.spis_sn == 0 && n.period_pl == 0)) {
    // если с капитализацией, без пополнений и снятий
    ProstCapit();
  } else if (n.sum > 0 && n.srok > 0 && n.procent_st > 0 && n.cap_proc == 1 &&
             (n.spis_pop == 0 && n.spis_sn == 0 &&
              (n.period_pl == 3 || n.period_pl == 6 || n.period_pl == 1))) {
    // если с капитализацией, без пополнений и снятий и с ежеквартальными
    // платежами
    PayCvartal();
  }
  if (n.proc < 0) n.proc = 0;
  if (n.itog >= 0) snprintf(n.itog_t, sizeof(n.itog_t), "%.2f", n.itog);
  if (n.itog < 0) snprintf(n.itog_t, sizeof(n.itog_t), "А что, а где?");
  snprintf(n.proc_t, sizeof(n.proc_t), "%.2f", n.proc);
  if (n.proc > 75000) {
    n.sum_nalog = (n.proc - 75000) / 100 * 13;
  } else {
    n.sum_nalog = 0;
  }
  snprintf(n.sum_nalog_t, sizeof(n.sum_nalog_t), "%.2f", n.sum_nalog);
  return 0;
}
void depos_calc::Post(double* new_summa, int j, const double* s, int t) {
  if (j == n.month_sum_j[t]) {
    *new_summa = *new_summa + s[t];
    n.sum = n.sum + s[t];
    n.sum_j[t] = 0;
    // printf("\ncyмма пополнения  %f", n.sum_j[t]);
  }
}

void depos_calc::MinPost(double* new_summa, int j, const double* s, int t) {
  if (j == n.month_sum_j[t]) {
    *new_summa = *new_summa - s[t];
    n.sum = n.sum - s[t];
    // printf("\ncyмма списания  %f с месяца %d после открытия счета",
    // n.sum_j[t],
    //    n.month_sum_j[t]);
    n.sum_j[t] = 0;
    //      printf("\ncyмма пополнения  %f", n.sum_j[t]);
  }
  if (*new_summa < 0) *new_summa = 0;
  if (n.sum < 0) n.sum = 0;
}
int depos_calc::Prost() {
  double new_summa = n.sum;
  int j = 0;
  if (n.flag_month == 0) n.srok = n.srok * 12;
  int temp = n.srok;
  while (temp != 0) {
    double proc = 0;

    Post(&new_summa, j, n.sum_j, 0);
    Post(&new_summa, j, n.sum_j, 1);
    Post(&new_summa, j, n.sum_j, 2);
    Post(&new_summa, j, n.sum_j, 3);
    Post(&new_summa, j, n.sum_j, 4);
    MinPost(&new_summa, j, n.sum_j, 5);
    MinPost(&new_summa, j, n.sum_j, 6);
    MinPost(&new_summa, j, n.sum_j, 7);
    MinPost(&new_summa, j, n.sum_j, 8);
    MinPost(&new_summa, j, n.sum_j, 9);
    proc =
        (new_summa * n.procent_st * n.srok / 12 / 100) /
        n.srok;  // сумма процентов начисленная за месяц вклада без пополнений
    //     printf("\ncyмма процентов за месяц %f   |%f|", proc, new_summa);
    n.proc = n.proc + proc;
    temp--;
    j++;
  }
  new_summa = new_summa + n.sum_j[0] + n.sum_j[1] + n.sum_j[2] + n.sum_j[3] +
              n.sum_j[4];
  new_summa = Okr(&new_summa);
  n.itog = new_summa;  // сумма на вкладе
  return 0;
}
double depos_calc::Okr(double* t) {
  double p = (*t * 100);
  *t = round(p) / 100;
  return *t;
}
int depos_calc::ProstCapit() {
  // double proc = 0;
  double new_summa = n.sum;
  int j = 0;
  if (n.flag_month == 0) n.srok = n.srok * 12;
  int temp = n.srok;
  //  double proc = 0;
  // если выбрано в месяцах срок
  while (temp != 0) {
    double proc = 0;
    Post(&new_summa, j, n.sum_j, 0);
    Post(&new_summa, j, n.sum_j, 1);
    Post(&new_summa, j, n.sum_j, 2);
    Post(&new_summa, j, n.sum_j, 3);
    Post(&new_summa, j, n.sum_j, 4);
    MinPost(&new_summa, j, n.sum_j, 5);
    MinPost(&new_summa, j, n.sum_j, 6);
    MinPost(&new_summa, j, n.sum_j, 7);
    MinPost(&new_summa, j, n.sum_j, 8);
    MinPost(&new_summa, j, n.sum_j, 9);
    proc =
        (new_summa * n.procent_st * n.srok / 12 / 100) /
        n.srok;  // сумма процентов начисленная за месяц вклада без пополнений
    //    printf("\ncyмма процентов за месяц %f", proc);
    new_summa = new_summa + proc;
    temp--;
    j++;
  }
  new_summa = new_summa + n.sum_j[1] + n.sum_j[2] + n.sum_j[3] + n.sum_j[4] +
              n.sum_j[0];
  new_summa = Okr(&new_summa);
  n.itog = new_summa;  // сумма на вкладе
  n.proc = n.itog - n.sum;
  return 0;
}
int depos_calc::PayCvartal() {
  double new_summa = n.sum;
  int temp2 = 1;
  if (n.flag_month == 0) n.srok = n.srok * 12;
  int temp = n.srok;
  double proc_cvartal = 0;
  int j = 0;
  // если выбрано в месяцах срок
  while (temp != 0) {
    double proc = 0;
    Post(&new_summa, j, n.sum_j, 0);
    Post(&new_summa, j, n.sum_j, 1);
    Post(&new_summa, j, n.sum_j, 2);
    Post(&new_summa, j, n.sum_j, 3);
    Post(&new_summa, j, n.sum_j, 4);
    MinPost(&new_summa, j, n.sum_j, 5);
    MinPost(&new_summa, j, n.sum_j, 6);
    MinPost(&new_summa, j, n.sum_j, 7);
    MinPost(&new_summa, j, n.sum_j, 8);
    MinPost(&new_summa, j, n.sum_j, 9);
    proc =
        (new_summa * n.procent_st * n.srok / 12 / 100) /
        n.srok;  // сумма процентов начисленная за месяц вклада без пополнений
    if (temp2 < 4 && n.period_pl == 3) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 4 && n.period_pl == 3) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //     printf("\ncyмма процентов eжеквартально %f", proc_cvartal);
      proc_cvartal = 0;
    }
    if (temp2 < 7 && n.period_pl == 6) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 7 && n.period_pl == 6) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //    printf("\ncyмма процентов пол года %f", proc_cvartal);
      proc_cvartal = 0;
    }
    if (temp2 < 13 && n.period_pl == 1) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 13 && n.period_pl == 1) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //      printf("\ncyмма процентов за год. %f", proc_cvartal);
      proc_cvartal = 0;
    }
    j++;
    temp--;
  }
  new_summa = new_summa + proc_cvartal + n.sum_j[0] + n.sum_j[1] + n.sum_j[2] +
              n.sum_j[3] + n.sum_j[4];
  // new_summa = Okr(&new_summa);
  n.itog = new_summa;  // сумма на вкладе
  n.proc = n.itog - n.sum;
  return 0;
}

}  // namespace s21