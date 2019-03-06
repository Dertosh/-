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
  QString str;
  for (auto ray : rays) {
    str += "{расстояние: " + QString::number(ray.distance) +
           ", узлы: " + QString::number(ray.firstNode) + ", " +
           QString::number(ray.secondNode) + "} ";
  }
  this->printString(str);
}

void Method::process() {}
