#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QUuid>
#include <QString>
#include <functional>

namespace Ui {
class Toast;
}


class Toast : public QWidget
{
    Q_OBJECT
public:
    explicit Toast(QString message, std::function<void ()> func, int timeToDisapear = 10);

    void moveTo(const QPoint &target, const float velocity);
    bool Toast::operator==(const Toast &toast) const;
    virtual ~Toast();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

signals:
    void beenDead(const QUuid id);

public slots:

private:
    Ui::Toast *ui;
    QTimer *moveTimer;
    QUuid id;
    std::function<void ()> func;
};

#endif // TOAST_H
