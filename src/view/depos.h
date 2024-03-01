#ifndef DEPOS_H
#define DEPOS_H

#include <QDateTimeEdit>
#include <QWidget>

#include "../controller/s21_controller_dep.h"
namespace Ui {
class depos;
}

class depos : public QWidget {
  Q_OBJECT

 public:
  explicit depos(QWidget *parent = nullptr);
  ~depos();
 private slots:
  void on_pushButton_clicked();

  void on_comboBox_activated(int index);

  void on_comboBox_2_activated(int index);

  void on_dateEdit_dateChanged(const QDate &date);

  void on_dateEdit_2_dateChanged(const QDate &date);

  void on_dateEdit_3_dateChanged(const QDate &date);

  void on_dateEdit_4_dateChanged(const QDate &date);

  void on_dateEdit_5_dateChanged(const QDate &date);

  void on_dateEdit_6_dateChanged(const QDate &date);

  void on_dateEdit_7_dateChanged(const QDate &date);

  void on_dateEdit_8_dateChanged(const QDate &date);

  void on_dateEdit_9_dateChanged(const QDate &date);

  void on_dateEdit_10_dateChanged(const QDate &date);

  void on_dateEdit_11_dateChanged(const QDate &date);

 private:
  void popDep();
  void minusDep();
  void FormulaPost(const QDate &d_, int i);
  void FormulaSnyat(const QDate &d_, int i);

 private:
  Ui::depos *ui;
  s21::controller_dep D;
  int index = 0;
  int period = 0;
  int capital = 0;
  int day0, month0, year0;
  QDate date0, date1, date2, date3, date4, date5, date6, date7, date8, date9,
      date10;
  QByteArray d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
};

#endif  // DEPOS_H
