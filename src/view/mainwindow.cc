#include "mainwindow.h"

// #include <stdlib.h>

// #include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushEQ_clicked() {
  QString name = ui->lineEdit->text();
  QByteArray t = name.toLocal8Bit();
  /////////////////////////////////////////
  s21::controller str(t.data());

  QFont front_("Newyork", 12);
  ui->widget->xAxis->setTickLabelFont(front_);
  ui->widget->yAxis->setTickLabelFont(front_);
  QString xminname = ui->lineX_min->text(), xmaxname = ui->lineX_max->text();
  QByteArray x1 = xminname.toLocal8Bit(), x2 = xmaxname.toLocal8Bit();
  QString yminname = ui->lineY_min->text(), ymaxname = ui->lineY_max->text();
  QByteArray y1 = yminname.toLocal8Bit(), y2 = ymaxname.toLocal8Bit();
  s21::graph point;

  double X1 = point.SetX1(x1.data()), X2 = point.SetX2(x2.data()),
         Y1 = point.SetY1(y1.data()), Y2 = point.SetY2(y2.data());
  h = point.step();
  ui->widget->replot();
  if (xmaxname.isEmpty()) X2 = point.SetX2(x1.data());
  if (name.isEmpty()) {
    ui->label->setText("0");
  } else {
    std::string res = str.GetResult(X1);
    ui->label->setText(res.data());
    y.resize(point.GetN());
    double x_ = X1;
    for (int i = 0; i < point.GetN(); ++i, x_ += h) {
      y[i] = atof(str.GetY(x_));
    }
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph()->setData(point.MassX(point.GetN(), X1), y);
    ui->widget->xAxis->setRange(X1, X2);
    if (ymaxname.isEmpty() || yminname.isEmpty())
      ui->widget->yAxis->setRange(
          *std::min_element(y.constBegin(), y.constEnd()),
          *std::max_element(y.constBegin(), y.constEnd()));
    ui->widget->yAxis->setRange(Y1, Y2);
    ui->widget->replot();

    point.ClearAll(y);
  }
}
void MainWindow::on_pushButton_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_Button0_2_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void MainWindow::on_Button0_3_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void MainWindow::on_Button0_4_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void MainWindow::on_Button0_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void MainWindow::on_Button0_8_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void MainWindow::on_Button0_5_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void MainWindow::on_Button0_7_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void MainWindow::on_Button0_12_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "~");
}

void MainWindow::on_Button0_30_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::on_Button0_11_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "^(");
}

void MainWindow::on_Button0_21_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void MainWindow::on_Button0_19_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ")");
}

void MainWindow::on_Button0_13_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sin(");
}

void MainWindow::on_Button0_15_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "cos(");
}

void MainWindow::on_Button0_9_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "tan(");
}

void MainWindow::on_Button0_24_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "ln(");
}

void MainWindow::on_Button0_17_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "asin(");
}

void MainWindow::on_Button0_18_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "acos(");
}

void MainWindow::on_Button0_20_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "atan(");
}

void MainWindow::on_Button0_23_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "log(");
}

void MainWindow::on_Button0_25_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sqrt(");
}

void MainWindow::on_Button0_22_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "mod");
}

void MainWindow::on_Button0_29_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "/");
}

void MainWindow::on_Button0_28_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "*");
}

void MainWindow::on_Button0_27_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "-");
}

void MainWindow::on_Button0_26_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "+");
}

void MainWindow::on_Button0_16_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void MainWindow::on_Button0_10_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void MainWindow::on_Button0_14_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void MainWindow::on_Button0_31_clicked() {
  ui->lineEdit->clear();
  ui->label->setText("0");
  point.ClearAll(y);
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked() { credit.show(); }

void MainWindow::on_pushButton_3_clicked() { depos.show(); }
