#include "depos.h"
// https://bbf.ru/calculators/24/ - по этому сайту
#include "ui_depos.h"

depos::depos(QWidget *parent) : QWidget(parent), ui(new Ui::depos) {
  ui->setupUi(this);
  date0 = date1 = date2 = date3 = date4 = date5 = date6 = date7 = date8 =
      date9 = date10 = QDate::currentDate();

  ui->dateEdit->setDate(date0);

  ui->dateEdit_2->setDate(date1);
  ui->dateEdit_3->setDate(date2);
  ui->dateEdit_4->setDate(date3);
  ui->dateEdit_5->setDate(date4);
  ui->dateEdit_6->setDate(date5);

  ui->dateEdit_7->setDate(date6);
  ui->dateEdit_8->setDate(date7);
  ui->dateEdit_9->setDate(date8);
  ui->dateEdit_10->setDate(date9);
  ui->dateEdit_11->setDate(date10);

  ui->radioButton->setChecked(true);
}

depos::~depos() { delete ui; }
void depos::popDep() {
  QString date_1 = ui->lineEdit_4->text(), date_2 = ui->lineEdit_5->text(),
          date_3 = ui->lineEdit_6->text(), date_4 = ui->lineEdit_7->text(),
          date_5 = ui->lineEdit_8->text();
  d1 = date_1.toLocal8Bit();
  d2 = date_2.toLocal8Bit();
  d3 = date_3.toLocal8Bit();
  d4 = date_4.toLocal8Bit();
  d5 = date_5.toLocal8Bit();

  (date_1.isEmpty() || atof(d1.data()) == 0.0)
      ? ui->lineEdit_4->setText("0")
      : ui->lineEdit_4->setText(d1.data());
  (date_2.isEmpty() || atof(d2.data()) == 0.0)
      ? ui->lineEdit_5->setText("0")
      : ui->lineEdit_5->setText(d2.data());
  (date_3.isEmpty() || atof(d3.data()) == 0.0)
      ? ui->lineEdit_6->setText("0")
      : ui->lineEdit_6->setText(d3.data());
  (date_4.isEmpty() || atof(d4.data()) == 0.0)
      ? ui->lineEdit_7->setText("0")
      : ui->lineEdit_7->setText(d4.data());
  (date_5.isEmpty() || atof(d5.data()) == 0.0)
      ? ui->lineEdit_8->setText("0")
      : ui->lineEdit_8->setText(d5.data());
}

void depos::minusDep() {
  QString date_6 = ui->lineEdit_9->text(), date_7 = ui->lineEdit_10->text(),
          date_8 = ui->lineEdit_11->text(), date_9 = ui->lineEdit_12->text(),
          date_10 = ui->lineEdit_13->text();
  d6 = date_6.toLocal8Bit();
  d7 = date_7.toLocal8Bit();
  d8 = date_8.toLocal8Bit();
  d9 = date_9.toLocal8Bit();
  d10 = date_10.toLocal8Bit();

  (date_6.isEmpty() || atof(d6.data()) == 0.0)
      ? ui->lineEdit_9->setText("0")
      : ui->lineEdit_9->setText(d6.data());
  (date_7.isEmpty() || atof(d7.data()) == 0.0)
      ? ui->lineEdit_10->setText("0")
      : ui->lineEdit_10->setText(d7.data());
  (date_8.isEmpty() || atof(d8.data()) == 0.0)
      ? ui->lineEdit_11->setText("0")
      : ui->lineEdit_11->setText(d8.data());
  (date_9.isEmpty() || atof(d9.data()) == 0.0)
      ? ui->lineEdit_12->setText("0")
      : ui->lineEdit_12->setText(d9.data());
  (date_10.isEmpty() || atof(d10.data()) == 0.0)
      ? ui->lineEdit_13->setText("0")
      : ui->lineEdit_13->setText(d10.data());
}
void depos::on_pushButton_clicked() {
  QString sum_in = ui->lineEdit->text(), procents = ui->lineEdit_3->text(),
          month = ui->lineEdit_2->text();
  QByteArray s = sum_in.toLocal8Bit(), p = procents.toLocal8Bit(),
             m = month.toLocal8Bit();

  if (ui->radioButton->isChecked())
    capital = 1;
  else
    capital = 0;

  if (sum_in.isEmpty() || atof(s.data()) == 0.0)
    ui->lineEdit->setText("0");
  else
    ui->lineEdit->setText(s.data());

  if (procents.isEmpty() || atof(p.data()) == 0.0)
    ui->lineEdit_3->setText("0");
  else
    ui->lineEdit_3->setText(p.data());

  if (month.isEmpty() || atof(m.data()) == 0.0)
    ui->lineEdit_2->setText("0");
  else
    ui->lineEdit_2->setText(m.data());

  D.SetOsn(s.data(), p.data(), m.data());

  D.SetFlags(index, capital, period);

  day0 = date0.day();
  month0 = date0.month();
  year0 = date0.year();
  popDep();
  minusDep();
  FormulaPost(date1, 0);
  FormulaPost(date2, 1);
  FormulaPost(date3, 2);
  FormulaPost(date4, 3);
  FormulaPost(date5, 4);

  D.SetSnyatMonth(d6.data(), d7.data(), d8.data(), d9.data(), d10.data());

  FormulaSnyat(date6, 5);
  FormulaSnyat(date7, 6);
  FormulaSnyat(date8, 7);
  FormulaSnyat(date9, 8);
  FormulaSnyat(date10, 9);

  D.SetPopMonth(d1.data(), d2.data(), d3.data(), d4.data(), d5.data());

  printf("SETUP_DATA %d, %d, %d", day0, month0, year0);
  D.Start();

  ui->label_13->setText(D.GetItog());
  ui->label_14->setText(D.GetProcent());
  ui->label_15->setText(D.GetNalog());

  D.~controller_dep();
}

void depos::on_comboBox_activated(int index_) { index = index_; }

void depos::on_comboBox_2_activated(int index) {
  if (index == 0) {
    period = 0;
  } else if (index == 1) {
    period = 3;
  } else if (index == 2) {
    period = 6;
  } else if (index == 3) {
    period = 1;
  }
}

void depos::on_dateEdit_dateChanged(const QDate &date_) { date0 = date_; }

void depos::on_dateEdit_2_dateChanged(const QDate &date1_) { date1 = date1_; }
void depos::FormulaPost(const QDate &d_, int i) {
  D.SetMonthSumJ(i, 0);
  int a = d_.day();
  int b = d_.year();
  int c = d_.month();
  D.SetMonthSumJ(i, (b * 12 + c) - (year0 * 12 + month0));
  if (day0 >= a) {
    D.SetMonthSumJ(i, (D.GetMonthSumJ(i) + 1));
  } else {
    D.SetMonthSumJ(i, (D.GetMonthSumJ(i) + 2));
  }
}
void depos::FormulaSnyat(const QDate &d_, int i) {
  D.SetMonthSumJ(i, 0);
  int b = d_.year();
  int c = d_.month();
  D.SetMonthSumJ(i, (b * 12 + c) - (year0 * 12 + month0));
}
void depos::on_dateEdit_3_dateChanged(const QDate &date2_) { date2 = date2_; }

void depos::on_dateEdit_4_dateChanged(const QDate &date3_) { date3 = date3_; }

void depos::on_dateEdit_5_dateChanged(const QDate &date4_) { date4 = date4_; }

void depos::on_dateEdit_6_dateChanged(const QDate &date5_) { date5 = date5_; }

void depos::on_dateEdit_7_dateChanged(const QDate &date6_) { date6 = date6_; }

void depos::on_dateEdit_8_dateChanged(const QDate &date7_) { date7 = date7_; }

void depos::on_dateEdit_9_dateChanged(const QDate &date8_) { date8 = date8_; }

void depos::on_dateEdit_10_dateChanged(const QDate &date9_) { date9 = date9_; }

void depos::on_dateEdit_11_dateChanged(const QDate &date10_) {
  date10 = date10_;
}
