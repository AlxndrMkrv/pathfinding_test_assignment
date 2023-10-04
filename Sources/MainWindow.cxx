#include "MainWindow.hxx"
#include "./ui_MainWindow.h"
#include <QDebug>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->view->setScene(&_field);
    //ui->view->
    ui->view->fitInView(_field, Qt::KeepAspectRatio);
    /*ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect());
    qDebug() << ui->graphicsView->viewport()->rect();
    ui->graphicsView->scene()->setSceneRect(0, 0, 200, 200);
    qDebug() << ui->graphicsView->sceneRect();*/
    //_field.mouseMoveEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::activateWindow()
{
    qDebug() << "activate";
    QMainWindow::activateWindow();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize: " << event->size() << ", " << ui->graphicsView->rect() << ", " << ui->graphicsView->viewport()->rect();
}*/

/*bool MainWindow::event(QEvent *event)
{
    qDebug() << "event: " << event;
    return QObject::event(event);
}*/


