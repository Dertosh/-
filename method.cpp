#include "method.h"
Q_LOGGING_CATEGORY(logMethod, "Method");
Method::Method(QObject *parent) : QObject(parent) {}

void Method::addData(short *mass, short size, short matrixSize) {
  setRayList(mass, size, matrixSize);
}

void Method::setRayList(short *mass, short size, short matrixSize) {
  qDebug(logMethod()) << "setRayList";
  QList<Ray> rays;
  short row = 1, column = 2;
  for (short *it = mass, *end = it + size; it < end; it++) {
    Ray temp(*it, row, column);
    rays.append(temp);
    if (column >= matrixSize) {
      row++;
      column = row + 1;
    } else {
      column++;
    }
  }

  this->printString("Начальная очередь");
  this->printString(getString(rays));

  sort(rays.begin(), rays.end());

  this->printString("Отсортированная очередь");
  this->printString(getString(rays));

  QList<Ray> route = getRoute(rays, matrixSize);

  this->printString("Маршрут");
  this->printString(getString(route));
}

template <typename Iterator>
void Method::bubble_sort(Iterator First, Iterator Last) {
  while (First < --Last)
    for (Iterator i = First; i < Last; ++i)
      if ((i + 1)->getDistance() < i->getDistance()) std::iter_swap(i, i + 1);
}

template <typename Iterator>
void Method::sort(Iterator First, Iterator Last) {
  bubble_sort(First, Last);
}

QString Method::getString(QList<Ray> rays) {
  QString str;
  for (auto ray : rays) {
    str += "{расстояние: " + QString::number(ray.getDistance()) +
           ", узлы: " + QString::number(ray.getFirstNode()) + ", " +
           QString::number(ray.getSecondNode()) + "} ";
  }
  return str;
}

QList<Ray> Method::getRoute(QList<Ray> rays, short size) {
  QList<Ray> route;

  route.append(rays.first());
  rays.removeFirst();

  for (short i = 1; i <= size; i++) {
    Ray temp(route.last());
    for (auto ray : rays) {
      if (temp.getSecondNode() == ray.getFirstNode() &&
          !isIncluded(ray.getSecondNode(), route)) {
        route.append(ray);
        rays.removeOne(ray);
        break;
      }
      if (temp.getSecondNode() == ray.getSecondNode() &&
          !isIncluded(ray.getFirstNode(), route)) {
        rays.removeOne(ray);
        ray.swapNodes();
        route.append(ray);
        break;
      }
      if (i == size) {
        if (temp.getSecondNode() == ray.getFirstNode() &&
            route.first().getFirstNode() == ray.getSecondNode()) {
          route.append(ray);
        }
        if (temp.getSecondNode() == ray.getSecondNode() &&
            route.first().getFirstNode() == ray.getFirstNode()) {
          ray.swapNodes();
          route.append(ray);
        }
      }
    }
  }
  Ray temp(route.first());
  for (auto ray : rays) {
    if (temp.getFirstNode() == ray.getFirstNode() &&
        !isIncluded(ray.getSecondNode(), route)) {
      route.append(ray);
      rays.removeOne(ray);
      break;
    }
    if (temp.getFirstNode() == ray.getSecondNode() &&
        !isIncluded(ray.getFirstNode(), route)) {
      rays.removeOne(ray);
      ray.swapNodes();
      route.append(ray);
      break;
    }
  }
  QString str = "Проверка: ";
  if (route.first().getFirstNode() == route.last().getSecondNode())
    str += QString::number(route.first().getFirstNode()) +
           " == " + QString::number(route.last().getSecondNode());
  else
    str += QString::number(route.first().getFirstNode()) +
           " != " + QString::number(route.last().getSecondNode());
  printString(str);
  return route;
}

template <typename T>
void Method::swap(T &a, T &b) {
  T t = a;
  a = b;
  b = t;
}

bool Method::isIncluded(short Node, QList<Ray> rays) {
  for (auto ray : rays) {
    if (ray.getFirstNode() == Node || ray.getSecondNode() == Node) return true;
  }
  return false;
}

void Method::process() {}
