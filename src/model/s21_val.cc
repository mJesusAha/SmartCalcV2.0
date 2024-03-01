
#include "s21_val.h"
namespace s21 {
validation_str::validation_str() : error_sign(0U), error_func(0U) {
  for (size_t i = 0; i < MAX; ++i) {
    str_[i] = 0;
  }
}
validation_str::validation_str(const char *a) : validation_str() {
  int i = 0;
  while (a[i] != 0 && i < 256) {
    DeleteBackspace(&i);
    str_[i] = a[i];
    ++i;
  }
}
void validation_str::ValidationMult() {
  std::string sign = "cstlqCSTL(";
  std::string sign2 = ")0123456789xX.";
  std::string sign3 = "0123456789xX.";
  for (int i = 0; str_[i] != 0; ++i) {
    if (str_[i] == ')' && ((sign.find(str_[i + 1]) != std::string::npos)))
      ++error_func;
    if (str_[i + 1] == '(' && ((sign2.find(str_[i]) != std::string::npos)))
      ++error_func;
    if ((str_[i + 1] == 'x' || str_[i + 1] == 'X') &&
        (sign2.find(str_[i]) != std::string::npos))
      ++error_func;
    if ((str_[i] == 'x' || str_[i] == 'X') &&
        (sign.find(str_[i + 1]) != std::string::npos))
      ++error_func;
    if ((str_[i] == 'x' || str_[i] == 'X') &&
        ((sign3.find(str_[i + 1]) != std::string::npos)))
      ++error_func;
  }
}
std::string validation_str::CheckValid() {
  int errors = 0;
  int flag = 0;
  DubleSign();
  for (int i = 0; str_[i] != 0; ++i) {
    if (errors != 0) {
      StrErrorPrint();
      return str_;
    }  // вышло с ошибкой в знаках

    errors = ValidSignAll(i);
    CheckBrackets(i, &flag);
  }
  if (flag != 0) {
    StrErrorPrint();
    return str_;
  }  // 99% ошибка в скобках
  NewStr();
  return str_;  // нет ошибки
}
void validation_str::DeleteBackspaceAll() {
  for (int i = 0; str_[i] != 0; ++i) {
    if (str_[i] == ' ') DeleteBackspace(&i);
  }
}
void validation_str::DeleteBackspace(int *n) {
  int i = *n;
  int j = i + 1;
  while (str_[j] == ' ') {
    ++j;
  }
  if (str_[i] == ' ' && str_[j] != 0) {
    str_[i] = str_[j];
    str_[j] = ' ';
  }
  if (str_[i] == ' ' && str_[j] == 0) {
    str_[i] = 0;
  }
}
void validation_str::CheckBrackets(int i, int *flag) {
  if (str_[i] == '(') ++*flag;
  if (str_[i] == ')') --*flag;
  // 0 normal else error
}
void validation_str::NewStr() {
  UnoMinus();
  UnoMinus();
  FuncOneSimvol();
  DeleteBackspaceAll();
  ValidationMult();
  DubleMinus();
  DeleteBackspaceAll();
  Exponent();
  if (error_func) {
    StrErrorPrint();
    return;
  }
}
int validation_str::ValidSignAll(int i) {  // Проверяет на ошибочные все
  // символы
  // Проверяет 1-й символ на ошибочный
  std::string sign = "/*Ee%^";
  if (sign.find(str_[0]) != std::string::npos) ++error_sign;
  // Проверяет на ошибочные все символы
  std::string simv = "+-/*Ee%^cosaintgarlqmdxX~COSAINTGARLGMD().0123456789~";
  //  for(int i = 0; str_[i]!=0;++i) {
  DeleteBackspace(&i);
  if (simv.find(str_[i]) == std::string::npos) ++error_sign;
  return error_sign;
}
void validation_str::Exponent() {
  if (strchr(str_, 'e') || strchr(str_, 'E')) {
    std::cout << "qqqqqq";
    char temp[MAX];
    // int j = 0;
    for (int i = 0, j = 0; str_[i] != 0; ++i && j++) {
      if (str_[i] == 'e' || str_[i] == 'E') {
        // Обработаем ошибки
        if (i == 0) {
          ++error_func;
          return;
        }
        if (((str_[i - 1] < 48 || str_[i - 1] > 57) && i != 0)) {
          ++error_func;
          return;
        }
        if (str_[i + 1] == 0 || ((str_[i + 1] < 48 || str_[i + 1] > 57) &&
                                 (str_[i + 1] != '+' && str_[i + 1] != '-' &&
                                  str_[i + 1] != '~'))) {
          ++error_func;
          return;
        }
        temp[j] = '*';
        temp[j + 1] = '1';
        temp[j + 2] = '0';
        temp[j + 3] = '^';
        temp[j + 4] = 0;
        j = j + 3;
      } else {
        temp[j] = str_[i];
        temp[j + 1] = 0;
      }
    }
    std::swap(str_, temp);
  }
}

void validation_str::UnoMinus() {  // Унарный минус

  for (int i = 0; str_[i] != 0; ++i) {
    DeleteBackspace(&i);
    if ((str_[i] == 'e' || str_[i] == 'E') && str_[i + 1] == '-')
      str_[i + 1] = '~';
    if ((str_[i] == 'e' || str_[i] == 'E') && str_[i + 1] == '+')
      str_[i + 1] = ' ';
    if ((str_[i] == '(' || str_[i] == '*' || str_[i] == '/' ||
         str_[i] == '^') &&
        str_[i + 1] == '-')
      str_[i + 1] = '~';
    if ((str_[i] == '(' || str_[i] == '*' || str_[i] == '/' ||
         str_[i] == '^') &&
        str_[i + 1] == '+')
      str_[i + 1] = ' ';
    if (str_[i] == '+' && (str_[i + 1] == '-' || str_[i + 1] == '~')) {
      str_[i] = '-';
      str_[i + 1] = ' ';
    }
    if (str_[i + 1] == '+' && (str_[i] == '-' || str_[i] == '~')) {
      str_[i] = '-';
      str_[i + 1] = ' ';
    }
  }
  if (str_[0] == '-') str_[0] = '~';
  if (str_[0] == '+') str_[0] = ' ';
  if ((str_[0] == '~' || str_[0] == '-') &&
      (str_[1] == '~' || str_[1] == '-')) {
    str_[0] = ' ';
    str_[1] = ' ';
  }
}
void validation_str::DubleSign() {
  std::string sign{"+/*Ee%^cosaintgarlqmdCOSAINTGARLGMD"};
  DeleteBackspaceAll();
  for (int i = 0; str_[i] != 0; ++i) {
    while (str_[i] == str_[i + 1] && sign.find(str_[i]) != std::string::npos) {
      for (int s = 0; sign[s] != 0; ++s)
        if ((str_[i] == sign[s]) && (str_[i + 1] == sign[s]) &&
            str_[i] == str_[i + 1]) {
          str_[i + 1] = ' ';
        }
    }
  }
}

void validation_str::DubleMinus() {
  DeleteBackspaceAll();
  for (int i = 0; str_[i] != 0; ++i) {
    if (str_[i] == '-' && str_[i + 1] == '-') {
      str_[i] = '+';
      str_[i + 1] = ' ';
    }
    if (str_[i] == '-' && str_[i + 1] == '+') {
      str_[i] = '-';
      str_[i + 1] = ' ';
    }
    if (str_[i] == '+' && (str_[i + 1] == '-' || str_[i + 1] == '~')) {
      str_[i] = '-';
      str_[i + 1] = ' ';
    }
  }
  DeleteBackspaceAll();
}
int validation_str::CheckingTheFunction(const char *func, int n, char simbol,
                                        int i) {
  int counter = 0, res = 1;
  for (int j = 0; j < n; j++) {
    if (str_[i + j] != func[j]) {
      break;
    } else {
      counter = counter + 1;
    }
  }
  if (counter == n) {
    res = 0;
  }
  if (res == 0) {
    for (int j = 1; j < n; j++) {
      str_[i] = simbol;
      str_[i + j] = ' ';
    }
  }
  return res;
}
void validation_str::FuncOneSimvol() {
  for (int i = 0; str_[i] != 0; ++i) {
    ReadFunc(i);
    std::string sign = " +-/*Ee%^cmstlqxXCSTL().0123456789~";
    if (sign.find(str_[i]) == std::string::npos) ++error_func;
  }
}
void validation_str::ReadFunc(int i) {
  std::string simbols = "sctmal";
  for (int j = 0; simbols[j] != '\0'; j++) {
    if (str_[i] == simbols[j]) {
      int res = 0;
      res += CheckingTheFunction("sin", 3, 's', i);
      res += CheckingTheFunction("cos", 3, 'c', i);
      res += CheckingTheFunction("tan", 3, 't', i);
      res += CheckingTheFunction("mod", 3, 'm', i);
      res += CheckingTheFunction("acos", 4, 'C', i);
      res += CheckingTheFunction("asin", 4, 'S', i);
      res += CheckingTheFunction("atan", 4, 'T', i);
      res += CheckingTheFunction("sqrt", 4, 'q', i);
      res += CheckingTheFunction("ln", 2, 'l', i);
      res += CheckingTheFunction("log", 3, 'L', i);

      if (res == 9)
        return;
      else
        ++error_func;
    }
  }
}

void validation_str::StrErrorPrint() {
  str_[0] = 'E';
  str_[1] = 'R';
  str_[2] = 'R';
  str_[3] = 'O';
  str_[4] = 'R';
  str_[5] = 0;
}

}  // namespace s21
