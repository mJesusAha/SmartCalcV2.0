#include "credit.h"

#include <QWidget>

#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

void credit::on_comboBox_activated(int index) {
  if (index == 1) type = 1;
  if (index == 0) type = 0;
}
void credit::on_pushButton_clicked() {
  QString sum_in = ui->lineEdit->text(), procents = ui->lineEdit_2->text(),
          month = ui->lineEdit_3->text();
  QByteArray s = sum_in.toLocal8Bit(), p = procents.toLocal8Bit(),
             m = month.toLocal8Bit();
  char *summ_in = s.data(), *proc = p.data(), *month_in = m.data();
  double sum = atof(summ_in);
  if (sum_in.isEmpty() || sum <= 0.0) {
    sum = 0;
    ui->lineEdit->setText("0");
  } else {
    ui->lineEdit->setText(s.data());
  }
  double procent = atof(proc);
  if (procents.isEmpty() || procent <= 0.0) {
    procent = 0.01;
    ui->lineEdit_2->setText("0.01");
  } else {
    ui->lineEdit_2->setText(p.data());
  }
  double years = atof(month_in);
  if (month.isEmpty() || years <= 0.0) {
    years = 1;
    ui->lineEdit_3->setText("1");
  } else {
    ui->lineEdit_3->setText(m.data());
  }
  s21::controller_cred N(type, sum, procent, years);

  if (sum_in.isEmpty() || procents.isEmpty() || month.isEmpty()) {
    ui->label_12->setText("0");
    ui->label_11->setText("0");
    ui->label_10->setText("0");
    ui->label_9->setText("0");
  } else {
    ui->label_12->setText(N.GetAllPay());
    ui->label_11->setText(N.GetPerepl());
    ui->label_10->setText(N.GetSumLast());
    ui->label_9->setText(N.GetSumFirst());
  }
}
