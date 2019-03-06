#ifndef WIDGET_H
#define WIDGET_H

#include <method.h>
#include <QThread>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

 signals:
  void sendData(short *, short, short);

 private slots:
  void on_tableWidget_cellChanged(int row, int column);

  void on_tableWidget_cellEntered(int row, int column);

  void tableWidget_incMatrix();

  void printString(QString);

  void calculate();

 private:
  Ui::Widget *ui;
  QBrush itemBlockBrush;
  Method *method;
  QThread methodTheard;
};

#endif  // WIDGET_H
