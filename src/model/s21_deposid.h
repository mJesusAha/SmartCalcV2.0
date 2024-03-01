#ifndef S21_DEPOSID_H
#define S21_DEPOSID_H
#include <math.h>
#include <stdio.h>
namespace s21 {
class depos_calc {
  // #include "credits.h"
  typedef struct {
    double sum;         // сумма вклада +
    double srok;        // срок размещения+
    double procent_st;  // процентная ставка+
    double nalog_st;    // налоговая ставка+
    double period_pl;  // периодичность выплат+ (3-eжеквартально 0-ежемесячно 6
                       // - пол года 1 - год)
    double cap_proc;   // капитализация процентов+
    double spis_pop;   // список пополнений+
    double spis_sn;    // список частичных снятий+
    double proc;       // начисленные проценты-
    double sum_nalog;  // сумма налога-
    double itog;       // сумма на вкладе к концу срока
    int flag_month;    // выбрано в месяцах
    int day_o;         // день открытия
    int month_o;       // месяц открытия
    int years_o;       // год открытия
    char sum_nalog_t[100];
    char itog_t[100];
    char proc_t[100];
    double sum_j[10];  // сумма для поступления
    int month_sum_j[10];  // месяц когда поступит от начала периода

  } deposid;

 public:
  deposid n;
  depos_calc();
  ~depos_calc();
  //////////Setters///////////////////

  void SetSum(double sum);
  void SetProcent(double procent_st);
  void SetSrock(double srok);
  void SetSumNalog(double sum_nalog);
  void SetItog(double itog);
  void SetCapital(double capital);
  void SetNalogSt(double nal_st);
  void SetPeriodPl(double period_pl);
  void SetSpisPop(double spis_pop);
  void SetSpisSn(double spis_sn);
  void SetFlagMonth(int flag_month);
  void SetSumJ(int i, char* sum_j);
  void SetMonthSumJ(int i, double month_sum_j);
  ///////////////////////////////////////
  ////////////Getters///////////////////
  char* GetProcent();
  int GetYearsO();
  int GetMonthO();
  int GetDayO();
  double GetSum();
  char* GetItog();
  char* GetNalog();
  double GetSumJ(int i);
  double GetMonthSumJ(int i);
  ///////////////////////////////////////

  void Minus();
  int DeposidCalc();
  void Post(double* new_summa, int j, const double* s, int t);
  void MinPost(double* new_summa, int j, const double* s, int t);
  int Prost();
  double Okr(double* t);
  int ProstCapit();
  int PayCvartal();
};
}  // namespace s21
#endif  // S21_DEPOSID_H
