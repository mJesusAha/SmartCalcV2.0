#ifndef S21_CONTROLLER_CALC_H
#define S21_CONTROLLER_CALC_H

#include "../model/s21_calc.h"
#include "../model/s21_sort.h"
#include "../model/s21_val.h"

namespace s21 {
class controller {
 public:
  controller() : polish_(nullptr){};
  controller(const char* str_in) {
    s21::validation_str str = str_in;
    std::string n = str.CheckValid();
    s21::pol_nat new_str(n);
    polish_ = new_str.Polish();
  }

  char* GetResult(double x1) {
    std::string pol = polish_;
    s21::calc_str result_(pol);
    return result_.S21Result(x1);
  }
  char* GetY(double x_) {
    std::string pol = polish_;
    s21::calc_str result_(pol);
    return result_.S21Result(x_);
  }

 private:
  std::string polish_;
};

}  // namespace s21
#endif  // S21_CONTROLLER_CALC_H
