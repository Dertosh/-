#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  method = new Method();
  QThread::connect(method, SIGNAL(printString(QString)), ui->textBrowser,
                   SLOT(append(QString)));
  QThread::connect(this, SIGNAL(sendData(short *, short, short)), method,
                   SLOT(addData(short *, short, short)));

  method->moveToThread(&methodTheard);
  QThread::connect(&methodTheard, SIGNAL(finished()), method,
                   SLOT(deleteLater()));
  QThread::connect(&methodTheard, SIGNAL(started()), method, SLOT(process()));

  QThread::connect(ui->incMatButton, SIGNAL(released()), this,
                   SLOT(tableWidget_incMatrix()));
  QThread::connect(ui->startButton, SIGNAL(released()), this,
                   SLOT(calculate()));

  methodTheard.start();

  QStringList tableHorizontalHeaders;
  tableHorizontalHeaders << "Узлы"
                         << "1";
  QStringList tableVerticalHeaders;
  tableVerticalHeaders << "1";
  ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                   QAbstractItemView::SelectedClicked |
                                   QAbstractItemView::EditKeyPressed);

  itemBlockBrush = ui->tableWidget->item(0, 0)->background();
  ui->tableWidget->resizeRowsToContents();
  ui->tableWidget->resizeColumnsToContents();
}

Widget::~Widget() {
  methodTheard.quit();
  delete ui;
  methodTheard.wait();
}

void Widget::on_tableWidget_cellChanged(int row, int column) {
  if (column > row) {
    QTableWidgetItem *item = ui->tableWidget->item(row, column)->clone();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setBackground(itemBlockBrush);
    ui->tableWidget->setItem(column, row, item);
  }
}

void Widget::on_tableWidget_cellEntered(int row, int column) {}

void Widget::tableWidget_incMatrix() {
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
  int row = ui->tableWidget->rowCount() - 1;
  for (int i = 0; i < ui->tableWidget->columnCount(); i++) {
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setBackground(itemBlockBrush);
    ui->tableWidget->setItem(row, i, item);
  }
  ui->tableWidget->item(row, ui->tableWidget->rowCount() - 1)->setText("*");
  ui->tableWidget->resizeRowsToContents();
  ui->tableWidget->resizeColumnsToContents();
}

void Widget::printString(QString str) { ui->textBrowser->append(str); }

void Widget::calculate() {
  ui->tableWidget->setEnabled(false);

  short size = ui->tableWidget->rowCount();
  size = size * (size - 1) / 2;
  short *mass = new short[size];
  for (short r = 0, c = 1, i = 0; i < size; i++) {
    mass[i] = ui->tableWidget->item(r, c)->text().toShort();
    if (c < (ui->tableWidget->columnCount() - 1)) {
      c++;
    } else {
      r++;
      c = r + 1;
    }
  }

  sendData(mass, size, ui->tableWidget->rowCount());

  ui->tableWidget->setEnabled(true);
}
