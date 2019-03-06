#include "method.h"
Q_LOGGING_CATEGORY(logMethod, "Method");
Method::Method(QObject *parent) : QObject(parent) {}

void Method::addData(short *mass, short size, short matrixSize) {
  setRayList(mass, size, matrixSize);
}

void Method::setRayList(short *mass, short size, short matrixSize) {
  qDebug(logMethod()) << "setRayList";
  short row = 1, column = 2;
  for (short *it = mass, *end = it + size; it < end; it++) {
    Ray temp;
    temp.distance = *it;
    temp.firstNode = row;
    temp.secondNode = column;
    rays.append(temp);
    if (column >= matrixSize) {
      row++;
      column = row + 1;
    } else {
      column++;
    }
  }

  this->printString(getString(rays));

  sort(rays.begin(), rays.end());

  this->printString(getString(rays));
}

template <typename Iterator>
void Method::bubble_sort(Iterator First, Iterator Last) {
  while (First < --Last)
    for (Iterator i = First; i < Last; ++i)
      if (Ray(*(i + 1)).distance < Ray(*i).distance) std::iter_swap(i, i + 1);
}

template <typename Iterator>
void Method::sort(Iterator First, Iterator Last) {
  bubble_sort(First, Last);
}

QString Method::getString(QList<Ray> items) {
  QString str;
  for (auto ray : items) {
    str += "{расстояние: " + QString::number(ray.distance) +
           ", узлы: " + QString::number(ray.firstNode) + ", " +
           QString::number(ray.secondNode) + "} ";
  }
  return str;
}

void Method::process() {}
