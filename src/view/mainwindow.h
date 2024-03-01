#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../view/credit.h>
#include <../view/depos.h>
#include <stdlib.h>

#include <QMainWindow>
#include <QVector>
#include <cstdlib>

#include "../controller/s21_controller_calc.h"
#include "../untitled/qcustomplot.h"
#include "../view/graf.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 private slots:
  void on_pushEQ_clicked();

  void on_pushButton_clicked();

  void on_Button0_2_clicked();

  void on_Button0_3_clicked();

  void on_Button0_4_clicked();

  void on_Button0_clicked();

  void on_Button0_8_clicked();

  void on_Button0_5_clicked();

  void on_Button0_7_clicked();

  void on_Button0_12_clicked();

  void on_Button0_30_clicked();

  void on_Button0_11_clicked();

  void on_Button0_21_clicked();

  void on_Button0_19_clicked();

  void on_Button0_13_clicked();

  void on_Button0_15_clicked();

  void on_Button0_9_clicked();

  void on_Button0_24_clicked();

  void on_Button0_17_clicked();

  void on_Button0_18_clicked();

  void on_Button0_20_clicked();

  void on_Button0_23_clicked();

  void on_Button0_25_clicked();

  void on_Button0_22_clicked();

  void on_Button0_29_clicked();

  void on_Button0_28_clicked();

  void on_Button0_27_clicked();

  void on_Button0_26_clicked();

  void on_Button0_16_clicked();

  void on_Button0_10_clicked();

  void on_Button0_14_clicked();

  void on_Button0_31_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

 private:
  Ui::MainWindow *ui;
  credit credit;
  depos depos;
  double xBegin = 0, xEnd = 0, h = 0, X = 0;
  int N = 0;
  QVector<double> x, y;
  s21::graph point;
};
#endif  // MAINWINDOW_H
