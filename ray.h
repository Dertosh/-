#ifndef RAY_H
#define RAY_H

#include <QObject>

class Ray : public QObject {
  Q_OBJECT
 public:
  explicit Ray(QObject *parent = nullptr);
  explicit Ray(short distance, short firstNode, short secondNode,
               QObject *parent = nullptr);
  Ray(Ray &, QObject *parent = nullptr);
  Ray(const Ray &, QObject *parent = nullptr);

  bool operator==(const Ray &ray) const;
  const Ray &operator=(const Ray &);
  void swapNodes();

  short getDistance();
  short getFirstNode();
  short getSecondNode();

 signals:

 public slots:

 private:
  short _distance;    // растояние между узлами
  short _firstNode;   // начальный узел
  short _secondNode;  // конечный узел
};

#endif  // RAY_H
