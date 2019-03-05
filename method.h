#ifndef METHOD_H
#define METHOD_H

#include <QObject>

class method : public QObject
{
    Q_OBJECT
public:
    explicit method(QObject *parent = nullptr);

signals:

public slots:
};

#endif // METHOD_H