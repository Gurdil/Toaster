#include "toast.h"
#include "ui_toast.h"

Toast::Toast(QString message, std::function<void ()> func, int timeToDisapear) : QWidget(NULL, Qt::Drawer
                                        | Qt::WindowStaysOnTopHint
                                        | Qt::X11BypassWindowManagerHint
                                        | Qt::FramelessWindowHint), moveTimer(new QTimer(this)), id(QUuid::createUuid()), func(func),
                                        ui(new Ui::Toast)
{
    ui->setupUi(this);
    auto rec = QApplication::desktop()->availableGeometry();

    this->setFixedWidth(2*rec.width()/10);
    this->setFixedHeight(rec.height()/10);
    this->move(rec.width(),rec.height()-this->height());

    ui->message->setText(message);
    connect(ui->exit, &QAbstractButton::clicked, this, &Toast::close);

    QTimer::singleShot(timeToDisapear*1000, this, SLOT(close()));
    moveTimer->setInterval(16);
}

Toast::~Toast()
{
    delete ui;
    delete moveTimer;
}

void Toast::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();

    if (event->button() == Qt::LeftButton)
    {
        this->func();
        this->close();
    }
}

void Toast::moveTo(const QPoint &target, const float velocity)
{
    moveTimer->disconnect();
    auto origine = this->pos();
    auto direction = target - origine;
    connect(moveTimer, &QTimer::timeout, this, [&, target, velocity, origine, direction]()
    {
        auto nowPos = this->pos();
        auto newPose = this->pos() + direction*(velocity/moveTimer->interval());
        if ((newPose - target).manhattanLength() > (nowPos - target).manhattanLength())
        {
            newPose = target;
            moveTimer->stop();
        }

        this->move(newPose);

    });
    moveTimer->start();
}


bool Toast::operator==(const Toast &toast) const
{
    if(this->id == toast.id)
    {
        return true;
    }
    return false;
}

void Toast::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit beenDead(this->id);
}
