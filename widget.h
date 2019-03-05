#ifndef WIDGET_H
#define WIDGET_H

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

 private slots:
  void on_tableWidget_cellChanged(int row, int column);

  void on_tableWidget_cellEntered(int row, int column);

  void tableWidget_incMatrix();

 private:
  Ui::Widget *ui;
  QBrush itemBlockBrush;
};

#endif  // WIDGET_H
