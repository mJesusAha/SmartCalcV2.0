#ifndef SRC_S21_GRAPH_H_
#define SRC_S21_GRAPH_H_

#include <QVector>

namespace s21 {
class graph {
  // double h;
 public:
  graph() {
    for_graph.x = for_graph.h = for_graph.x_end = for_graph.x_begin = 0;
    for_graph.x1 = for_graph.x2 = for_graph.y1 = for_graph.y2 = 0;
    for_graph.n = 0;
  }
  double step() {
    double h = 0.01;
    double x2 = for_graph.x2, x1 = for_graph.x1;
   long long int t = 10000;
    while (x1-x2>t|| x1-x2<(-1*(t))) {t = t*10; h = h*10;}
    for_graph.h = h;
    return for_graph.h;
  }
  double SetX1(char* str) {
    for_graph.x1 = MyAtof(str);
    return for_graph.x1;
  }

  double SetX2(char* str) {
    for_graph.x2 = MyAtof(str);
    if (for_graph.x2 < for_graph.x1) for_graph.x2 = for_graph.x1;
    return for_graph.x2;
  }

  double SetY1(char* str) {
    for_graph.y1 = MyAtof(str);
    return for_graph.y1;
  }

  double SetY2(char* str) {
    for_graph.y2 = MyAtof(str);
    return for_graph.y2;
  }
  double GetX1() { return for_graph.x1; }

  QVector<double> MassX(int N, double a) {
    for_graph.mas_x.resize(N);
    QVector<double> mass_x(N);
    for_graph.n = N;
    int i = 0;
    for (double X = a; i < N; X += for_graph.h) {
      if (X == -INFINITY || X == INFINITY || X == NAN) X = 0;
      mass_x[i] = X;
      i++;
    }
    for_graph.mas_x = mass_x;
    return mass_x;
  }
  int GetN() {
    for_graph.n = (for_graph.x2 - for_graph.x1) / for_graph.h + 2;
    return for_graph.n;
  }
  QVector<double> GetMasX() { return for_graph.mas_x; }

  QVector<double> GetMasY() { return for_graph.mas_y; }
  void ClearAll(QVector<double> mas_y) {
    mas_y.clear();
    mas_y.squeeze();
    for_graph.mas_x.clear();
    for_graph.mas_x.squeeze();
  }

 private:
  double MyAtof(char* str) {
    char* ptrEnd;
    double res = strtod(str, &ptrEnd);
    return res;
  }

 private:
  typedef struct graph_n {
    QVector<double> mas_x, mas_y;
    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;
    double x_begin = 0, x_end = 0, h = 0, x = 0;
    int n = 0;
  } graph_n;

 public:
  graph_n for_graph;
};
}  // namespace s21
#endif  // SRC_S21_GRAPH_H_
