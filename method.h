#ifndef METHOD_H
#define METHOD_H

#include <ray.h>
#include <QLoggingCategory>
#include <QObject>

class Method : public QObject {
  Q_OBJECT
 public:
  explicit Method(QObject *parent = nullptr);
  explicit Method(short *mass, short size, short matrixSize,
                  QObject *parent = nullptr);

  template <typename Iterator>
  void bubble_sort(Iterator First, Iterator Last);

  template <typename Iterator>
  void sort(Iterator First, Iterator Last);

 signals:
  void printString(QString);

 public slots:
  void addData(short *mass, short size, short matrixSize);

  void process();

 private:
  QList<Ray> _rays;
  void setRayList(short *mass, short size, short matrixSize);
  QString getString(QList<Ray> rays);
  QList<Ray> getRoute(QList<Ray> rays, short size);
  template <typename T>
  void swap(T &a, T &b);
  bool isIncluded(short Node, QList<Ray> rays);
  QString getRouteGraphString(QList<Ray> rays);
  QString getRouteSumString(QList<Ray> rays);
  QString getRouteString(QList<Ray> rays);
};

#endif  // METHOD_H
