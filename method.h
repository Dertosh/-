#ifndef METHOD_H
#define METHOD_H

#include <QLoggingCategory>
#include <QObject>

class Method : public QObject {
  Q_OBJECT
 public:
  explicit Method(QObject *parent = nullptr);
  explicit Method(short *mass, short size, short matrixSize,
                  QObject *parent = nullptr);

 signals:
  void printString(QString);

 public slots:
  void addData(short *mass, short size, short matrixSize);

  void process();

 private:
  struct Ray {         // луч между узлами
    short distance;    // растояние между узлами
    short firstNode;   // начальный узел
    short secondNode;  // конечный узел
  };

  QList<Ray> rays;
  void setRayList(short *mass, short size, short matrixSize);
};

#endif  // METHOD_H
