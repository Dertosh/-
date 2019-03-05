#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  QThread::connect(ui->incMatButton, SIGNAL(released()), this,
                   SLOT(tableWidget_incMatrix()));
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

Widget::~Widget() { delete ui; }

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
