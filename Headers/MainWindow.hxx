#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PathfindScene.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* Base class methods implementation */
protected:
    //void activateWindow();
    //virtual void resizeEvent(QResizeEvent *event) override;
    //virtual bool event(QEvent *event) override;

private:
    Ui::MainWindow *ui;
    PathfindScene _field;
};
#endif // MAINWINDOW_H
