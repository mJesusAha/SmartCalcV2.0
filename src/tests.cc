// Test v
#include <gtest/gtest.h>
#include <tgmath.h>

#include <iostream>

#include "model/s21_calc.h"
#include "model/s21_credits.h"
#include "model/s21_deposid.h"
#include "model/s21_sort.h"
#include "model/s21_val.h"
double myatof(char *s) {
  char *ptrEnd;
  double res = strtod(s, &ptrEnd);
  return res;
}
// int main(){
//  s21::depos_calc new_;
//  ////////////Add//////////////
//  new_.SetSum(1000); //Сумма
//  new_.SetSrock(1);  //Срок
//  new_.SetProcent(10); //Процентная ставка
//  new_.SetCapital(0); //Капитализация 0 без 1
//  new_.SetFlagMonth(0); //0-год
//  new_.SetPeriodPl(3);
//  ////////////////////////////
//  std::string a = "100";
//  new_.SetMonthSumJ(0, 2);
//  new_.SetSumJ(0, a.data());
//  new_.deposid_calc();

// std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
// std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
// std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";

//  deposid new;
//   new.nalog_st = 13;     // налоговая ставка+

//   new.period_pl = 1;     // периодичность выплат+

//   new.spis_pop = 0;    // список пополнений+
//   new.spis_sn = 0;     // список частичных снятий+
//   new.flag_month = 1;  // вклад в месяцах == 1+ а в годах 0;
//   new.sum_j[0] = -500;
//   new.month_sum_j[0] = 0;
//   new.sum_j[1] = -500;
//   new.month_sum_j[1] = 0;
//   new.sum_j[2] = 0;
//   new.month_sum_j[2] = -1;
//   new.sum_j[3] = 0;
//   new.month_sum_j[3] = -50;
//   new.sum_j[4] = 0;
//   new.month_sum_j[4] = -5;
//   new.sum_j[5] = 0;
//   new.month_sum_j[5] = -5;

//   new.sum_j[6] = 0;
//   new.month_sum_j[6] = -1;
//   new.sum_j[7] = 0;
//   new.month_sum_j[7] = -50;
//   new.sum_j[8] = 0;
//   new.month_sum_j[8] = -5;
//   new.sum_j[9] = 0;
//   new.month_sum_j[9] = -5;
//   deposid_calc(&new);
//   printf("\nпроценты начисленные за весь период %f", new.proc);
//   printf("\nсумма на вкладе %f", new.itog);
// ck_assert_int_eq(new.proc, new.proc);

// ck_assert_int_eq(new.itog, new.itog);
// }

//   bool n = 1;
// s21::credit_calc c(n);
// c.SetSum(1000000);
// c.SetProcent(14.5);
// c.SetYears(6);
// c.creds();
// std::cout<< "\nСумма всего\n"<<c.GetAllPay();
// std::cout<< "\nСумма переплаты\n"<<c.GetPerepl();
// std::cout<< "\nСумма платежа в начале\n"<<c.GetSumFirst();
// std::cout<< "\nСумма платежа в конце\n"<<c.GetSumLast();
// //  //  s21::validation_str str ={"1+2"};
// //  s21::validation_str str ={"2^sqrt(4)"};
// //  std::cout<<"Правильно"<<(46-4)-cos(-sin(13.2e1))*126e3<<"\n";
// //  std::string n = str.CheckValid();
// // //std::cout<<"++++++ "<<str<<"\n";

// //  std::cout<<"чек валид "<<n<<"\n";
// // s21::pol_nat new_str_(n);
// // //char* f = {"123"};
// // std::string t;
// // t = new_str_.Polish();
// // std::cout<<"польская нотация  "<<t<<"\n";
// // //s21::calc_str result_(t);
// // //std::cout<<"польская нотация1  "<<t<<"\n";
// // //std::cout<<"********\n";
// // //result_.PrintMass();
// // //std::cout<<"********\n";
// // std::string r;
// // // char r1[500];
// // for (int i = 0; i < 1; i++) {
// //   s21::calc_str result_(t);
// // r = result_.S21Result(i);}

// // std::cout<<"****"<<pow(2, sqrt(4)) <<"*****v2***\n";
// // // result_.PrintMass();
// // // std::cout<<"********\n";
// // // std::cout<<"польская нотация2  "<<t<<"\n";
// // // r = result_.S21Result(3);
// // // std::cout<<"рез-т  "<<r<<"\n";
// // //new_str.S21Result(0);
//     return 0;
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Valid, case1_Uno_minus1) {
  s21::validation_str a = {"--sin(x)"};
  s21::validation_str b = {"-sin(x)"};
  s21::validation_str c = {"-+sin(x)"};

  EXPECT_EQ(a.CheckValid(), "s(x)");
  EXPECT_EQ(b.CheckValid(), "~s(x)");
  EXPECT_EQ(c.CheckValid(), "~s(x)");
}
TEST(Valid, case1_Uno_minus2) {
  s21::validation_str a = {"5+--sin(x)"};
  s21::validation_str b = {"5+-sin(x)"};
  s21::validation_str c = {"5-+sin(x)"};

  EXPECT_EQ(a.CheckValid(), "5+s(x)");
  EXPECT_EQ(b.CheckValid(), "5-s(x)");
  EXPECT_EQ(c.CheckValid(), "5-s(x)");
}

TEST(Valid, case1_Uno_minus3) {
  s21::validation_str a = {"5+-(-sin(x))"};
  s21::validation_str b = {"5+-(sin(x))"};
  s21::validation_str c = {"5-(+sin(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~s(x))");
  EXPECT_EQ(b.CheckValid(), "5-(s(x))");
  EXPECT_EQ(c.CheckValid(), "5-(s(x))");
}
TEST(Valid, case1_Uno_minus4) {
  s21::validation_str a = {"5+   -(-sin( x))"};
  s21::validation_str b = {"5+-   (sin  (x))"};
  s21::validation_str c = {"5-(+   si n(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~s(x))");
  EXPECT_EQ(b.CheckValid(), "5-(s(x))");
  EXPECT_EQ(c.CheckValid(), "5-(s(x))");
}

TEST(Valid, case2_bracket_1ERROR) {
  s21::validation_str a = {"(5+   -(-sin( x))"};
  s21::validation_str b = {"5+-   (sin  (x)))"};
  s21::validation_str c = {"5-(((+   si n(x))"};

  EXPECT_EQ(a.CheckValid(), "ERROR");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}

TEST(Valid, case2_simv_dubl_) {
  s21::validation_str a = {"5+   -(-ssssin( x))"};
  s21::validation_str b = {"5+-   (siiiin  (x))"};
  s21::validation_str c = {"5-(+   si nnnnn(x))"};

  EXPECT_EQ(a.CheckValid(), "ERROR");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}

TEST(Valid, case2_simv_dubl) {
  s21::validation_str a = {"5+   -(-ssin( x))"};
  s21::validation_str b = {"5+-   (siiin  (x))"};
  s21::validation_str c = {"5-(+   si nnn(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~s(x))");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}

TEST(Valid, case2_simv_dubl1) {
  s21::validation_str a = {"5+   -(-ccos( x))"};
  s21::validation_str b = {"5+-   (cooos  (x))"};
  s21::validation_str c = {"5-(+   cosssss(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~c(x))");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}
TEST(Valid, case2_simv_dubl2) {
  s21::validation_str a = {"5+   -(-acoos( x))"};
  s21::validation_str b = {"5+-   (attag  (x))"};
  s21::validation_str c = {"5-(+   tttttgg(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~C(x))");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}
TEST(Valid, case2_simv_dubl3) {
  s21::validation_str a = {"5+   -(-acos( x))"};
  s21::validation_str b = {"5+-   (atan  (x))"};
  s21::validation_str c = {"5-(+   tan(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~C(x))");
  EXPECT_EQ(b.CheckValid(), "5-(T(x))");
  EXPECT_EQ(c.CheckValid(), "5-(t(x))");
}

TEST(Valid, case2_simv_dubl4) {
  s21::validation_str a = {"5+   -(-ln( x))"};
  s21::validation_str b = {"5+-   (asin  (x))"};
  s21::validation_str c = {"5-(+   sqrt(x))"};

  EXPECT_EQ(a.CheckValid(), "5-(~l(x))");
  EXPECT_EQ(b.CheckValid(), "5-(S(x))");
  EXPECT_EQ(c.CheckValid(), "5-(q(x))");
}
TEST(Valid, case2_simv_dubl5) {
  s21::validation_str a = {"5+   -(-llnn( x))"};
  s21::validation_str b = {"5+-   (aassiinn  (x))"};
  s21::validation_str c = {"5-(+   ssqqrrtt(x))"};

  EXPECT_EQ(a.CheckValid(), "ERROR");
  EXPECT_EQ(b.CheckValid(), "ERROR");
  EXPECT_EQ(c.CheckValid(), "ERROR");
}
TEST(Valid, case2_simv_dubl6) {
  s21::validation_str a = {"50%"};
  s21::validation_str b = {"5^+3"};
  s21::validation_str c = {"5^-3"};

  EXPECT_EQ(a.CheckValid(), "50%");
  EXPECT_EQ(b.CheckValid(), "5^3");
  EXPECT_EQ(c.CheckValid(), "5^~3");
}
TEST(result, case1) {
  s21::validation_str str = {"2^(sqrt(4))"};
  std::string n = str.CheckValid();
  s21::pol_nat new_str_(n);
  std::string t = new_str_.Polish();
  s21::calc_str result_(t);
  std::string r = result_.S21Result(0);
  EXPECT_EQ(r, "4.0000000000");
}

TEST(result1, case1) {
  s21::validation_str str = {"2^(sqrt(4))"};
  std::string n = str.CheckValid();
  s21::pol_nat new_str_(n);
  std::string t = new_str_.Polish();
  s21::calc_str result_(t);
  std::string r = result_.S21Result(0);
  char r1[MAX];
  for (int i = 0; r[i] != 0; i++) {
    r1[i] = r[i];
    r[i + 1] = 0;
  }
  double new_ = atof(r1);
  double temp = powf(2, sqrt(4));
  EXPECT_EQ(new_, temp);
}

TEST(result_fun, case1) {
  s21::validation_str str = {"(1+3)+7-(10/2+4)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(0);
  char r1[MAX];
  for (int i = 0; r[i] != 0; i++) {
    r1[i] = r[i];
    r[i + 1] = 0;
  }
  double new_ = atof(r1);
  double temp = (1 + 3) + 7 - (10 / 2 + 4);

  EXPECT_EQ(new_, temp);
}

TEST(result_fun1, case1) {
  s21::validation_str str = {"23/25"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(0);
  char r1[MAX];
  for (int i = 0; r[i] != 0; i++) {
    r1[i] = r[i];
    r[i + 1] = 0;
  }
  double new_ = atof(r1);
  double temp = 23 / 25;
  EXPECT_EQ(new_, temp);
}

TEST(result_fun2, case1) {
  s21::validation_str str = {"(1+3)+7-(10/2.5+4)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(0);
  char r1[MAX];
  for (int i = 0; r[i] != 0; i++) {
    r1[i] = r[i];
    r[i + 1] = 0;
  }
  double new_ = atof(r1);
  double temp = (1 + 3) + 7 - (10 / 2.5 + 4);
  EXPECT_EQ(new_, temp);
}

TEST(result_fun3, case1) {
  s21::validation_str str = {"sin(x)+cos(x)"};
  double temp = sin(3) + cos(3);
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}

TEST(result_fun4, case1) {
  s21::validation_str str = {"tan(x)+asin(x)"};
  double temp = tan(3) + asin(3);
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
/////////////////////////////////
TEST(result_fun5, case1) {
  s21::validation_str str = {"atan(x)+acos(x)"};
  double temp = atan(3) + acos(3);
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun6, case1) {
  s21::validation_str str = {"acos(1)+asin(1) - x"};
  double temp = acos(1) + asin(1) - 3;
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun7, case1) {
  s21::validation_str str = {"22%3"};
  double temp = 22 % 3;
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun8, case1) {
  s21::validation_str str = {"22mod3"};
  double temp = 22 % 3;
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun9, case1) {
  s21::validation_str str = {"log(x)+ln(x)"};
  double temp = log(3) + log10(3);
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun10, case1) {
  s21::validation_str str = {"21+~21.4e6"};
  double temp = 21 + (-21.4 * pow(10, 6));
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}

TEST(result_fun12, case1) {
  s21::validation_str str = {"21+~21.4e6"};
  double temp = 21 + (-21.4 * pow(10, 6));
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}

TEST(result_fun14, case1) {
  s21::validation_str str = {"(21)(2+1)"};
  // double temp = 21+(-21.4*pow(10, 6));
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  // std::string r1;
  // char string_result [MAX];
  // snprintf(string_result, sizeof(string_result), "%.10f", temp);
  // for (int i = 0; string_result[i]!=0; i++)
  //   r1.push_back(string_result[i]);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun13, case1) {
  s21::validation_str str = {"(21+3) cos (x)"};
  // double temp = 21+(-21.4*pow(10, 6));
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  // std::string r1;
  // char string_result [MAX];
  // snprintf(string_result, sizeof(string_result), "%.10f", temp);
  // for (int i = 0; string_result[i]!=0; i++)
  //   r1.push_back(string_result[i]);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun15, case1) {
  s21::validation_str str = {"(21+3) (cos (x))"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(result_fun16, case1) {
  s21::validation_str str = {"(21+3)+(1)"};
  double temp = (21 + 3) + (1);
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  std::string r1;
  char string_result[MAX];
  snprintf(string_result, sizeof(string_result), "%.10f", temp);
  for (int i = 0; string_result[i] != 0; i++) r1.push_back(string_result[i]);
  EXPECT_EQ(r, r1);
}
TEST(result_fun17, case1) {
  s21::validation_str str = {"(21+3)cos (x))"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(result_fun18, case1) {
  s21::validation_str str = {"(21(x))"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(result_fun19, case1) {
  s21::validation_str str = {"(21*(x))(1)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun20, case1) {
  s21::validation_str str = {"sin(x)cos(x))"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun21, case1) {
  s21::validation_str str = {"(21-(x))()"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun22, case1) {
  s21::validation_str str = {"(21-(xx)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun23, case1) {
  s21::validation_str str = {"(21-(x)x"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(result_fun24, case1) {
  s21::validation_str str = {"(21x-(x)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(result_fun25, case1) {
  s21::validation_str str = {"(x.3-(x)"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}
TEST(result_fun26, case1) {
  s21::validation_str str = {"1^xlog3"};
  s21::pol_nat new_str_(str.CheckValid());
  s21::calc_str result_(new_str_.Polish());
  std::string r = result_.S21Result(3);
  EXPECT_EQ(r, "ERROR");
}

TEST(credit_calc, aut) {
  bool n = 1;
  s21::credit_calc c(n);
  c.SetSum(1000000);
  c.SetProcent(14.5);
  c.SetYears(6);
  c.Creds();

  EXPECT_EQ((std::string)c.GetAllPay(), "1042714.92");
  EXPECT_EQ((std::string)c.GetPerepl(), "42714.92");
  EXPECT_EQ((std::string)c.GetSumFirst(), "173785.82");
  EXPECT_EQ((std::string)c.GetSumLast(), "173785.82");
}

TEST(credit_calc, dif) {
  bool n = 0;
  s21::credit_calc c(n);
  c.SetSum(486000);
  c.SetProcent(12.75);
  c.SetYears(60);
  c.Creds();

  EXPECT_EQ((std::string)c.GetAllPay(), "643494.38");
  EXPECT_EQ((std::string)c.GetPerepl(), "157494.38");
  EXPECT_EQ((std::string)c.GetSumFirst(), "13263.75");
  EXPECT_EQ((std::string)c.GetSumLast(), "8186.06");
}

TEST(depos_calc, cap) {
  s21::depos_calc new_;
  ////////////Add//////////////
  new_.SetSum(1000);     // Сумма
  new_.SetSrock(1);      // Срок
  new_.SetProcent(10);   // Процентная ставка
  new_.SetCapital(0);    // Капитализация 0 без 1
  new_.SetFlagMonth(0);  // 0-год
  new_.SetPeriodPl(3);
  ////////////////////////////
  std::string a = "100";
  new_.SetMonthSumJ(0, 2);
  new_.SetSumJ(0, a.data());
  new_.DeposidCalc();

  // std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
  // std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
  // std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";
  EXPECT_EQ((double)new_.GetSum(), (double)new_.GetSum());
  EXPECT_EQ((std::string)new_.GetNalog(), (std::string)new_.GetNalog());
  EXPECT_EQ((std::string)new_.GetProcent(), (std::string)new_.GetProcent());
}

TEST(depos_calc, not_cap) {
  s21::depos_calc new_;
  ////////////Add//////////////
  new_.SetSum(1000);     // Сумма
  new_.SetSrock(12);     // Срок
  new_.SetProcent(10);   // Процентная ставка
  new_.SetCapital(1);    // Капитализация 0 без 1
  new_.SetFlagMonth(1);  // 0-год
  new_.SetPeriodPl(3);
  ////////////////////////////
  std::string a = "100";
  new_.SetMonthSumJ(0, 2);
  new_.SetSumJ(0, a.data());
  new_.DeposidCalc();

  // std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
  // std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
  // std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";
  EXPECT_EQ((double)new_.GetSum(), (double)new_.GetSum());
  EXPECT_EQ((std::string)new_.GetNalog(), (std::string)new_.GetNalog());
  EXPECT_EQ((std::string)new_.GetProcent(), (std::string)new_.GetProcent());
}

TEST(depos_calc, month_cap) {
  s21::depos_calc new_;
  ////////////Add//////////////
  new_.SetSum(1000);     // Сумма
  new_.SetSrock(12);     // Срок
  new_.SetProcent(10);   // Процентная ставка
  new_.SetCapital(0);    // Капитализация 0 без 1
  new_.SetFlagMonth(1);  // 0-год
  new_.SetPeriodPl(3);
  ////////////////////////////
  std::string a = "100";
  new_.SetMonthSumJ(0, 2);
  new_.SetSumJ(0, a.data());
  new_.DeposidCalc();

  // std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
  // std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
  // std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";
  EXPECT_EQ((double)new_.GetSum(), (double)new_.GetSum());
  EXPECT_EQ((std::string)new_.GetNalog(), (std::string)new_.GetNalog());
  EXPECT_EQ((std::string)new_.GetProcent(), (std::string)new_.GetProcent());
}

TEST(depos_calc, mont_cap) {
  s21::depos_calc new_;
  ////////////Add//////////////
  new_.SetSum(1000);     // Сумма
  new_.SetSrock(12);     // Срок
  new_.SetProcent(10);   // Процентная ставка
  new_.SetCapital(1);    // Капитализация 0 без 1
  new_.SetFlagMonth(0);  // 0-год
  new_.SetPeriodPl(1);
  ////////////////////////////
  std::string a = "100";
  new_.SetMonthSumJ(0, 2);
  new_.SetSumJ(0, a.data());
  new_.DeposidCalc();

  // std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
  // std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
  // std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";
  EXPECT_EQ((double)new_.GetSum(), (double)new_.GetSum());
  EXPECT_EQ((std::string)new_.GetNalog(), (std::string)new_.GetNalog());
  EXPECT_EQ((std::string)new_.GetProcent(), (std::string)new_.GetProcent());
}

TEST(depos_calc, mont_cap2) {
  s21::depos_calc new_;
  ////////////Add//////////////
  new_.SetSum(1000);     // Сумма
  new_.SetSrock(12);     // Срок
  new_.SetProcent(10);   // Процентная ставка
  new_.SetCapital(1);    // Капитализация 0 без 1
  new_.SetFlagMonth(0);  // 0-год
  new_.SetPeriodPl(0);
  ////////////////////////////
  std::string a = "100";
  new_.SetMonthSumJ(0, 2);
  new_.SetSumJ(0, a.data());
  new_.DeposidCalc();

  // std::cout<<"*******Cумма "<< new_.GetSum()<<"***\n";
  // std::cout<<"*******Налог "<< new_.GetNalog()<<"***\n";
  // std::cout<<"*******Проценты "<< new_.GetProcent()<<"***\n";
  EXPECT_EQ((double)new_.GetSum(), (double)new_.GetSum());
  EXPECT_EQ((std::string)new_.GetNalog(), (std::string)new_.GetNalog());
  EXPECT_EQ((std::string)new_.GetProcent(), (std::string)new_.GetProcent());
}