#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

#include "../controller/s21_controller_credit.h"
namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_comboBox_activated(int index);

  void on_pushButton_clicked();

 public:
  bool type;

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
