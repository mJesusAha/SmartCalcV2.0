#include "s21_sort.h"
namespace s21 {
pol_nat::pol_nat() {
  text.errors = 0;
  for (int i = 0; i < MAX; ++i) {
    text.string_out[i] = 0;
    string[i] = 0;
    text.stek[i] = 0;
    text.X = 0;
    text.flagNum = 0;
  }
}
pol_nat::pol_nat(const std::string string_) : pol_nat() {
  for (int i = 0; string_[i] != 0; i++) string[i] = string_[i];
}
std::string pol_nat::Polish() {
  int sum = strlen(string);
  // std::cout << "  строка поступила " << string << "\n";
  int res = 0;
  if (string[1] == 'R') {
    res = 1;
  }
  if (res > 0) {
    text.errors = 1;
    //  std::cout << "  ошибка " << res << "\n";
  }
  if (res == 0) {
    for (int i = 0; i != sum; i++) {  // string
      Sort(i);
    }
  }
  text.errors = CheckNat(text.string_out) + text.errors;
  if (text.errors > 0) {
    StrErrorPrint();
  }
  return text.string_out;
}

void pol_nat::Sort(int i) {
  int n = TransferringNumberToString(i);
  if (n == 1) {
    if ((string[i] != ')' && string[i] != '(' && string[i + 1] != 0)) {
      int j = strlen(text.stek) - 1;

      while (FunctionPriority(string, i) <= FunctionPriority((text.stek), j) &&
             j >= 0 && text.stek[j] != '(') {
        TransferringSimbolToStrOut();
        j--;
      }
      TransferringSimbolToSteck(i);
    } else {
      TransferringSimbolToSteck(i);
      ForBracket(i);
    }
  }
  if (string[i + 1] == 0) {
    while (strlen(text.stek) > 0) {
      TransferringSimbolToStrOut();
    }
  }
}

int pol_nat::CheckNat(char* str) {
  int ret = 0;
  int j = strlen(str);
  if ((j >= 2 && (str[j - 1] == '~' || str[j - 1] == '.' ||
                  (str[j - 2] >= 48 && str[j - 2] <= 57) || str[j - 2] == 'X' ||
                  str[j - 2] == 'x' || str[j - 2] == 'E' ||
                  (str[j - 1] >= 48 && str[j - 1] <= 57) || str[j - 1] == 'X' ||
                  str[j - 1] == 'x' || str[j - 1] == 'E' || str[j - 1] == 'e' ||
                  str[j - 2] == 'e')) ||
      j < 2) {
    ret = 1;
  }
  return ret;
}

int pol_nat::TransferringSimbolToStrOut() {
  int k = strlen(text.string_out);
  text.string_out[k] = text.stek[strlen(text.stek) - 1];
  text.stek[strlen(text.stek) - 1] = 0;
  text.string_out[k + 1] = 0;
  return 0;
}

int pol_nat::ForBracket(int i) {
  int res = 0;
  int j = strlen(text.stek);
  int k = strlen(text.string_out);
  if (string[i] == ')' && k + j < MAX) {
    while (j > 1 && text.stek[j - 1] != '(') {
      if (text.stek[j - 1] != ')') {
        int t = strlen(text.string_out);
        text.string_out[t] = text.stek[j - 1];
        text.string_out[t + 1] = 0;
        text.stek[j - 1] = 0;
      }
      j--;
    }
    if (text.stek[j - 1] == '(' && j - 1 >= 0) {
      text.stek[j - 1] = 0;
    }
  }
  return res;
}

int pol_nat::FunctionPriority(char* string, int i) {
  int priority = 0;
  if (i >= 0) {
    char func[] = {"sctmCSTqlL"};
    if (strchr(func, string[i]) != NULL) {
      priority = 3;
    } else if (string[i] == '+' || string[i] == '-') {
      priority = 1;
    } else if (string[i] == '*' || string[i] == '/' || string[i] == '%') {
      priority = 2;
    } else if (string[i] == '^') {
      priority = 4;  // 4
    }
  }
  return priority;
}
int pol_nat::TransferringSimbolToSteck(int i) {
  int j = strlen(text.stek);
  if (j + 2 < MAX && j >= 0) {
    text.stek[j] = string[i];
    text.stek[j + 1] = 0;
  }
  return 0;
}

int pol_nat::TransferringNumberToString(int i) {
  int res = 1;
  if (((string[i] == 126 && (string[i + 1] >= 48 && string[i + 1] <= 57)) ||
       (string[i] >= 48 && string[i] <= 57)) &&
      strlen(text.string_out) < MAX) {
    text.flagNum = 1;
    res = 0;
  }
  if ((((string[i] == 'x' || string[i] == 'X') ||
        (string[i] == 126 && (string[i + 1] == 'x' || string[i + 1] == 'X'))) &&
       strlen(text.string_out) < MAX) &&
      text.flagNum == 0) {
    res = 0;
    // Если есть унарный минус, a за ним x или X и нет права ставить точку то
    // помечаем что перед нами цифра
  }
  if ((string[i] == 46 && text.flagNum == 1) && strlen(text.string_out) < MAX) {
    text.flagNum = 0;
    res = 0;

    // Если уже точно цифра, и можно поставить символ дроби (точку)
  }
  if (((string[i] == 'x' || string[i] == 'X') && text.flagNum == 1) ||
      ((string[i] == 46 && (string[i + 1] == 'x' || string[i + 1] == 'X')) ||
       ((string[i] == 'e' || string[i] == 'E') &&
        text.flagNum == 0)) /*||(string[i] == 46 && text->flagNum == 1)*/) {
    res = -1;  // Если есть цифра и пошел х, если есть точка и пошел х, или ecть
               // е но перед ней не было цифры
    // Если есть точка но перед ней нет цифры, если есть x, и перед ним точка,
    // если есть точка и пошел х, если пошла цифра и за ней х
    //  то re = -1 это ошибка выражения!!!!
  }
  if (res < 0) {
    text.errors = 1;
  }
  if (res == 0) {
    text.string_out[strlen(text.string_out)] = string[i];
    text.string_out[strlen(text.string_out)] = 0;
  }
  if ((res == 0 &&
       (string[i + 1] != 126 && string[i + 1] != 46 && string[i + 1] != 'x' &&
        string[i + 1] != 'X') &&
       (string[i + 1] < 48 || string[i + 1] > 57)) &&
      strlen(text.string_out) < MAX) {
    text.flagNum = 0;
    text.string_out[strlen(text.string_out)] = ' ';
    text.string_out[strlen(text.string_out)] = 0;
  }

  return res;
}
void pol_nat::StrErrorPrint() {
  text.string_out[0] = 'E';
  text.string_out[1] = text.string_out[2] = text.string_out[4] = 'R';
  ;
  text.string_out[3] = 'O';
  text.string_out[5] = 0;
}
}  // namespace s21
