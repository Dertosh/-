#include "ray.h"

Ray::Ray(QObject *parent) : QObject(parent) {}

Ray::Ray(short distance, short firstNode, short secondNode, QObject *parent)
    : QObject(parent) {
  _distance = distance;
  _firstNode = firstNode;
  _secondNode = secondNode;
}

bool Ray::operator==(const Ray &ray) const {
  return this->_distance == ray._distance &&
         this->_firstNode == ray._firstNode &&
         this->_secondNode == ray._secondNode;
}

Ray::Ray(const Ray &ray, QObject *parent) : QObject(parent) { *this = ray; }

Ray::Ray(Ray &ray, QObject *parent) : QObject(parent) { *this = ray; }

const Ray &Ray::operator=(const Ray &ray) {
  this->_distance = ray._distance;
  this->_firstNode = ray._firstNode;
  this->_secondNode = ray._secondNode;
  return *this;
}

short Ray::getDistance() { return this->_distance; }
short Ray::getFirstNode() { return this->_firstNode; }
short Ray::getSecondNode() { return this->_secondNode; }

void Ray::swapNodes() {
  short tempNode = this->_firstNode;
  this->_firstNode = this->_secondNode;
  this->_secondNode = tempNode;
}
