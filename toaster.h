#ifndef TOASTER_H
#define TOASTER_H

#include <QObject>
#include "toast.h"
#include <QList>
#include <QVector>
#include <QString>
#include <functional>

class Toaster : public QObject
{
    Q_OBJECT
public:
    explicit Toaster(QObject *parent = 0);
    void toastIt(QString message, std::function<void ()> func, int timeToDisapear = 10);
    virtual ~Toaster();

signals:

public slots:
private:
    QList<Toast*> toasts;
    QRect screen;
    void update();
};

#endif // TOASTER_H
