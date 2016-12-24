#include "toaster.h"

Toaster::Toaster(QObject *parent) : QObject(parent), screen(QApplication::desktop()->availableGeometry()), toasts()
{
}

void Toaster::toastIt(QString message, std::function<void ()> func, int timeToDisapear)
{
    Toast *toast = new Toast(message, func, timeToDisapear);
    connect(toast, &Toast::beenDead, this, [this, toast]()
    {
        this->toasts.removeOne(toast);
        delete toast;
        this->update();
    });
    toasts.push_front(toast);
    this->update();
    toast->show();
}

void Toaster::update()
{
    auto heigth = screen.height();

    for(int i = 0; i< toasts.size(); i++)
    {
        heigth -= toasts[i]->height();
        toasts[i]->moveTo(QPoint(screen.width()-toasts[i]->width(),heigth), 1);
    }
}

Toaster::~Toaster()
{
    for (auto toast: toasts)
    {
        delete toast;
    }
}
