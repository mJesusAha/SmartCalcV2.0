#include "s21_calc.h"
namespace s21 {
calc_str::calc_str() {
  count.flag1 = count.flag2 = count.res = count.result_j = string.X =
      string.errors = 0;
  for (int i = 0; i < MAX; ++i) {
    count.str_a[i] = count.str_b[i] = count.string_out[i] =
        string.string_out[i] = string.result[i] = 0;
  }
}

calc_str::calc_str(std::string str_) : calc_str() {
  for (int i = 0; str_[i] != 0; ++i) {
    string.string_out[i] = str_[i];
  }
}

char *calc_str::S21Result(double x) {
  char temp[MAX];
  for (int i = 0; string.string_out[i] != 0; ++i) {
    temp[i] = string.string_out[i];
    temp[i + 1] = 0;
  }
  string.X = x;
  Calculation();
  for (int i = 0; temp[i] != 0; ++i) {
    string.string_out[i] = temp[i];
    string.string_out[i + 1] = 0;
  }
  return string.result;
}

void calc_str::Calculation() {
  // printf("\nCтрока в обратной польск = |%s|\n", string.string_out);
  if (string.string_out[0] == 'E') string.errors = 1;
  int i = 0, temp = 0;
  while (string.string_out[i] != 0 && string.errors == 0) {
    temp++;
    int s = ReadSimbols(i);
    if (s == 1) {
      WorkDigitS(i);
    } else if (s == 2) {
      WorkBackSpace();
    } else if (s == 3) {
      WorkBinaryFunc(i);
      i = -1;
      CleanArrayAfterFunc();
    } else if (s == 4) {
      WorkUnaryFunc(i);
      i = -1;
      CleanArrayAfterFunc();
    }
    i++;
  }
  double result = count.res;

  if (string.errors > 0 || result == NAN || result == 1.0 / 0.0 ||
      result == -1.0 / 0.0 || result == 0.0 / 0.0) {
    string.result[0] = 'E';
    string.result[1] = string.result[2] = string.result[4] = 'R';
    string.result[3] = 'O';
    string.result[5] = 0;
    string.errors = 1;
  } else {
    snprintf(string.result, sizeof(string.result), "%.10f", count.res);
  }
}

int calc_str::WorkUnaryFunc(int i) {
  if (count.flag2 == 0 && count.flag1 == 0) {
    string.errors = 666;
  }
  if (count.flag2 == 1) {
    RewiriteArray(count.str_a, count.str_b);
  }
  if (count.flag2 == 2) {
    for (int t = 0; count.str_a[t] != 0; t++) {
      count.string_out[strlen(count.string_out)] = count.str_a[t];
      count.string_out[strlen(count.string_out)] = 0;
    }
    count.string_out[strlen(count.string_out)] = ' ';
  }
  double b = PreparingTheNum(count.str_b, count.result);
  ////      ////////////////////////
  double c = UnaryFunction(b, string.string_out[i]);
  string.errors = (c == NAN || c == INFINITY || c == -INFINITY)
                      ? string.errors + 1
                      : string.errors;
  //////////////////////////////////////////////////////
  ConvertAdressToNum(i, c);
  RewiriteArray(count.string_out, string.string_out);
  CleanArrayAfterFunc();  // oчищение массивов после использования знака
  return 0;
}

int calc_str::WorkDigitS(int i) {
  int j;
  if (count.flag1 == 0 && count.flag2 == 0) {
    count.str_a[0] = string.string_out[i];
    count.str_a[1] = 0;
    count.flag1 = 1;
  } else if (count.flag1 == 1 && count.flag2 == 0) {
    j = strlen(count.str_a);
    count.str_a[j] = string.string_out[i];
    count.str_a[j + 1] = 0;
  } else if ((count.flag1 == 0 && count.flag2 == 1)) {
    count.str_b[0] = string.string_out[i];
    count.str_b[1] = 0;
    count.flag1 = 1;
  } else if (count.flag1 == 1 && count.flag2 == 1) {
    j = strlen(count.str_b);
    count.str_b[j] = string.string_out[i];
    count.str_b[j + 1] = 0;
  } else if (count.flag1 == 0 && count.flag2 == 2) {
    for (int t = 0; count.str_a[t] != 0; t++) {
      int k = strlen(count.string_out);
      count.string_out[k] = count.str_a[t];
      if (count.str_a[t + 1] == 0) {
        count.string_out[k + 1] = ' ';
        k++;
      }
      count.string_out[k + 1] = 0;
    }
    CleanArray(count.str_a, MAX);
    for (int t = 0; count.str_b[t] != 0; t++) {
      int k = strlen(count.str_a);
      count.str_a[k] = count.str_b[t];
      count.str_a[k + 1] = 0;
    }
    CleanArray(count.str_b, MAX);
    count.str_b[0] = string.string_out[i];
    count.str_b[1] = 0;
    count.flag1 = count.flag2 = 1;
  }
  return 0;
}

int calc_str::WorkBackSpace() {
  if (count.flag1 == 1 && count.flag2 == 0) {
    count.flag2 = 1;
    count.flag1 = 0;
  } else if (count.flag1 == 1 && count.flag2 == 1) {
    count.flag2 = 2;
    count.flag1 = 0;
  }
  return 0;
}

int calc_str::WorkBinaryFunc(int i) {
  if (count.flag2 != 2) {
    string.errors = 1;
  }
  if (count.flag2 == 2) {
    double a = PreparingTheNum(count.str_a, count.result);
    double b = PreparingTheNum(count.str_b, count.result);
    ////      ////////////////////////
    double c = BinaryFunction(a, b, string.string_out[i]);
    if (c == NAN || c == INFINITY || c == -INFINITY) {
      string.errors = 1;
    }
    //////////////////////////////////////////////////////
    ConvertAdressToNum(i, c);
    RewiriteArray(count.string_out, string.string_out);
    CleanArrayAfterFunc();
    //     //oчищение массивов после использования знака
  }
  return 0;
}

void calc_str::ConvertAdressToNum(
    int i,
    double c) {  // переведет индекс адреса в строку и закинет
  char res_j[6];
  count.string_out[strlen(count.string_out)] = '$';
  snprintf(res_j, 4, "%d", count.result_j);
  for (int j = 0; res_j[j] != 0; j++) {
    count.string_out[strlen(count.string_out)] = res_j[j];
    count.string_out[strlen(count.string_out)] = 0;
  }
  count.result[count.result_j] = c;
  count.res = count.result[count.result_j];
  count.result_j = count.result_j + 1;
  count.string_out[strlen(count.string_out)] = ' ';
  count.string_out[strlen(count.string_out)] = 0;

  for (int t = i + 1; string.string_out[t] != 0; t++) {
    count.string_out[strlen(count.string_out)] = string.string_out[t];
    count.string_out[strlen(count.string_out)] = 0;
  }
}

double calc_str::PreparingTheNum(
    char *str,
    const double *result) {  // Готовит число к переводу в цифру (адрес = -1)
  // Ecли встретился адрес, то результат положителен.
  // По итогу возвращает число или по адресу или как есть
  int adress = -1;
  double a = 0;
  for (int j = 0; str[j] != 0; j++) {
    if (str[j] == 126) {
      str[j] = 45;
    }
    if (str[j] == 'x' || str[j] == 'X') {
      adress = -2;
    } else if (str[j] == 36) {
      str[j] = ' ';
      adress = atof(str);
    }
  }
  if (adress == -2) {
    a = string.X;  // обработка Х здесь
  } else if (adress == -1) {
    //  a = atof(str);
    a = MyAtof(str);
  } else {
    a = result[adress];
  }
  return a;
}

void calc_str::RewiriteArray(const char *count,
                             char *string) {  // из count в sfring
  CleanArray(string, MAX);
  for (int j = 0; count[j] != 0; j++) {
    string[j] = count[j];
  }
}

void calc_str::CleanArrayAfterFunc() {
  for (int i = 0; i < MAX; ++i) {
    count.string_out[i] = 0;
    count.str_a[i] = 0;
    count.str_b[i] = 0;
  }
  count.flag2 = 0;
  count.flag1 = 0;
  // oчищение массивов после использования знака
}

int calc_str::ReadSimbols(int i) {
  int res = 0;
  if (string.string_out[i] == '$' || string.string_out[i] == 126 ||
      string.string_out[i] == 46 ||
      (string.string_out[i] == 'e' || string.string_out[i] == 'E') ||
      (string.string_out[i] >= 48 && string.string_out[i] <= 57)) {
    res = 1;  // Если прочитало цифру
  } else if (string.string_out[i] == ' ') {
    res = 2;  // Если прочитало пробел
  } else if (string.string_out[i] == '+' || string.string_out[i] == '-' ||
             string.string_out[i] == '*' || string.string_out[i] == '^' ||
             string.string_out[i] == '/' || string.string_out[i] == 'm' ||
             string.string_out[i] == '%') {
    res = 3;  // Если прочитало бинарную функцию
  } else if (FunkcionUn(i) == 1) {
    res = 4;  // Если прочитало унарную функцию
  } else if (string.string_out[i] == 'x' || string.string_out[i] == 'X') {
    res = 1;  // Если прочитало x
  }
  return res;
}

int calc_str::FunkcionUn(int i) {
  char simbols[10] = "sctCSTqlL";
  int res = 0;
  for (int j = 0; simbols[j] != '\0'; j++) {
    if (string.string_out[i] == simbols[j]) {
      res = 1;
    }
  }
  return res;
}

void calc_str::CleanArray(char *str, int max) {
  for (int i = 0; i < max; i++) {
    str[i] = 0;
  }
}

double calc_str::BinaryFunction(double A, double B,
                                char znak) {  // Возвращает вычисление
  double res = 0;
  if (znak == '+')
    res = A + B;
  else if (znak == '-')
    res = A - B;
  else if (znak == '*')
    res = A * B;
  else if (znak == '/')
    res = A / B;
  else if (znak == '^')
    res = powf(A, B);
  else if (znak == 'm' || znak == '%')
    res = fmod(A, B);
  return res;
}
double calc_str::UnaryFunction(double A, char znak) {  // Возвращает вычисление
  double res = 0;
  if (znak == 's')
    res = sin(A);
  else if (znak == 'c')
    res = cos(A);
  else if (znak == 't')
    res = tan(A);
  else if (znak == 'C')
    res = acos(A);
  else if (znak == 'S')
    res = asin(A);
  else if (znak == 'T')
    res = atan(A);
  else if (znak == 'q')
    res = sqrt(A);
  else if (znak == 'l')
    res = log(A);
  else if (znak == 'L')
    res = log10(A);
  return res;
}

double calc_str::MyAtof(char *s) {
  char *ptrEnd;
  double res = strtod(s, &ptrEnd);
  return res;
}

}  // namespace s21
