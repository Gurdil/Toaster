#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), toaster(new Toaster(this))
{
    ui->setupUi(this);

    connect(ui->toastIt, &QPushButton::clicked, this , [this]()
    {
        this->toaster->toastIt(this->ui->mesage->text(), []()
        {
            qDebug() << "A great action";
        }, this->ui->timeDisappear->value());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete toaster;
}
