#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUI();
    InitConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle(tr("title"));
    ui->m_appNameBtn->setText(tr("title"));

    QString stylePath = QDir::currentPath() + "/main.qss";
    QFile fileQss(stylePath);
    if(!fileQss.open(QFile::ReadOnly))
        return;
    this->setStyleSheet(fileQss.readAll());
}

void MainWindow::InitConnect()
{
    connect(ui->m_closeBtn, &QPushButton::clicked, [=](){this->close();});
    connect(ui->m_minBtn, &QPushButton::clicked, [=](){this->showMinimized();});
    connect(ui->m_maxBtn, &QPushButton::clicked, [=](){this->isMaximized() ? this->showNormal() : this->showMaximized();});
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->setMouseTracking(true);
        m_bMouseIsPressed = true;
        m_pointMove = event->pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMouseIsPressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //最大化时，禁止拖动
    if(this->isMaximized())
        return;
    if (m_bMouseIsPressed)
    {
        QPoint pointPos = event->globalPos();
        this->move(pointPos - m_pointMove);
    }
}
